#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Use.h"
#include "llvm/IR/User.h"
#include <sstream>
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Utils/PromoteMemToReg.h"
#include "llvm/Transforms/Utils/LoopUtils.h"
#include "llvm/Transforms/Utils/LoopSimplify.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Constants.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"


//#include "llvm/Analysis/LoopInfo.h"
#include <algorithm>

using namespace llvm;

//static cl::opt<std::string> variable_to_process("var-name", cl::desc("Name of the variable for which scope,footprint,read/writes are analysed "), cl::value_desc("name of the variable/identifier string"), cl::Required);

namespace {
  struct SclaorEvol_Test : public ModulePass {
    static char ID;
    SclaorEvol_Test() : ModulePass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const override {
    //AU.addRequired<LoopSimplifyWrapperPass>();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
    AU.setPreservesAll();
  }
    
    bool runOnModule(Module &M) override {
        //llvm::Module M=Module();
        // legacy::PassManager PM;
        auto FPM = llvm::legacy::FunctionPassManager(&M);
        
        FPM.add(createPromoteMemoryToRegisterPass());
        FPM.add(createSCCPPass());
        FPM.add(createDeadCodeEliminationPass());
        FPM.add(createLoopSimplifyPass());
        //FPM.run();
        // running all the tranformation pases on each function in the translation unit
        for(auto& F:M)
        {
            FPM.run(F);
            dbgs()<< F.getName()<<"\n";
        }
       
        // dbgs()<<"***************************************************************************************************************\n\n";
        // dbgs()<<"DUMPING TRANSFORMED MODULE"<<"\n";
        // M.dump();
        // dbgs()<<"***************************************************************************************************************\n\n";
        
        //declaring data_structures
        SmallVector<llvm::Instruction *, 64> Instruc_float_vars;
        Function* main_func=nullptr;
        SmallVector<llvm::Loop*,4> Loop_nest_root;
        DenseMap<llvm::Loop*,SmallVector<llvm::Loop*>> Root_to_nested;
        SmallVector<Loop*> All_loops;
        DenseMap<Loop*,SmallVector<Instruction*>> All_loop_to_phi;
        DenseMap<Loop*,const SCEV*> loop_to_maxbackedge_takencount;
        DenseMap<Loop*,bool> loop_to_noninvariant_backedge;
        DenseMap<Loop*,unsigned long long > loop_to_total_count;
        unsigned long long total_flops_in_main=0UL;

        //# step1: determine floating-point operations in the translation unit 
        for(auto& F:M)
        {
          if(F.getName().lower() == "main") // since the kernel function has been inlined in main via "always_inline" 
          {
                main_func=&F;
                  for (auto& BB:F)
                {
                    for(auto& I:BB)
                    {
                        //instruc_a_float=false;
                        if(isa<llvm::AllocaInst>(&I)==false and isa<llvm::LoadInst>(&I)==false)
                        {
                            if(isa<llvm::BinaryOperator>(&I)==true)
                            {
                                auto inst_type=I.getType();
                                if(inst_type->isBFloatTy()==true or inst_type->isFloatTy()==true or inst_type->isDoubleTy()==true or inst_type->isX86_FP80Ty()==true or inst_type->isFP128Ty()==true or inst_type->isFloatingPointTy()==true)
                            {
                                //instruc_a_float=true;
                                Instruc_float_vars.push_back(&I);
                            }

                            }
                            else
                            if(isa<llvm::FCmpInst>(&I)==true)
                            {
                                Instruc_float_vars.push_back(&I);
                            }
                            else
                            if(isa<llvm::UIToFPInst>(&I)==true or isa<llvm::TruncInst>(&I)==true or isa<llvm::ZExtInst>(&I)==true or isa<llvm::FPExtInst>(&I)==true or isa<llvm::FPToSIInst>(&I)==true or isa<llvm::FPToUIInst>(&I)==true or isa<llvm::FPTruncInst>(&I)==true or isa<llvm::SIToFPInst>(&I)==true or isa<llvm::UIToFPInst>(&I)==true)
                            {
                                Instruc_float_vars.push_back(&I);
                            }
                            //float_vars.push_back(AI);
                            //dbgs()<<"Float/double var:"<<"\n";
                            //AI->dump();
                            else
                            if(auto call=dyn_cast<llvm::CallInst>(&I))
                            {
                                //auto t=I.getType();
                                auto t=call->getCalledFunction();

                                // if(t->isBFloatTy()==true or t->isFloatTy()==true or t->isDoubleTy()==true or t->isX86_FP80Ty()==true or t->isFP128Ty()==true or t->isFloatingPointTy()==true)

                                //     {
                                //         Instruc_float_vars.push_back(&I);
                                //     }    

                                // to be on safer side each intrinsic is assumed to contribute 2 floating point operation     
                                if(t->getName().startswith("llvm.fmuladd")||
                                t->getName().startswith("llvm.smax")||
                                t->getName().startswith("llvm.smin") ||
                                t->getName().startswith("llvm.umax") ||
                                t->getName().startswith("llvm.umin") ||
                                t->getName().startswith("llvm.sqrt") ||
                                t->getName().startswith("llvm.powi") ||
                                t->getName().startswith("llvm.sin") ||
                                t->getName().startswith("llvm.cos") ||
                                t->getName().startswith("llvm.pow") ||
                                t->getName().startswith("llvm.exp") ||
                                t->getName().startswith("llvm.exp2") ||
                                t->getName().startswith("llvm.log") ||
                                t->getName().startswith("llvm.log2") ||
                                t->getName().startswith("llvm.log10") ||
                                t->getName().startswith("llvm.fma")||
                                t->getName().startswith("llvm.fabs") ||
                                t->getName().startswith("llvm.fmuladd")||
                                t->getName().startswith("llvm.fabs") ||
                                t->getName().startswith("llvm.minnum") ||
                                t->getName().startswith("llvm.maxnum") ||
                                t->getName().startswith("llvm.minimum") ||
                                t->getName().startswith("llvm.maximum") ||
                                t->getName().startswith("llvm.copysign") ||
                                t->getName().startswith("llvm.floor") ||
                                t->getName().startswith("llvm.ceil") ||
                                t->getName().startswith("llvm.trunc") ||
                                t->getName().startswith("llvm.rint") ||
                                t->getName().startswith("llvm.nearbyint") ||
                                t->getName().startswith("llvm.round") ||
                                t->getName().startswith("llvm.roundeven") ||
                                t->getName().startswith("llvm.lround") ||
                                t->getName().startswith("llvm.llround") ||
                                t->getName().startswith("llvm.lrint") ||
                                t->getName().startswith("llvm.llrint") ||
                                t->getName().startswith("llvm.convert.to.fp16") ||
                                t->getName().startswith("llvm.convert.from.fp16") ||
                                t->getName().startswith("llvm.fptoui.sat") ||
                                t->getName().startswith("llvm.fptosi.sat") ||
                                t->getName().startswith("llvm.bitreverse") ||
                                t->getName().startswith("llvm.bswap") ||
                                t->getName().startswith("llvm.ctpop") ||
                                t->getName().startswith("llvm.ctlz") ||
                                t->getName().startswith("llvm.cttz") ||
                                t->getName().startswith("llvm.fshl") ||
                                t->getName().startswith("llvm.fshr") ||
                                t->getName().startswith("llvm.sadd.with.overflow") ||
                                t->getName().startswith("llvm.uadd.with.overflow") ||
                                t->getName().startswith("llvm.ssub.with.overflow") ||
                                t->getName().startswith("llvm.usub.with.overflow") ||
                                t->getName().startswith("llvm.smul.with.overflow") ||
                                t->getName().startswith("llvm.umul.with.overflow") ||
                                t->getName().startswith("llvm.sadd.sat") ||
                                t->getName().startswith("llvm.uadd.sat") ||
                                t->getName().startswith("llvm.ssub.sat") ||
                                t->getName().startswith("llvm.usub.sat") ||
                                t->getName().startswith("llvm.sshl.sat") ||
                                t->getName().startswith("llvm.ushl.sat") ||
                                t->getName().startswith("llvm.smul.fix") ||
                                t->getName().startswith("llvm.umul.fix") ||
                                t->getName().startswith("llvm.smul.fix.sat") ||
                                t->getName().startswith("llvm.umul.fix.sat") ||
                                t->getName().startswith("llvm.sdiv.fix") ||
                                t->getName().startswith("llvm.udiv.fix") ||
                                t->getName().startswith("llvm.sdiv.fix.sat") ||
                                t->getName().startswith("llvm.udiv.fix.sat")
                                )                         
                                {
                                    dbgs()<<"!@!!#!###$#$#$$! ";
                                    I.dump(); 
                                    //just to be safe w.r.t estimation one fmuladd is considered as two floating point ops
                                    Instruc_float_vars.push_back(&I);
                                    Instruc_float_vars.push_back(&I);
                                }

                                        }

                        }
                    }
                }
          }
          
          }

          // for(auto inst_itr:Instruc_float_vars)
          // {
          //   inst_itr->dump();
          //   dbgs()<<"\n";
          // }
        
        // checking wether loop simplification and amenability to scalor-evolution has happend properly        
        //assuming that loop simplify pass has been run before executing our pass
        
        //running all the Analysis_Pass on function "main"
        //********************************************************************************************************************************  
        auto &SE = getAnalysis<ScalarEvolutionWrapperPass>(*main_func).getSE();
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>(*main_func).getLoopInfo();
        //********************************************************************************************************************************


        //SE.print(std::stdout);   
        
        //get all the loop nests outermost loops in a vector
        for(Loop* L: LI)
        {
          if(!(L->getParentLoop()))
          {
            Loop_nest_root.push_back(L) ;
          }
        }

        //apply getInnerLoopsInPreorder() to get all child loops nested by these outermost loops

        for(auto* L: Loop_nest_root)
        {   
            Root_to_nested.insert(std::make_pair(L,SmallVector<Loop*,4>()));
            for(auto child_loop: L->getLoopsInPreorder())
            {
                Root_to_nested[L].push_back(child_loop);                
            }
            assert(!Root_to_nested[L].empty());
            Root_to_nested[L].erase(Root_to_nested[L].begin());


        }

        //store all teh loops in teh vector
        for(auto map_itr:Root_to_nested)
        {
            All_loops.push_back(map_itr.first);
            for(auto child_loop: map_itr.second)
            {
                All_loops.push_back(child_loop);
            }
        }    

       // get the phi instruction of all the loops from teh header block of each loop
       // this info will be stored in a densemap such taht key will be teh root/outermost loop of each loop nest

        for(auto* loop_itr:All_loops)
        {
            All_loop_to_phi.insert(std::make_pair(loop_itr,SmallVector<Instruction*,4>()));                
            auto current_loop=loop_itr;
            auto loop_header=current_loop->getHeader();
            auto phis_range=loop_header->phis();
            for(auto phi_itr=phis_range.begin(); phi_itr!=phis_range.end();phi_itr++)
            {
                All_loop_to_phi[loop_itr].push_back(&(*phi_itr));
            }
        }

        dbgs()<<"\n"<<"******* size of All_loops list ********* "<<All_loops.size()<<"\n";
                   
        for(auto map_itr:All_loop_to_phi)
        {
            // for(auto phi: map_itr.second)
            // {
            //     dbgs()<<"Loop is"<<"\n\n";
            //     map_itr.first->dump();
            //     dbgs()<<"changing phi node to SCEV Expr"<<"\n\n";
            //     auto scev_phi=SE.getSCEV(phi);
                //dbgs()<<"SCEV Expr"<<"\n\n";
                //auto temp=map_itr.first->getInductionVariable(SE);
                //if(!temp)
                //dbgs()<<"!!!! nullptr !!!!"<<"\n\n";

                //dbgs()<<" Is loop's backedge Invariant " <<"\n\n";
                //bool bool_invariant_back_edge=SE.hasLoopInvariantBackedgeTakenCount(map_itr.first);
                loop_to_noninvariant_backedge[map_itr.first]=SE.hasLoopInvariantBackedgeTakenCount(map_itr.first);                
                if(loop_to_noninvariant_backedge[map_itr.first])
                loop_to_maxbackedge_takencount[map_itr.first]=SE.getConstantMaxBackedgeTakenCount(map_itr.first);                
                else
                dbgs()<<" NOT OK to apply SE's backedge count "<<"\n\n";

                
                // dbgs()<<"Backedge count scev"<<"\n\n";
                // auto back_edge_scev=SE.getBackedgeTakenCount(map_itr.first);
                // back_edge_scev->dump();

                // dbgs()<<"MAX Backedge count scev"<<"\n\n";
                // auto max_back_edge_scev=SE.getConstantMaxBackedgeTakenCount(map_itr.first);
                // max_back_edge_scev->dump();    


                //scev_phi->dump();
                // dbgs()<<"SCEV Type"<<"\n\n";
                // scev_phi->getType()->dump();



            }
           
            dbgs()<<"************** Loop backedge invarince status ****************"<<"\n";
            for(auto map_itr:loop_to_noninvariant_backedge)
            {
                dbgs()<<map_itr.second<<"\n";
            }

            dbgs()<<"************** Loop max backedge taken count ****************"<<"\n";
            for(auto map_itr:loop_to_maxbackedge_takencount)
            {
                map_itr.second->dump();
                dbgs()<<"Unsigned 64 bit INT:"<<"\n";
                if(auto const_scev=dyn_cast<llvm::SCEVConstant>(map_itr.second))
                {
                    dbgs()<<const_scev->getValue()->getZExtValue()<<"\n";
                }
                //dbgs()<<map_itr.second->getValue();
                dbgs()<<"\n";
            }

           
            // Now Need to finds two things 1) the loop to which identified FLOP belongs to 
            // Depth if the corrsponding loop 

            for(auto loop_itr:All_loops)
            {
                loop_to_total_count[loop_itr]=1UL;
                auto parent_loop=loop_itr->getParentLoop();
                auto current_loop=loop_itr;
                auto temp=current_loop;
                if(!parent_loop)
                {
                        if(auto const_scev=dyn_cast<llvm::SCEVConstant>(loop_to_maxbackedge_takencount[current_loop]))                        
                            loop_to_total_count[current_loop]=const_scev->getValue()->getZExtValue();                       
                        
                }
                else
                {
                    while(parent_loop)
                    {
                        
                        if(auto const_scev=dyn_cast<llvm::SCEVConstant>(loop_to_maxbackedge_takencount[temp]))                        
                            loop_to_total_count[current_loop]*=const_scev->getValue()->getZExtValue();
                        
                        temp=parent_loop;
                        parent_loop=temp->getParentLoop();
                    }
                    //above loop will break before processing trip count for outermost loop . ex L1->L2->L3->L4->L5
                    // when temp will hold L1 , parent_loop=nullptr. hence the while will break
                    if(auto const_scev=dyn_cast<llvm::SCEVConstant>(loop_to_maxbackedge_takencount[temp]))
                    loop_to_total_count[current_loop]*=const_scev->getValue()->getZExtValue();
                }
            }

            dbgs()<<"\n ***** loops to total trip-count ***** \n";
            for(auto map_itr:loop_to_total_count)
            {
                dbgs()<<"--- Loop is ---\n";
                map_itr.first->dump();
                dbgs()<<"::: Trip -count is ::: \n"<<map_itr.second;                

            }


            for(auto flop_itr: Instruc_float_vars)
            {
                auto parent_bb=flop_itr->getParent();
                SmallVector<Loop*> present;
                unsigned long long flop_trip_count=0UL;
                for(auto loop_itr: All_loops)
                {
                    if(loop_itr->contains(parent_bb))
                    present.push_back(loop_itr);
                }
                for(auto pres_loop:present)
                {
                    flop_trip_count=flop_trip_count<loop_to_total_count[pres_loop]?loop_to_total_count[pres_loop]:flop_trip_count;
                    total_flops_in_main+=flop_trip_count;
                }

                
            }

            dbgs()<<"\n ****************** Total trip-count is ************************\n"<<total_flops_in_main;



        }
        
       
        // for(auto map_itr:Root_to_nested)
        // {
        //     dbgs()<< "Root loop is :"<<"\n";
        //     map_itr.first->dump();
        //     dbgs()<< "\n\n";
        //     dbgs()<< "important aspects for parent loop" <<"\n";
        //     dbgs()<< "geting induction variable phi instruction" <<"\n";
            
        //     //map_itr.first->getInductionVariable(SE)->dump();
        //     dbgs()<<"********* dumping all child loops ****************" <<"\n\n";
        //     for(auto child_loop:map_itr.second)
        //     {
        //         child_loop->dump();
        //         dbgs()<<"\n\n";
                
        //     }
            
        // }


       
        
       
        // for(auto map_itr:Root_to_nested)
        // {
        //     dbgs()<< "Root loop is :"<<"\n";
        //     map_itr.first->dump();
        //     dbgs()<< "\n\n";
        //     dbgs()<< "important aspects for parent loop" <<"\n";
        //     dbgs()<< "geting induction variable phi instruction" <<"\n";
            
        //     //map_itr.first->getInductionVariable(SE)->dump();
        //     dbgs()<<"********* dumping all child loops ****************" <<"\n\n";
        //     for(auto child_loop:map_itr.second)
        //     {
        //         child_loop->dump();
        //         dbgs()<<"\n\n";
                
        //     }
            
        // }


          

    

    
    };
}

char SclaorEvol_Test::ID = 0;
static RegisterPass<SclaorEvol_Test> X("SclaorEvol_Test", "testing Scalor evolution framework in llvm ");



