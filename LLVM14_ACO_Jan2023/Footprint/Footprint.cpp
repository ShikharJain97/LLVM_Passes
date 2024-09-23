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

using namespace llvm;

static cl::opt<std::string> variable_to_process("var-name", cl::desc("Name of the variable for which scope,footprint,read/writes are analysed "), cl::value_desc("name of the variable/identifier string"), cl::Required);

namespace {
  struct ftprint : public ModulePass {
    static char ID;
    ftprint() : ModulePass(ID) {}
    
    bool runOnModule(Module &M) override {
      //dbgs()<<variable_to_process<<"\n";
      std::set <unsigned int> var_footprint;
      int reads=0;
      int writes=0;

      // task1 : need to get some meta data about the current translation unit . Needed info is 
      // -> Traget Triple      
      // -> clang version used
      // -> LLVM guthub repo link from which build is done
      // -> LLVM Commit Hash
      // for accessing above info we need to acces certain named metadata nodes 
      // I specifically used llvm.ident named metadata node as this is availbale in the IR even without use of -g flag. 
      // Thus atleast some information returned by this pass will be agnostic to source leve;l debug info
      auto *Ident = M.getNamedMetadata("llvm.ident");
      if (!Ident) {
        errs() << "llvm.ident metadata not found.\n";
        //return false;
      }
      else
      {
        char delim1='(';
        char delim2=' ';
        std::string clang_version="";
        std::string llvm_source_repo="";
        std::string commit_hash="";
        std::string Target=M.getTargetTriple();
        bool stop1=false;
        bool stop2=false;

      for (auto Op : Ident->operands()) {
          //Op->dump();
          Metadata* m=Op->getOperand(0);
        if (auto *MDStr = dyn_cast<MDString>(m)) {
          auto Str = MDStr->getString().str();
          
          for (int i=0; i<Str.size();i++)
          {
            if(Str.at(i)!=delim1 && stop1==false)
            {
            clang_version+=Str.at(i);            
            }
            else
            {
              stop1=true;
                if(Str.at(i)!=delim2 && stop2==false)
                {
                  llvm_source_repo+=Str.at(i);
                }
                else
                {
                  stop2=true;
                  commit_hash+=Str.at(i);
                }
            }

          }
          dbgs()<<"Clang Version: "<<clang_version.substr(14)<<"\n";
          dbgs()<<"LLVM Source Repository: "<<llvm_source_repo.substr(1)<<"\n";
          dbgs()<<"LLVM Commit Hash:"<<commit_hash.substr(0,Str.size()-1)<<"\n";
          dbgs()<<"Target: "<<Target<<"\n";
      

}
      }
      }


      
      // task2 : get all the llvm.debug.declare type call instructions. Then iterate over them and get the variable name and check which of them is relevant
      
      for(auto& F: M)
      {
        for(auto& BB: F)
        {
          for(auto& I: BB)
          {
            //dbgs()<<"*^^^^^^^";

            if(auto *debg_declare_inst=dyn_cast<DbgDeclareInst>(&I))
            {
              if(auto *meta_info=dyn_cast<MetadataAsValue>(debg_declare_inst->getOperand(1)))
              {

                if(auto *di_local=dyn_cast<DIVariable>(meta_info->getMetadata()))
                {
                    auto var_name=di_local->getName().str();

                    if(var_name==variable_to_process)
                    {
                      reads=0;
                      writes=0;
                      dbgs()<<"var_name: "<<var_name<<"\n";
                      dbgs()<<"Variable Scope: "<<di_local->getLine()<<":"<<"\n";
                      //dbgs()<<"DI Type:"<<di_local->getType()->getName()<<"\n";

                    if(auto *meta_info=dyn_cast<MetadataAsValue>(debg_declare_inst->getOperand(0))) // this is showing uses of call instruction only bu i need uses of first argument of that call inst
                      {
                        //meta_info->dump();
                        if(auto* mm=dyn_cast<ValueAsMetadata>(meta_info->getMetadata()))
                        {
                       // dbgs()<<"%%%%%"<<"\n";  
                        // maybe need dyn_cast
                        
                       // dbgs()<<"&&&&"<<"\n";
                       // dbgs()<<"need footprint hence need instruction pointer";
                          for(auto& uses:mm->getValue()->uses())                    // will give uses thrugh non pointer/scalors 
                          {
                            if(auto user=dyn_cast<Instruction>(uses.getUser()))
                            {
                              //dbgs()<<"used at"<<user->getDebugLoc()->getLine()<<"\n";
                              //dbgs()<<"user is:";
                              var_footprint.insert(user->getDebugLoc()->getLine());
                              //user->dump();

                            // getting no. of read and rights
                            //dbgs()<<"opcode is "<<"\n"; 
                              if (std::string(user->getOpcodeName()) == "load")
                              {
                                //get uses of this load if it has a store auch that this load is 2nd operand or target of teh store than its a right else its a read
                                 for(auto& load_uses:user->uses())
                                 {
                                  if(auto* used_as_store=dyn_cast<StoreInst>(&load_uses))
                                  {
                                    if (used_as_store->getPointerOperand() == user)
                                    {
                                      writes++;
                                    }
                                  }
                                  reads++;
                                 }
                                 reads++;
                              }                              
                              if(std::string(user->getOpcodeName()) == "store")
                              {
                                if(auto* store_use=dyn_cast<StoreInst>(user))
                                  {
                                  if (store_use->getPointerOperand() == mm->getValue())
                                    {
                                      writes++;
                                    }
                                  }

                              }
                            }
                          }
                        }
                      }
                      std:: string footprint="";
                      dbgs()<<"Footrpint is: ";
                      for(auto iter:var_footprint)
                      {
                      footprint+=std::to_string(iter)+",";
                      //dbgs()<<iter<<",";
                      }
                      //dbgs()<<iter<<",";
                      auto fp=footprint.erase(footprint.size()-1,1);
                      dbgs()<<fp<<"\n";
                      
                      //dbgs()<<"\n";
                      dbgs()<<"Number of Reads: ";
                      dbgs()<<reads<<"\n";
                      dbgs()<<"Number of Writes: ";
                      dbgs()<<writes<<"\n";
                      var_footprint.clear();
                    }
                }
              }
              //
              

            }
            else
            {
              //dbgs()<<"*****";
            }
          }
        }
      }
      

      
            return false;
    }
  };
}

