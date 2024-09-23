#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
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
#include <llvm/ADT/DenseMap.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/Casting.h>
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
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/Dominators.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/CodeGen/UnreachableBlockElim.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Analysis/LoopNestAnalysis.h"
#include "llvm/ADT/SetVector.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/Analysis/DomTreeUpdater.h"
#include "llvm/Analysis/InstructionSimplify.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DebugInfo.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IntrinsicInst.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/MDBuilder.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/Module.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include <map>
#include <optional>
#include "llvm/IR/Verifier.h"



//#include "llvm/Analysis/LoopInfo.h"
#include <algorithm>

using namespace llvm;

static cl::opt<int> num_clones("loop-partitions",
                          cl::desc("number of innermost loop clones"),
                          cl::init(3),
                          cl::value_desc("integer value >=0"));

namespace {
  struct LoopSplitting : public FunctionPass {
    static char ID;
    LoopSplitting() : FunctionPass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const override {
    //AU.addRequired<LoopSimplifyWrapperPass>();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
    AU.addRequired<DominatorTreeWrapperPass>();
    AU.setPreservesAll();
  }

  llvm::Instruction* resolve_induction_bound()
  {}
    
    bool runOnFunction(Function &F) override {
        //llvm::Module M=Module();
        // legacy::PassManager PM;
        dbgs()<<":::::::::::"<<"\n";
        dbgs()<<num_clones.getValue();
        int clones_num=num_clones.getValue();
        //F.viewCFGOnly();
       auto FPM = llvm::legacy::FunctionPassManager(F.getParent());
       auto FPM3 = llvm::legacy::FunctionPassManager(F.getParent());
       auto FPM4 = llvm::legacy::FunctionPassManager(F.getParent());
        //FPM.add(createPromoteMemoryToRegisterPass());
        FPM.add(createLoopSimplifyPass());
        
        FPM3.add(createPromoteMemoryToRegisterPass());

        FPM4.add(createBreakCriticalEdgesPass());
        //FPM3.run(F);
      auto FPM2=llvm::legacy::FunctionPassManager(F.getParent());
      FPM2.add(createCFGSimplificationPass());  
      //FPM3.run(F);
      FPM.run(F);
      //F.viewCFG();
      
      unsigned int num_clones=3;
      //auto ub= llvm::UnreachableBlockElimPass();
        // PM.add(new CountFlop());
        //SmallVector<llvm::AllocaInst*, 4> float_vars;
        // for (auto& F:M)
        // {
        dbgs()<<"\n\n***************************** Function is :"<<F.getName()<<"****************************************"<<"\n";
        //F.viewCFG();

        // detect inner most loop of every loopnest
        SmallVector<llvm::Loop*,4> loop_nest_inner_most;
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        DominatorTree &DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();
        //DT.viewGraph();
        std::vector<Loop *> LoopNests;
        for (Loop *L : LI) 
         {
            dbgs()<<"^^^^^^";
            L->dump();
            SmallVector<llvm::Loop*>temp;
            //auto sub_loop_vec=L->getSubLoopsVector();
            L->getInnerLoopsInPreorder(*L,temp);
            
            for(auto loop=temp.begin(); loop!=temp.end(); loop++)
            {
                //dbgs()<<"%%^%^^^^^^^"<<"\n";
                //(*loop)->dump();
            if((*loop)->isInnermost()==true)  
            {
                loop_nest_inner_most.push_back((*loop));
                dbgs()<<"##############"<<"\n";
                (*loop)->dump();
            }
            }
            if(temp.size()==0)
            {
              dbgs()<<"()()()(()())"<<"\n";
              loop_nest_inner_most.push_back(L);
              L->dump();
              L->getLoopPreheader()->dump();
            }

            
        
        }

        // now we have complete list of innermost loops
        dbgs()<<"%%%%%%%%"<<loop_nest_inner_most.size()<<"\n";
        
        //F.viewCFG();
        auto veri=llvm::verifyFunction(F);
        dbgs()<<"////////////// "<<veri<<"\n";
        if(veri==false)
        {
            dbgs()<<"!!!!!!!!!!!!!!!!!"<<"\n";
        }
        for(auto inner_itr=loop_nest_inner_most.begin();inner_itr!=loop_nest_inner_most.end();inner_itr++)
        {
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            DominatorTree &DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            auto currentloop=(*inner_itr);
            auto parent=currentloop->getParentLoop();
            if(parent)
            {          
             
            llvm:: BasicBlock* old_curr_exit_block=nullptr;
            llvm:: Loop* old_last_innermost=nullptr;
            llvm::Value* loop_initial_bound=nullptr;
            llvm::Value* loop_final_bound=nullptr;

        for(int xx=0;xx<clones_num-1;xx++)
            {
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
            DominatorTree &DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            DT.recalculate(F);

            llvm::Loop* last_innermost=nullptr;
            
            for(auto loop:LI)
            {
                if(loop->getLoopDepth()==1)
                {
                    for(auto child:loop->getLoopsInPreorder())
                    {
                        if(child->isInnermost() && child->getParentLoop()==parent)
                        {
                            last_innermost=child;
                            dbgs()<<"~~~~~~~~~~~~~~~~"<<"\n";
                            last_innermost->getExitBlock()->dump();
                        }
                    }
                }
            }
            
            ValueToValueMapTy m,m1;
            std::string suffx="clone"+std::to_string(xx); 

            //auto list1=SmallVectorImpl<Loop*>(4);
            SmallVector<BasicBlock*, 8> list1;
            currentloop=last_innermost;
            auto curr_exit_block=currentloop->getExitBlock();
            auto cloned_curr_exit_block=llvm::CloneBasicBlock(curr_exit_block, m1,suffx);
            cloned_curr_exit_block->insertInto(&F,parent->getLoopLatch());
            //DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();
            

            //F.viewCFG();
            //cloned_curr_exit_block->setName(llvm::Twine("exit"+suffx));
            dbgs()<<"**************** for xx ="<<xx<<"\n";
            
            curr_exit_block->dump();
            dbgs()<<"\n********** cloned"<<"\n";
            cloned_curr_exit_block->dump();
            dbgs()<<"\n"<<cloned_curr_exit_block->getName();

            auto cloned_curr_exit_bb_term=cloned_curr_exit_block->getTerminator();
            
       // std::string suffx="clone"+std::to_string(xx);    
        llvm::Instruction* cur_exit_term=nullptr;
        
        dbgs()<<"curentttttttttt"<<"\n";
        currentloop->getHeader()->dump();
        currentloop->getExitBlock()->dump();

        if(xx==0)
        {
        //  for(auto inst:currentloop->getHeader())
        //  {

        //  }  
           cloneLoopWithPreheader(parent->getLoopLatch(), currentloop->getExitBlock(), currentloop, m, suffx, &LI, &DT, list1);
            cur_exit_term=currentloop->getExitBlock()->getTerminator();
        }
        else
        {
            dbgs()<<"OLDDDDDDDDDDDDDDDDDDD"<<"\n";
            old_last_innermost->getExitBlock()->dump();
             dbgs()<<"OLDDDDDDDDDDDDDDDDDDD1111111"<<"\n";
           old_curr_exit_block->dump();
           currentloop->getExitBlock()->dump();
            cloneLoopWithPreheader(parent->getLoopLatch(), currentloop->getExitBlock(), currentloop, m, suffx, &LI, &DT, list1);
           

           cur_exit_term=currentloop->getExitBlock()->getTerminator();

        }
           //cloneLoopWithPreheader(parent->getLoopLatch(), currentloop->getExitBlock(), currentloop, m, "clone", &LI, &DT, list1);
           auto newph=list1.front();
           auto newlatch=list1.back();
           dbgs()<<"ULLLLLL"<<"\n";
           list1.back()->dump();
           auto newhead=list1[1];
           auto newph_term=newph->getTerminator();
           auto newlatch_term=newlatch->getTerminator();
           auto newhead_term=newhead->getTerminator();
           //auto cur_exit_term=currentloop->getExitBlock()->getTerminator();
            //cur_exit_term=old_curr_exit_block->getTerminator();
            dbgs()<<"@@@@@@@@@00000000000";
           cur_exit_term->dump();
           if(auto bra=dyn_cast<llvm::BranchInst>(cur_exit_term))
           {
                if (bra->isUnconditional())
                {
                    dbgs()<<"@@@@@@@@@1";
                    bra->setSuccessor(0, newph);
                    if(auto bra1=dyn_cast<llvm::BranchInst>(newph_term))
                    {
                        if(bra1->isUnconditional())
                        {
                            bra1->setSuccessor(0, newhead);
                            dbgs()<<"@@@@@@@@@2";
                            if(auto bra2=dyn_cast<llvm::BranchInst>(newhead_term))
                            {
                                if(bra2->isConditional())
                                {
                                    dbgs()<<"@@@@@@@@@3";
                                     bra2->setSuccessor(0, list1[2]);
                                     // here insert a exit_block


                                        bra2->setSuccessor(1, cloned_curr_exit_block);
                                        //bra2->setSuccessor(1, parent->getLoopLatch());
                                        if(auto bra_exit=dyn_cast<llvm::BranchInst>(cloned_curr_exit_bb_term))
                                        {
                                            if(bra_exit->isUnconditional())
                                            {
                                                bra_exit->setSuccessor(0,parent->getLoopLatch());
                                                dbgs()<<"@@!!!@@@!!!2222222222222222222" <<"\n";
                                                cloned_curr_exit_block->dump();
                                                //bra_exit->dump();
                                            }
                                        }

                                    //set predecessors also for cloned loop header
                                    //get the phi instructions
                                    for(auto &inst : (*newhead))
                                    {
                                        dbgs()<<"\n#####"<<inst.getName()<<"\n";
                                        if(auto phi=dyn_cast<llvm::PHINode>(&inst))
                                        {
                                            phi->setIncomingBlock(0, newph);
                                            phi->setIncomingBlock(1, newlatch);

                                        }

                                    }    
                                
                                    llvm::BasicBlock* last_body_bb=nullptr;
                                    for(auto newbb=list1.begin();newbb!=list1.end();)
                                    {
                                        dbgs()<<"@@@@@@@@@4";
                                        if(*(newbb+1)==newlatch)
                                        {
                                            dbgs()<<"@@@@@@@@@6";
                                                last_body_bb=(*newbb);
                                                auto last_body_bb_term=last_body_bb->getTerminator();
                                                if(auto bra4=dyn_cast<llvm::BranchInst>(last_body_bb_term))
                                                {
                                                    if(bra4->isUnconditional())
                                                    {
                                                        bra4->setSuccessor(0, newlatch);
                                                        if(auto bra5=dyn_cast<llvm::BranchInst>(newlatch_term))
                                                        {
                                                            if(bra5->isUnconditional())
                                                            {
                                                                bra5->setSuccessor(0, newhead);
                                                            }
                                                        }
                                                        
                                                    }
                                                }
                                                break;
                                        }
                                        
                                        if ((*newbb)!=newhead && (*newbb)!=newph && (*newbb) !=newlatch)
                                        {
                                            (*newbb)->dump();
                                            (*(newbb+1))->dump();
                                            dbgs()<<"@@@@@@@@@5";
                                            auto newbb_term=(*newbb)->getTerminator();
                                            if(auto bra3=dyn_cast<llvm::BranchInst>(newbb_term))
                                            {
                                                if(bra3->isUnconditional())
                                                {
                                                    if(newbb+1!=list1.end())
                                                    bra3->setSuccessor(0, (*newbb+1));
                                                }
                                            }
                                        }
                                        newbb++;
                                    }

                                }
                            }
                        }

                    }               
               
               
                }
                  

           }

           dbgs()<<"SUCCCCCCCCCCCCCCC"<<"\n";
           cur_exit_term->getParent()->getUniqueSuccessor()->dump();
            dbgs()<<"\n"<<cur_exit_term->getParent()->getName();



        
        //    LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        // DominatorTree &DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();

        //    //get all the instruction in the original loop basic blocks which are getting used in the cloned loop
        //    SmallVector<llvm::Instruction*> used_in_clone;
        //    auto curr_loop_bb=currentloop->getBlocksVector();
        //    DenseMap<llvm::Instruction*, llvm::Instruction*> orig_inst_clone_users;
          unsigned int len1=0;
          auto new_ph_pred_term=newph_term->getPrevNonDebugInstruction();
           while(true)
        {
            LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        DominatorTree &DT=getAnalysis<DominatorTreeWrapperPass>().getDomTree();

           //get all the instruction in the original loop basic blocks which are getting used in the cloned loop
           SmallVector<llvm::Instruction*> used_in_clone;
           auto curr_loop_bb=currentloop->getBlocksVector();
           DenseMap<llvm::Instruction*, llvm::Instruction*> orig_inst_clone_users;
           len1=used_in_clone.size(); 
           dbgs()<<"len1 "<<len1<<"\n";
           for(auto bb:curr_loop_bb)
           {
            dbgs()<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<"\n"; 
            for(auto& inst: *bb)
            {
                for(auto us:inst.users())
                {
                    if(auto inst_us=dyn_cast<llvm::Instruction>(us))
                    {
                        auto bb_us=inst_us->getParent();
                        //check wether this basic block lies in cloned loop or not
                        for(auto clone_bb:list1)
                        {
                            if(bb_us==clone_bb)
                            {
                                if(DT.dominates(inst.getParent(),bb_us)==false)
                                {
                                used_in_clone.push_back(&inst);
                                orig_inst_clone_users[&inst]=inst_us;
                                }
                            }
                        }
                    }
                }
            }
           }
           

           if(used_in_clone.size()==0)
           {
            dbgs()<<"DOMINATION STABILIZED!!!!!!!!!!!!!!!!"<<"\n";
           break;
           }
        
           dbgs()<<"11111111111111111AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<"\n"; 

           DenseMap<llvm::Instruction*, llvm::Instruction*> orig_to_clone_inst; 
           for(auto inst: used_in_clone)
           {
            inst->dump();
           }
           // need to clone these instructions and put them in the cloned loop preheader just before the terminator instruction
           
           for(auto inst: used_in_clone)
           {
            auto temp=inst->clone();
            orig_to_clone_inst[inst]=temp;
            
            //newph->getInstList().insertAfter(new_ph_pred_term, temp)
            temp->insertAfter(new_ph_pred_term);

           }

           for(auto itr=orig_inst_clone_users.begin(); itr!=orig_inst_clone_users.end();itr++)
           {
            auto orig=itr->first;
            auto usr=itr->second;
            auto op_list=usr->getOperandList();
            int num_op=usr->getNumOperands();
            for(unsigned int z=0;z<num_op;z++)
            {
                auto op_pos=usr->getOperand(z);
                if(auto op_inst=dyn_cast<llvm::Instruction>(op_pos))
                {
                    if(op_inst==orig)
                    {
                        usr->setOperand(z, orig_to_clone_inst[orig]);
                    }
                }

            }
            // for(auto op:op_list)
            // {
                
            // }
           }
        }
        old_last_innermost=currentloop;
        old_curr_exit_block=currentloop->getExitBlock();
            

            // else // if xx>0 i.e one loop  has been cloned
            //  {
            
            // }

           
           

           
            


           
           //FPM3.run(F);
          // FPM.run(F);
           //FPM2.run(F);
           //FPM3.run(F);
           //FPM4.run(F);
           //F.viewCFG();
            //DT.viewGraph();


           
        //    for(auto b:list1)
        //    {
        //     b->dump();
        //    }

           //FPM2.run(F);
           //F.viewCFG();
        //DT.viewGraph();
           auto veri=llvm::verifyFunction(F);
        dbgs()<<"////////////// "<<veri<<"\n";

            }

            // now again go thrugh all cloned parallel loops and change the bounds


            }
        }

     F.viewCFG();
        DT.viewGraph();   
    }
    
  };
}
char LoopSplitting::ID = 0;
static RegisterPass<LoopSplitting> X("LoopSplitting", "To do Naive Index set spliting transformation ");

