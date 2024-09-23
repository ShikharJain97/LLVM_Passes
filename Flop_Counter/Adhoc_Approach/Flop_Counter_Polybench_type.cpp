// THe current state of this pass has been since end of 3rd sem. 
// This pass is good POC for static FLOP estimation 
// This pass is working for some polybench kernels
// This pass has multiple ad-hoc approaches which is needed to be "cleaned"/generalized using as much already present LLVM's analysis-pass info as possible


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


//#include "llvm/Analysis/LoopInfo.h"
#include <algorithm>

using namespace llvm;

//static cl::opt<std::string> variable_to_process("var-name", cl::desc("Name of the variable for which scope,footprint,read/writes are analysed "), cl::value_desc("name of the variable/identifier string"), cl::Required);

namespace {
  struct CountFlop : public FunctionPass {
    static char ID;
    CountFlop() : FunctionPass(ID) {}

    void getAnalysisUsage(AnalysisUsage &AU) const override {
    //AU.addRequired<LoopSimplifyWrapperPass>();
    AU.addRequired<LoopInfoWrapperPass>();
    AU.addRequired<ScalarEvolutionWrapperPass>();
    AU.setPreservesAll();
  }
    
    bool runOnFunction(Function &F) override {
        //llvm::Module M=Module();
        // legacy::PassManager PM;
       auto FPM = llvm::legacy::FunctionPassManager(F.getParent());
        FPM.add(createPromoteMemoryToRegisterPass());
        FPM.add(createLoopSimplifyPass());
        FPM.run(F);
        // PM.add(new CountFlop());
        //SmallVector<llvm::AllocaInst*, 4> float_vars;
        // for (auto& F:M)
        // {
        dbgs()<<"\n\n***************************** Function is :"<<F.getName()<<"****************************************"<<"\n";
        DenseMap<llvm::Function*,SmallVector<llvm::Instruction *, 64>> func_to_float_instruc;
        SmallVector<llvm::Instruction *, 64> Instruc_float_vars;
        DenseMap<llvm::Loop*,SmallVector<llvm::Loop*>> inorder_loop_nest;
        DenseMap<llvm::Loop*,SmallVector<std::string,5>> loop_bounds_dict;
        DenseMap<llvm::Loop*,SmallVector<llvm::BasicBlock*,16>>loop_bb_dict;
        DenseMap<llvm::Instruction*,int >float_inst_trip_count;
        long long int total_trip_count=0;
        //bool instruc_a_float=false;

        

        // a instrn will be floating point if it involves a floating/double variabel,constant , another floating/doubke intrsn as a operand
        //it could also be possible that the actual result of some instrn is floating point but by sone implicit or explicit cast that result is changed to floating point hence that will also be termed as floating point.

        //Step:1 get all the single precison or double preciosn floating point variables
        // use type of alloca for this
        
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
                    if(isa<llvm::FPExtInst>(&I)==true or isa<llvm::FPToSIInst>(&I)==true or isa<llvm::FPToUIInst>(&I)==true or isa<llvm::FPTruncInst>(&I)==true or isa<llvm::SIToFPInst>(&I)==true or isa<llvm::UIToFPInst>(&I)==true)
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

                        if(t->getName().startswith("llvm.fmuladd"))
                        {
                            dbgs()<<"!@!!#!###$#$#$$! ";
                            I.dump(); 
                            Instruc_float_vars.push_back(&I);
                        }

                                }

                }
            }
        }
        

        // for(auto& F:M)
        // {      
        
        //DenseMap<llvm::Loop*,SmallVector<llvm::Loop*>> inorder_loop_nest;
        //assuming that loop simplify pass has been run before executing our pass
        auto &SE = getAnalysis<ScalarEvolutionWrapperPass>().getSE();
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        std::vector<Loop *> LoopNests;
        for (Loop *L : LI) {
        if (L->getLoopDepth() == 1) {
            LoopNests.push_back(L);
             dbgs()<<"\n\n&&&"<<"\n";            
            //L->dump();
            // dbgs()<<"!!!!"<<"\n";
            // L->dumpVerbose();
            // dbgs()<<"***&&"<<L->getName();
            SmallVector<llvm::Loop*,4> trav;
            std::pair<llvm::Loop*,llvm::SmallVector<llvm::Loop*>> loop_to_inorder=std::make_pair(L,trav);
            inorder_loop_nest.insert(loop_to_inorder);
            trav=L->getLoopsInPreorder();
            dbgs()<<"travvvvvvvvvvvv"<<trav.size();
            for(auto x=trav.begin();x!=trav.end();x++)
            {
                inorder_loop_nest.find(L)->second.push_back(*x);
            }
            
            for(auto itr: trav)
            {
                dbgs()<<"$$$$"<<"\n";
                dbgs()<<"`````````````````````````` "<<itr->getStartLoc().getLine()<<"\n";
                //itr->dump();
                dbgs()<<"$$$$"<<"\n";
                //dbgs()<<"****"<<"\n";
                auto parent=itr->getParentLoop();
                if (parent)
                {
                    if(loop_bounds_dict.find(parent)==loop_bounds_dict.end())
                    {
                    SmallVector<std::string,5> bounds_list;    
                    dbgs()<<"\n212121212 "<<bounds_list.size()<<"\n";
                    std::pair<llvm::Loop*,llvm::SmallVector<std::string,5>> loop_to_bounds=std::make_pair(parent,bounds_list);
                    loop_bounds_dict.insert(loop_to_bounds);
                    
                    }
                    //parent->dump();
                    //dbgs()<<"!!!"<<parent->getName()<<"\n";
                    // auto loop_info_struct=parent->getBounds(SE);
                    // auto lulu=loop_info_struct.getPointer();
                    // auto intial_val=lulu->getDirection();
                    // getInitialIVValue();
                    // llvm::Instruction& step_instruc=loop_info_struct.getPointer()->getStepInst();
                    // auto step_val=loop_info_struct.getPointer()->getStepValue();
                    // llvm::Value& final_val=loop_info_struct.getPointer()->getFinalIVValue();
                    // dbgs()<<"&*&*&&"<<parent->getNumBackEdges();
                    // dbgs()<<"&*&*&& :";
                    // parent->getHeader()->dump();
                    // dbgs()<<"%%%%"<<"\n";
                    // parent->getHeader()->getTerminator()->dump();
                    // //parent->getHeader()->getTerminator()->get
                    // dbgs()<<"\n";
                    // dbgs()<<"&*&*&& ::"; 
                    // parent->getLoopPreheader()->dump();
                    // dbgs()<<"\n"; 
                    // dbgs()<<"&*&*&& ::"; 
                    // parent->getLoopLatch()->dump();
                    // dbgs()<<"\n";            
                    //get the cmp instrn from the header of the loop and thus get the upper bound of the loop
                    // this cmp instruction(result) will be used in the branch instruc to take a jump
                    auto loop_header=parent->getHeader();
                    auto loop_header_term=loop_header->getTerminator();
                    llvm::Value* upper_bound=nullptr;
                    long long int ub=0;
                    llvm::Value* induction_variable=nullptr; 
                    llvm::Value* lower_bound=nullptr;
                    long long int lb=0;
                    //auto loop_header_terminator_operands=->getOperandList();
                    for (auto& I: *(loop_header))
                    {
                     if(isa<llvm::CmpInst>(I)==true)
                     {
                            for(auto op=loop_header_term->op_begin();op!=loop_header_term->op_end();op++)
                            {
                                if((*op).get()==(&I))
                                {
                                       // get the 
                                       //dbgs()<<"{{{}}}"<<"\n";
                                       upper_bound=I.getOperand(1);
                                       auto temp=I.getOperand(0);
                                       if(auto int_const=dyn_cast<llvm::ConstantInt>(upper_bound))
                                       {
                                        ub=int_const->getSExtValue();
                                        //dbgs()<<ub;
                                       }
                                       if(auto induc=dyn_cast<llvm::LoadInst>(temp))
                                       {
                                        induction_variable=induc->getPointerOperand();
                                        //dbgs()<<"oioi "<<"\n";
                                        //induction_variable->dump();
                                        //dbgs()<<"oioi "<<"\n";
                                       }

                                       break; 
                                }
                            }
                     }   
                    }

                    //process loop preheader and get initial bounds on induction variable
                    auto loop_preheader=parent->getLoopPreheader();
                    for (auto instruc = loop_preheader->rbegin();  instruc!= loop_preheader->rend(); instruc++) {
                     // do something with instruction *I
                     if(isa<llvm::StoreInst>(*instruc))
                     {
                        //dbgs()<<"aaaaaa"<<"\n";
                        if(instruc->getOperand(1)==induction_variable)
                        {
                            lower_bound=instruc->getOperand(0);
                            if(auto int_const=dyn_cast<llvm::ConstantInt>(lower_bound))
                            {
                                   lb=int_const->getSExtValue(); 
                            }
                        break;
                        }
                     }
                            }

                    //process loop's latch block to get step size
                    auto loop_latch=parent->getLoopLatch();
                    llvm::Value* step_inst=nullptr;
                    std::string opcode="";
                    long long int step_size=0;
                    
                    for(auto& instruc:(*loop_latch))
                    {
                        if(isa<llvm::LoadInst>(*(&instruc)))
                        {
                            //dbgs()<<"!~~~!"<<"\n";
                            //instruc.getOperand(0)->dump();
                            if(instruc.getOperand(0)==induction_variable)
                            {
                                for(auto arithm : instruc.users())
                                {
                                    if(isa<llvm::BinaryOperator>(arithm)==true)
                                    {
                                        //dbgs()<<"~~~"<<"\n";
                                        //arithm->dump();                                        
                                        //dbgs()<<"~~~"<<"\n";
                                        step_inst=arithm;
                                        if(auto arithm_instruc=dyn_cast<llvm::Instruction>(arithm))
                                        {
                                            opcode=std::string(arithm_instruc->getOpcodeName());
                                            auto step_temp=arithm->getOperand(1);
                                            if(auto int_step=dyn_cast<llvm::ConstantInt>(step_temp))
                                    {
                                        step_size=int_step->getSExtValue();

                                        }
                                        }
                                    }
                                }
                            }
                        }
                    }



                     dbgs()<<" loop's intail val, step size , opcode_step, final_val are "<<lb<<" "<<step_size<<" "<<opcode<<ub<<"\n";       
                    if(loop_bounds_dict.find(parent)!=loop_bounds_dict.end() && loop_bounds_dict.find(parent)->second.size()==0)
                    {
                      //dbgs()<<"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"<<"\n";  
                      
                      
                    loop_bounds_dict.find(parent)->second.push_back(std::to_string(lb));
                    loop_bounds_dict.find(parent)->second.push_back(std::to_string(step_size));
                    loop_bounds_dict.find(parent)->second.push_back(opcode);
                    loop_bounds_dict.find(parent)->second.push_back(std::to_string(ub));
                    loop_bounds_dict.find(parent)->second.push_back(std::to_string(0));
                   // dbgs()<<"\nXXXXXXXXXXXXX"<<loop_bounds_dict.find(parent)->second.size()<<"\n";
                    }




                    // if(intial_val)
                    // {
                    // dbgs()<<"Loop induction intial value"<<" :";                    
                    // intial_val.dump();
                    // dbgs()<<"\n";
                    // }
                    // if(step_instruc)
                    // {
                    // dbgs()<<"Loop induction step decider instruction"<<" :";
                    // step_instruc.dump();
                    // dbgs()<<"\n";
                    // }
                    // if(step_val)
                    // {
                    //  dbgs()<<"Loop induction step value"<<" :";
                    // step_val->dump();
                    // dbgs()<<"\n";   
                    // }
                    // if(final_val)
                    // {
                    //  dbgs()<<"Loop induction final value"<<" :";
                    // final_val.dump();
                    // dbgs()<<"\n";
                    // }

                    
                    
                    
                }
                if(!parent || itr)
                {
                dbgs()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~loop has no parent-loop"<<"\n";
                //itr->dump();
                if(loop_bounds_dict.find(itr)==loop_bounds_dict.end())
                    {
                    SmallVector<std::string,5> bounds_list;    
                    dbgs()<<"\n212121212 "<<bounds_list.size()<<"\n";
                    std::pair<llvm::Loop*,llvm::SmallVector<std::string,5>> loop_to_bounds=std::make_pair(itr,bounds_list);
                    loop_bounds_dict.insert(loop_to_bounds);
                    }

                auto loop_header=itr->getHeader();
                    auto loop_header_term=loop_header->getTerminator();
                    llvm::Value* upper_bound=nullptr;
                    long long int ub=0;
                    llvm::Value* induction_variable=nullptr; 
                    llvm::Value* lower_bound=nullptr;
                    long long int lb=0;
                    //auto loop_header_terminator_operands=->getOperandList();
                    for (auto& I: *(loop_header))
                    {
                     if(isa<llvm::CmpInst>(I)==true)
                     {
                            for(auto op=loop_header_term->op_begin();op!=loop_header_term->op_end();op++)
                            {
                                if((*op).get()==(&I))
                                {
                                       // get the 
                                       //dbgs()<<"{{{}}}"<<"\n";
                                       upper_bound=I.getOperand(1);
                                       auto temp=I.getOperand(0);
                                       if(auto int_const=dyn_cast<llvm::ConstantInt>(upper_bound))
                                       {
                                        ub=int_const->getSExtValue();
                                        //dbgs()<<ub;
                                       }
                                       if(auto induc=dyn_cast<llvm::LoadInst>(temp))
                                       {
                                        induction_variable=induc->getPointerOperand();
                                        //dbgs()<<"oioi "<<"\n";
                                        //induction_variable->dump();
                                        //dbgs()<<"oioi "<<"\n";
                                       }

                                       break; 
                                }
                            }
                     }   
                    }

                    //process loop preheader and get initial bounds on induction variable
                    auto loop_preheader=itr->getLoopPreheader();
                    for (auto instruc = loop_preheader->rbegin();  instruc!= loop_preheader->rend(); instruc++) {
                     // do something with instruction *I
                     if(isa<llvm::StoreInst>(*instruc))
                     {
                        //dbgs()<<"aaaaaa"<<"\n";
                        if(instruc->getOperand(1)==induction_variable)
                        {
                            lower_bound=instruc->getOperand(0);
                            if(auto int_const=dyn_cast<llvm::ConstantInt>(lower_bound))
                            {
                                   lb=int_const->getSExtValue(); 
                            }
                        break;
                        }
                     }
                            }

                    //process loop's latch block to get step size
                    auto loop_latch=itr->getLoopLatch();
                    llvm::Value* step_inst=nullptr;
                    std::string opcode="";
                    long long int step_size=0;
                    
                    for(auto& instruc:(*loop_latch))
                    {
                        if(isa<llvm::LoadInst>(*(&instruc)))
                        {
                            //dbgs()<<"!~~~!"<<"\n";
                            //instruc.getOperand(0)->dump();
                            if(instruc.getOperand(0)==induction_variable)
                            {
                                for(auto arithm : instruc.users())
                                {
                                    if(isa<llvm::BinaryOperator>(arithm)==true)
                                    {
                                        //dbgs()<<"~~~"<<"\n";
                                        //arithm->dump();                                        
                                        //dbgs()<<"~~~"<<"\n";
                                        step_inst=arithm;
                                        if(auto arithm_instruc=dyn_cast<llvm::Instruction>(arithm))
                                        {
                                            opcode=std::string(arithm_instruc->getOpcodeName());
                                            auto step_temp=arithm->getOperand(1);
                                            if(auto int_step=dyn_cast<llvm::ConstantInt>(step_temp))
                                    {
                                        step_size=int_step->getSExtValue();

                                        }
                                        }
                                    }
                                }
                            }
                        }
                    }



                     dbgs()<<" !!!!!!!!!!!!!!!!!!!!!!!!!loop's intail val, step size , opcode_step, final_val are "<<lb<<" "<<step_size<<" "<<opcode<<ub<<"\n";       
                    if(loop_bounds_dict.find(itr)!=loop_bounds_dict.end() && loop_bounds_dict.find(itr)->second.size()==0)
                    {
                    dbgs()<<"QQQQQQQQQQQQQQQQQQQQQQQ"<<"\n";    
                    loop_bounds_dict.find(itr)->second.push_back(std::to_string(lb));
                    loop_bounds_dict.find(itr)->second.push_back(std::to_string(step_size));
                    loop_bounds_dict.find(itr)->second.push_back(opcode);
                    loop_bounds_dict.find(itr)->second.push_back(std::to_string(ub));
                    loop_bounds_dict.find(itr)->second.push_back(std::to_string(0)); 
                    dbgs()<<"\nGGGGGGGGG"<<loop_bounds_dict.find(itr)->second.size()<<"\n";
                    

                    }







                dbgs()<<"^^^^^^^^^^^^^\n";
                }
            }
         }
        }
        dbgs()<<"\nZZZZZZZZZZZZZZZZZZ "<<loop_bounds_dict.size()<<"\n";
        for(auto dict_itr=loop_bounds_dict.begin();dict_itr!=loop_bounds_dict.end();dict_itr++)
        {
            //dbgs()<<"~!~@~@@"<<dict_itr.second[0];
            //dict_itr.second.push_back(std::to_string(0));
            long long int temp_trip_count=0;
            int lb=std::stoi(dict_itr->second[0]);
            int step_size=std::stoi(dict_itr->second[1]);
            std::string opc=dict_itr->second[2];
            int ub=std::stoi(dict_itr->second[3]);

            dbgs()<<"lb is "<<lb<<" "<<"ub is "<<ub<<"opc is "<<opc<<"\n";
            if(lb<=ub)
            {
                //dbgs()<<"PPPPPPPPPPp";
                if (opc=="add")
                {
                    //dbgs()<<"ZZZZZZZZ";
                    temp_trip_count=(ub-lb+2)/step_size;
                    dbgs()<<"@@"<<temp_trip_count;

                }
                else
                if(opc=="mul")
                {
                   // dbgs()<<"BBBBBBBBBBB";
                    temp_trip_count=(std::log2(ub-lb+2)/std::log2(step_size))+1;
                    dbgs()<<"@@"<<temp_trip_count;
                }
            }
            else
            {
                if (opc=="sub")
                {
                    temp_trip_count=(lb-ub+2)/step_size;

                }
                
                else
                if(opc=="sdiv")
                {
                    temp_trip_count=(std::log2(lb-ub+2)/std::log2(step_size))+1;
                }

                       }
                       //dbgs()<<"%^%^^^"<<temp_trip_count<<"\n";
         //dict_itr.second.push_back(std::to_string(temp_trip_count));
         dict_itr->second[4]=std::to_string(temp_trip_count);
         dbgs()<<"@#@#@"<<dict_itr->second[0]<<" "<<dict_itr->second[1]<<" "<<dict_itr->second[2]<<" "<<dict_itr->second[3]<<" "<<dict_itr->second[4]<<"\n";
         dbgs()<<"\n"<<"!!!"<<dict_itr->second.size()<<"\n";   
        }

        for(auto dict_itr:loop_bounds_dict)
        {
            dbgs()<<"AAAAAAAAAAA()()()"<<dict_itr.second.size()<<"\n";
            dbgs()<<"!!~~!!~!"<<dict_itr.second[0]<<" "<<dict_itr.second[1]<<" "<<dict_itr.second[2]<<" "<<dict_itr.second[3]<<" "<<dict_itr.second[4]<<"\n";

        }
        
        
        //adjust the trip count according to parent-child relatioship between loops
        for(auto itr=inorder_loop_nest.begin();itr!=inorder_loop_nest.end();itr++)
        {
            //itr->first->dump();
            dbgs()<<itr->second.size();
            for(auto loop_itr=itr->second.begin();loop_itr!=itr->second.end();loop_itr++)
            {
               // (*loop_itr)->dump();
                auto parent=(*loop_itr)->getParentLoop();
                if(parent)
                {
                    auto temp=loop_bounds_dict.find((*loop_itr));
                    //dbgs()<<"\nChilDDDDDDD "<<temp->second[4];
                    //dbgs()<<"\nparenTTTTTT "<<loop_bounds_dict.find(parent)->second[4];
                    temp->second[4]=std::to_string(std::stoi(temp->second[4])*std::stoi(loop_bounds_dict.find(parent)->second[4]));


                }
            }
        }

        //print updated loop_bounds_dict
        for(auto dict_itr:loop_bounds_dict)
        {
            dbgs()<<"()()()"<<dict_itr.second.size()<<"\n";
            dbgs()<<"!!~~!!~!"<<dict_itr.second[0]<<" "<<dict_itr.second[1]<<" "<<dict_itr.second[2]<<" "<<dict_itr.second[3]<<" "<<dict_itr.second[4]<<"\n";

        }


        for(auto itr:loop_bounds_dict)
        {
            if(loop_bb_dict.find(itr.first)==loop_bb_dict.end())
            {
                SmallVector<llvm::BasicBlock*,16> bb_list;
                std::pair<llvm::Loop*,llvm::SmallVector<llvm::BasicBlock*,16>> loop_to_bb=std::make_pair(itr.first,bb_list);
                loop_bb_dict.insert(loop_to_bb);
            }

            
        }
        // For each loop we have the list of BB under it
        for(auto itr=loop_bb_dict.begin();itr!=loop_bb_dict.end();itr++)
        {
            for(auto bb_itr:itr->first->blocks())
            {
                itr->second.push_back(bb_itr);
            }
        
        }

        for(auto inst:Instruc_float_vars)
        {
            if(float_inst_trip_count.find(inst)==float_inst_trip_count.end())
            {
                std::pair<llvm::Instruction*,int> instruc_to_count=std::make_pair(inst,1);
                float_inst_trip_count.insert(instruc_to_count);
            }
        }



        //for each floating point type instruction in Instruc_float_vars check against the preorder loop dict and loop_bb_dict
        
        
        dbgs()<<"!@!#!@#!@#  "<<Instruc_float_vars.size()<<"\n";
        for(auto float_inst:Instruc_float_vars)
        {
            dbgs()<<"OKOKKOK1"<<"\n";
            for(auto loop_itr:inorder_loop_nest)
            {
                //dbgs()<<"OKOKKOK2"<<"\n";
                for(auto rev=loop_itr.second.rbegin();rev!=loop_itr.second.rend();rev++)
                {
                    auto temp=loop_bb_dict.find(*rev);
                   // dbgs()<<"OKOKKOK3"<<"\n";
                    for(auto bb_itr:temp->second)
                    {
                     // dbgs()<<"OKOKKOK4"<<"\n";  
                       // float_inst->getParent()->dump();
                       // dbgs()<<"\n";
                       // bb_itr->dump();                    
                        if(float_inst->getParent()==bb_itr)
                        {
                        float_inst_trip_count.find(float_inst)->second=float_inst_trip_count.find(float_inst)->second+std::stoi(loop_bounds_dict.find(*rev)->second[4]);
                       // dbgs()<<"$$$$$$^^^^^^^^^^"<<"\n";
                      //  float_inst_trip_count.find(float_inst)->first->dump();
                       // dbgs()<<float_inst_trip_count.find(float_inst)->second<<"\n";
                        break;
                        }
                    }
                    if(float_inst_trip_count.find(float_inst)->second>1)
                    break;
                }
                if(float_inst_trip_count.find(float_inst)->second>1)
                    break;
            }
        }

        
        for(auto itr : float_inst_trip_count)
        {
            //itr.first->dump();
            dbgs()<<itr.second<<"\n";
            total_trip_count+=itr.second;

        }