char ftprint::ID = 0;
static RegisterPass<ftprint> X("ftprint", "CS6383 Assign 1 ; Analysis Pass");


















// //===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
// //
// // Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// // See https://llvm.org/LICENSE.txt for license information.
// // SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// //
// //===----------------------------------------------------------------------===//
// //
// // This file implements two versions of the LLVM "Hello World" pass described
// // in docs/WritingAnLLVMPass.html
// //
// //===----------------------------------------------------------------------===//

// #include "llvm/ADT/Statistic.h"
// #include "llvm/IR/Function.h"
// #include "llvm/Pass.h"
// #include "llvm/Support/raw_ostream.h"
// #include "llvm/IR/Module.h"
// #include "llvm/IR/DebugInfo.h"
// #include "llvm/Analysis/ModuleDebugInfoPrinter.h"

// using namespace llvm;

// //#define DEBUG_TYPE "hello"

// //STATISTIC(HelloCounter, "Counts number of functions greeted");


// namespace {
//   // Hello2 - The second implementation with getAnalysisUsage implemented.
//   struct Test_Pass1 : public ModulePass {
//     static char ID; // Pass identification, replacement for typeid
//     Test_Pass1() : ModulePass(ID) {}

//     bool runOnModule(Module &M) override {
//       //++HelloCounter;
//       errs()<<"Hello: ";
//       errs()<<M.getName() << '\n';
//       errs()<<M.getInstructionCount() << '\n';
//       errs()<<M.getTargetTriple()<<'\n';      
//       errs()<<M.getDataLayoutStr()<<'\n';
//       DebugInfoFinder dbg_info;
//       //raw_ostream out=new raw_ostream();
//       printModuleDebugInfo (errs(), &M, dbg_info);


//       //dbg_info.processModule(M);      
//       //errs()<< dbg_info.compile_unit_count();
      
//       errs()<<"\n";
      
//       return false;
//     }

//     // We don't modify the program, so we preserve all analyses.
//     // void getAnalysisUsage(AnalysisUsage &AU) const override {
//     //   AU.setPreservesAll();
//     // }
//   };
// }

// char Test_Pass1::ID = 0;
// static RegisterPass<Test_Pass1>Y("Test_Pass1", "get the debug info of whole module");