dbgs()<<"Final total trip count of function "<<F.getName()<<" is: "<<total_trip_count<<"\n";
        

        // according to def use chain concept get the uses of each alloca above  
        // for(auto al_begin=float_vars.begin(),al_end=float_vars.end();al_begin!=al_end;al_begin++)
        // {
        //     dbgs()<<"for alloca :";
        //     (*al_begin)->dump();
        //     for(auto var_user:(*al_begin)->users())
        //     {
        //         dbgs()<<"**"<<var_user->getNumOperands()<<"\n";
        //         var_user->dump();
        //         if(auto *instruc=dyn_cast<llvm::Instruction>(var_user))
        //         Instruc_float_vars.push_back(instruc);

        //     }

        // }

        // // for(auto itr:Instruc_float_vars)
        // // itr->dump();
        // //std::sorting+ std::unique on Instruc_float_vars
        // //std::sort(Instruc_float_vars.begin(),Instruc_float_vars.end());
        // //dbgs()<<"!!!"<<Instruc_float_vars.size()<<"\n";
        // auto ip=std::unique(Instruc_float_vars.begin(),Instruc_float_vars.end());s
        // Instruc_float_vars.resize(std::distance(Instruc_float_vars.begin(), ip));
        // //dbgs()<<"!!!"<<Instruc_float_vars.size()<<"\n";
                // for(auto itr:Instruc_float_vars)
                // {
                // itr->dump();
                // //itr->getType()->dump();
                // }

        // // now get all those intsructions that uses these instructions ; this will be iterative procedure






    

    }
    };
}

char CountFlop::ID = 0;
static RegisterPass<CountFlop> X("count_flop", "specifically for arm(Raspberry pi4) since it doesnt have corresponding HW or SW event ; Analysis Pass");

