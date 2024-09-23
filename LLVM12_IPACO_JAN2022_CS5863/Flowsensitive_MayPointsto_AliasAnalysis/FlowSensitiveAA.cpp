/// update on 20/03/2021 01:23 AM
// for transfer func x=&a;
// code is working fine for allmost all cases (except behavouir is unknown for functions having pointer arguments)

#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/User.h"
#include "llvm/IR/Value.h"

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/SmallSet.h"


#include<vector>
#include<map>
#include<list>
using namespace llvm;
namespace{
class FlowSensitiveAA:public FunctionPass
{
    public:
    static char ID;
    FlowSensitiveAA():FunctionPass(ID){}

//bool islistnotempty(std::vector<BasicBlock*> *list){
  //  auto l1=(*list).front();
   // outs()<<"#$#$#$$"<< l1->getNameOrAsOperand()<<"\n";

//auto itb=(*list).begin();
//auto ite=(*list).end();
//for(;itb!=ite;++itb)
//{
 //   if(*itb)
  //  return true;

//}
//return false;

  //  }

// function to return an empty points to graph
    //DenseMap<Instruction*,SmallVector<char> > EmptyPointsToGraph(SmallVector<Instruction*> * pointer_vars_vec,int size)
   // {
// look and feel.        
//       %2: <0,0,0,1,0>
//       %3: <0,0,1,1,0> 

     //   DenseMap<Instruction*,SmallVector<char> > temp1;
     //   auto itb=(*pointer_vars_vec).begin();
     //   auto ite=(*pointer_vars_vec).end();
        
     //   for(;itb!=ite;++itb)
     //   {
       //     SmallVector<char> temp2(size,'0');
            //temp2.reserve(size);
     //       temp1.insert(std::make_pair(*itb,temp2));
     //   }
     //   return temp1;
   // }
  

  void PrintPointsToPerInstrn(DenseMap<Instruction*,SmallVector<char> >* pointstomap,DenseMap<Instruction*,SmallVector<std::string> >* pointer_vars,DenseMap<Instruction*,SmallVector<std::string> >* scalors_vars)
  {

     // outs()<<"inside printspoints\n";
      // this function takes pointer sn order to minimize stack frame size
     // outs()<<"@@";
      auto itb=pointstomap->begin();
    ////  outs()<<"@@";
      auto ite=pointstomap->end();
      //Instruction* temp;

// for printing first row
auto tt1=pointer_vars->begin();
auto tt2=pointer_vars->end();
auto tt3=scalors_vars->begin();
auto tt4=scalors_vars->end();
//outs()<<"\t\t";
for(;tt1!=tt2;++tt1)  // printing all ppointers
{
    //outs()<<tt1->second[0]<<" ";
}

for(;tt3!=tt4;++tt3)  // printing all scalors
{
    //outs()<<tt3->second[0]<<" ";
}

// printing row labels along with points to info

      for(;itb!=ite;++itb)
      {
auto temp=pointer_vars->find(itb->first);
if(temp!=pointer_vars->end())
{
   // outs() <<" variable is :";
  //  outs()<<temp->second[0];// it will print the label of the th row of the points to map
}
//else
//{
//temp=*scalors_vars.find(itb->first);
//if(temp!=*scalors_vars.end())
//{
//    outs <<" variable is :";
//    outs()<<temp->first;// it will print the label of the th row of the points to map
//}     
    //  outs()<<"\t";
      // print the corresponding row
auto svitb=itb->second.begin();
auto svite=itb->second.end();
for(;svitb!=svite;++svitb)
{
//outs()<<" ,"<<*svitb;
}
      }
  }
  

 //@#@#@$$##@#@ THERE COULD BE NO POINTERS IN THE PROGRAM @#@#@#@#$#$#%$
 // thus size of pointers_vars or pointer_vars_vec could be zero
// hence code depending on them should be put under appropriate checks



    bool runOnFunction(Function &F) override
    {
    DenseMap<Instruction*,SmallVector<std::string> > pointer_vars;// this map will hold the instrn for 1) alloca pointer instrn 2) load instrn (reading a poninter value)  
    SmallVector<Instruction*> pointer_vars_vec;
    DenseMap<Instruction*,SmallVector<std::string> > scalors_vars;
    SmallVector<Instruction*>scalors_vec; 
    unsigned int pointer_level=0;
    int pointer_var_count=-1;
    int instrn_count=0;
    SmallVector<std::string> temp_vec;
    //std::map<std::string,std::vector<std::string> > pointer_vars_info; 
    //std::map<std:: string,std:: string> scalors_vars_info;
    std::string temps;


    SmallVector<Instruction*>prog_vars;

    // need to create inset and out set
    DenseMap<Instruction*,DenseMap<Instruction*,SmallVector<char> > > Inset;
    DenseMap<Instruction*,DenseMap<Instruction*,SmallVector<char> > > Outset;
    // look and feel
    //%1:--> a points_to_map on heap
    //%2:--> a points_to_map on heap
// where --> means a pointer.


    // for iteratng over CFG in bfs fashion
    //outs()<<"Function is: "<<F.getName();    
    SmallVector<BasicBlock*> list; // worklist
    DenseMap<BasicBlock*,char> list_color;
    BasicBlock& entry=F.getEntryBlock();// entry basic block
    BasicBlock* l1;// to hold head BB node
    BasicBlock *lastBB_BFS;
    // unsigned int BBcounter=0;

    list.push_back(&entry);
    list_color.insert(std::make_pair(&entry,'0'));
    //BBcounter++;
    //auto list_it=list.begin();

    while(list.size()>0)// "worklist fashioned" BFS traversal of CFG
    {
    l1=list.front();
        //outs()<< l1->getNameOrAsOperand()<<"\n";
    list.erase(list.begin());// removed the basic block.
if(list_color.find(l1)->second=='0')// checking whtehr the node is white
{
 list_color.find(l1)->second='1';// making node gray
        for(BasicBlock *Pred : successors(l1))
        {
            if(list_color.find(Pred)==list_color.end())
            {
            list.push_back(Pred);
            list_color.insert(std::make_pair(Pred,'0'));
            //BBcounter++;
        }  
        }
// traversing a basic block
    for(auto insb=l1->begin(),inse=l1->end();insb!=inse;++insb)
    {
        instrn_count++;
        //temps="%"+std::to_string(instrn_count);
        temps = (*insb).getNameOrAsOperand();

        //checking for alloca pointer or load of pointer tyoe
                auto ali = dyn_cast<AllocaInst>(insb);
                auto li = dyn_cast<LoadInst>(insb);
                if (ali) // is it alloca
                {
                   Type* ty =ali->getAllocatedType();
                if(ty->isPointerTy())// is a pointer type allocated
                {
                   //outs()<<"\n:-- ";                      
                   pointer_level=1;
                   SmallVector<std::string>temp_vec(3);
                   temp_vec[0]=temps;// string label for pointer instrn or variable
                  temp_vec[1]="" ;// string form unsigned int detrerminig pointer level
                   temp_vec[2]="" ;// Base primitive type
               // can be delayed //pointer_vars.insert(std::make_pair(*insb,temp));
                pointer_vars_vec.push_back(&*insb);

// determining the level of pointer and primitive type 
               while(ty->isPointerTy())
                { 
                    //outs()<<"@@@\n";
                    //tt->getPointerElementType();
                    //outs()<<"\n";
                    pointer_level++;
                    //temp=tt;
                    ty=ty->getPointerElementType();
                    //tt=dyn_cast<PointerType>(tt);
                    
                }
temp_vec[1]=std::to_string(pointer_level);
if(ty->isFloatTy())
                {
//temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Float"));
 
 temp_vec[2]="Float";
 
 //pointer_vars.insert(std::make_pair(temps,bib));
 
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
 
                }
else
    if(ty->isDoubleTy())
    {
    //temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Double"));
 //pointer_vars.insert(std::make_pair(temps,bib));
 temp_vec[2]="Double";
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
 
 }
else
if (ty->isIntegerTy())
{
 //  temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Int"));
 //pointer_vars.insert(std::make_pair(temps,bib));
 temp_vec[2]="Int";
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
 
}
pointer_vars.insert(std::make_pair(&*insb,temp_vec));
pointer_level=0;
temp_vec.clear();
// pointer level and base primitive checked
                }
                else // is it alloca but scalor allocation
                {
                     //outs()<<"\n:-- ";
                    auto ty2=ali->getAllocatedType();
                     SmallVector<std::string> temp_vec2(2);
                    if(ty2 && (ty2->isIntegerTy() || ty2->isFloatTy() || ty2->isDoubleTy()))
                    {
                       
                        temp_vec2[0]=temps;
                        temp_vec2[1]="";
                        //can be delayed//scalors_vars.insert(std::make_pair(temp,*insb));
                        scalors_vec.push_back(&*insb);
                        //outs()<<"\n A scalor :-- ";
                        //bib->dump();
                    }
// what is the base prmitive for this scalor
if(ty2->isIntegerTy())
                    {
                        //scalor_vars.insert(std::make_pair(temps,bib));
                        //scalor_vars_info.insert(std::make_pair(temps,"Int"));
                          temp_vec2[1]="Int";
                        //outs()<<"\n A scalor :-- ";
                        //bib->dump();
                    }
                    if(ty2->isFloatTy())
                    {
     //scalor_vars.insert(std::make_pair(temps,bib));
                        //scalor_vars_info.insert(std::make_pair(temps,"Float"));
                        temp_vec2[1]="Float";
                                       }
                    if(ty2->isDoubleTy())
                    {
     //scalor_vars.insert(std::make_pair(temps,bib));
                        //scalor_vars_info.insert(std::make_pair(temps,"Double"));
                        temp_vec2[1]="Double";
                                       }

scalors_vars.insert(std::make_pair(&*insb,temp_vec2));
                    
                }
                }
                else  // is it a load instrn
        if(li) 
        {
            auto ty2=li->getOperand(0)->getType()->getPointerElementType();
            if(ty2->isPointerTy()) // is ths load instrn loading a pointer type value
            {
                pointer_level=1;
           //can be delayed // pointer_vars.insert(std::make_pair(temp,*insb));
            SmallVector<std::string>temp_vec3(3);
            temp_vec3[0]=temps;
            temp_vec3[1]="";
            temp_vec3[2]="";
            pointer_vars_vec.push_back(&*insb); 

// determining the level of pointer and primitive type 
               while(ty2->isPointerTy())
                { 
                    //outs()<<"@@@\n";
                    //tt->getPointerElementType();
                    //outs()<<"\n";
                    pointer_level++;
                    //temp=tt;
                    ty2=ty2->getPointerElementType();
                    //tt=dyn_cast<PointerType>(tt);
                    
                }
temp_vec3[1]=std::to_string(pointer_level);

if(ty2->isFloatTy())
                {
//temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Float"));
 //pointer_vars.insert(std::make_pair(temps,bib));
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
  temp_vec3[2]="Float";
                }
else
    if(ty2->isDoubleTy())
    {
  //  temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Double"));
 //pointer_vars.insert(std::make_pair(temps,bib));
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
 temp_vec3[2]="Double";
 }
else
if (ty2->isIntegerTy())
{
   //temp_vec.push_back(std::to_string(pointer_level));
//temp_vec.push_back(std::string("Int"));
 //pointer_vars.insert(std::make_pair(temps,bib));
 //pointer_vars_info.insert(std::make_pair(temps,temp_vec));
 temp_vec3[2]="Int";
}
pointer_vars.insert(std::make_pair(&*insb,temp_vec3));
pointer_level=0;
temp_vec.clear();



                
            }
        }
    }
 list_color.find(l1)->second='2';// node is black now.
 lastBB_BFS = l1; // to capture the last BB in BFS order
}  // color checkng if end
}// worklist loop over








// till here we have
//1) collevcted all pointers (alloca nd load)
//2) all scalors(alloca)
//3)checked ponter level and base primitive for pointer and scalors

// merge pointers_vec and scalors_vec;Name it as prog_vars

prog_vars.reserve(pointer_vars_vec.size()+scalors_vec.size()); // if pointer_vars_vec.size==0 then prog_vars.size==scalors.size 
if(pointer_vars_vec.size()>0)
prog_vars.insert(prog_vars.end(),pointer_vars_vec.begin(),pointer_vars_vec.end());
prog_vars.insert(prog_vars.end(),scalors_vec.begin(),scalors_vec.end());

//outs() << "loop case: " << prog_vars.size()<<"\n";

// print prog vars
//outs()<<"printing prog vars\n";
//auto pvitb=prog_vars.begin();
//auto pvite=prog_vars.end();
//for(;pvitb!=pvite;++pvitb)
//(*pvitb)->dump();


// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// now will populate the inset and outset
// need to agin iterate over the CFG the same way

const size_t s = prog_vars.size(); // total no. of pointers and scalors
if(pointer_vars_vec.size()>0)
{

//clear color map
list_color.clear();
//clear worklist
list.clear();

//entry=F.getEntryBlock();
list.push_back(&entry);
list_color.insert(std::make_pair(&entry,0));

while(list.size()>0)// "worklist fashioned" BFS traversal of CFG
    {
  //outs() << "for loop: " << list.size() << "\n";
  l1 = list.front();
  // outs()<< l1->getNameOrAsOperand()<<"\n";
  list.erase(list.begin());             // removed the basic block.
  if (list_color.find(l1)->second == 0) // checking whtehr the node is white
  {
    list_color.find(l1)->second == 1; // making node gray
    for (BasicBlock *Pred : successors(l1)) {
      if(list_color.find(Pred)==list_color.end())
            {  
      list.push_back(Pred);
      list_color.insert(std::make_pair(Pred, 0));
      // BBcounter++;
            }
    }

    // traversing a basic block
    for(auto insb=l1->begin(),inse=l1->end();insb!=inse;++insb)
    {
        //(*insb).dump();

        
        DenseMap<Instruction*,SmallVector<char> > temp1; // for each instrn a new ponints to map wii be created
        //auto t1itb=pointer_vars_vec.begin();
        //auto t1ite=pointer_vars_vec.end();
        //outs() << pointer_vars_vec.size()<<"\n";
        // only when the current function have pointers then this loop will actually allocate something.
        for (auto t1itb : pointer_vars_vec) // not coming inside this loop
        {
          // SmallVector<char> temp2(prog_vars.size(),'0');
          // temp2.reserve(size);
          //outs() << "hello\n";
          temp1.insert(std::make_pair(t1itb, SmallVector<char>(s,'0')));
          //outs() << "hello\n";
        }
        //outs() << "#$#$#";
        //outs() << *(temp1.begin()->second.begin());
        //outs()<< *(temp1.begin()->second.begin());
        // points to map is ready
        // auto Eptm=EmptyPointsToGraph(&pointer_vars_vec,prog_vars.size());
        // if(Eptm)

        Inset.insert(std::make_pair((&*insb), temp1));
        Outset.insert(std::make_pair((&*insb), temp1));
    }
   list_color.find(l1)->second==2; /// making node black 
}
    } // end while loop for inset outset population process
// *(Inset.begin())->first->dump();
//// end of the if condition check for the size of pointer_vars_vec

//outs() << ((((Inset.begin())->second).begin())->second).front();
//auto z1 = Outset.begin();
//auto z2 = z1->second;
//auto z3 = z2.begin();
//auto z4 = (z3->second).begin();
//auto z5 = (z3->second).end();
//for (; z4 != z5 ;z4++)
//outs()<< *z4<<",";

// auto isib=Inset.begin();
// auto isie=Inset.end();

//outs()<< (((isib->second).begin())->second)[0];

//for(auto isib : Inset)
//{ 
//  outs()<<" Instruction :";
   //(isib.first)->dump();
   //auto tt10=isib.second; //return a dense map
   //auto tt11=tt10.begin();// return iterator to above dense map
   //outs()<< *(tt11->second.begin());
   //auto tt12=(tt11->second);// return small vector in above dense map
    
   
   //for(auto tt13: tt12)
  // outs()<< tt13<<",";
   //outs()<<"\n";
//outs()<<"points to "<< isib->second-><<", "<<isib->second[1];
  //  PrintPointsToPerInstrn(isib->second,&pointer_vars,&scalors_vars);
//}

//######@@##@@$@$#$@#$@#$#$@$@# isue is inset are not getting accessed prpoerly i.e the points to map.


// finalyy will create a map where key is elements of pointers_vec and and 2nd element is a vector corresponding to prog_vars  
// this above map is the ponts to map.


// printing prog_vars : they should contain all pointers generated by alloca, load and scalors.
//auto pvitb=prog_vars.begin();
//auto pvite=prog_vars.end();
//for(;pvitb!=pvite;++pvitb)
//{
 //   (*pvitb)->dump();
//}
// printing fine ; till here code is working fine; 


//auto pvitb=pointer_vars.begin();
//auto pvite=pointer_vars.end();
//for(;pvitb!=pvite;++pvitb)
//{
//pvitb->first->dump();
//outs()<<"label:"<<pvitb->second[0]<<"level:"<<pvitb->second[1]<<"Base Primitive:"<<pvitb->second[2]<<"\n";/
//}
// the dense map such as pointer_vars is working fine.

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

// now actual worklist loop will begin
// this loop will not traverse the CFG in BFS order 
// this loop maintainenece depends upon the change in old Pin with respect to new Pin .

//clear color map
list_color.clear();
//clear worklist
list.clear();
int zz1 = prog_vars.size();
int zz2=0;
char WYAS = '0'; // WHY ADD SUCCESORS BB
// entry=F.getEntryBlock();
list.push_back(&entry);
list_color.insert(std::make_pair(&entry,0));



while(list.size()>0)// "worklist fashioned" BFS traversal of CFG but halting criteria is different than "color the node" scheme and hence will take many more iterations
    {
  //outs() << "current BB is: ";
  
  l1 = list.front();
  WYAS = '0';
  //outs() << l1->getNameOrAsOperand() << "\n";
  list.erase(list.begin()); // removed the basic block.
  //outs() << "\n current worklist size" << list.size()<<"\n";
  SmallVector<BasicBlock *> predstocurrentbb;

  // creating an empty dense map to hold union operation results
  // this dense map "tempPT" will hold all the union of all the preds for the frst instrn of each BASIC BLOCK 
   DenseMap<Instruction*,SmallVector<char> > tempPT; // for each instrn a new ponints to map wii be created
       for (auto t1itb : pointer_vars_vec) 
        {
          tempPT.insert(std::make_pair(t1itb, SmallVector<char>(s,'0')));
          
        }


      //  outs() << l1->getNameOrAsOperand()<<"\n";
        // adding all preds of current BB
        auto entryPoint = &entry;
if(l1==entryPoint)
{
     // outs() << "\n05\n";
    // since it's entry BB thus just add all the succsesors of this bb into worklist
    // rememeber there is no back edge to entry BB
    for(auto xx:successors(l1)) // its not ncessary that a BB has succesors
    {
      //  outs() << "\n05";
      list.push_back(xx);
    }
}


        if (l1 != entryPoint)  // this is for unioning of all preds to this current BB and putting that in 
        //current BB first INstrn inset. 
        {

          //outs() << "\n02\n";
          for (auto *pp : predecessors(l1))
            predstocurrentbb.push_back(pp);
        
//outs() << "for current BB:" << l1->getNameOrAsOperand() << "\n";
for(auto pp: predstocurrentbb) /// right now issue is in case of multiple BB code is HALTING prematurely hence need to check about union.
{
  //outs() << "\n03";
  // access terminator instrn of each pp

  //outs() << "the preds are: " << pp->getNameOrAsOperand() << " ,";
  auto pp1 = pp->getTerminator();
  //outs() << " the terminator is :";
 // pp1->dump();
  // for this terminator access the outset and acces its pointsto
  auto pp2 = &(Outset.find(pp1)->second);
  // need to union it with others
  // how to do union??
  // for each insrn in pointer_vars_vec just iterate through complete char vector and update 
  for (auto pp3 : pointer_vars_vec)
   {
        zz2 = 0;
   while(zz2<zz1)
   { 
    if((((*pp2).find(pp3))->second)[zz2]=='1')
    {
    //  outs() << "Im in\n";
      ((tempPT.find(pp3))->second)[zz2] = '1';
    //  outs() << "$$$ " << ((tempPT.find(pp3))->second)[zz2];
    }
    zz2++;
   }
   zz2 = 0;
  // outs() << " printing temppt"<< "\n";
          while(zz2<zz1)
          {
       //     outs() << ((tempPT.find(pp3))->second)[zz2]<<" # ";
            zz2++;
          }
     //     outs() << "\n";

  } // union done
} // for every terminator of every pred bb of current bb
        

///////// ###################################################################### /////////////
// here we decide depending on tempPT or new best approx info inset to the current BB that whether we should put successors 
//of this BB or not . BUT WHAT IF A BB DOES NOT GATE UPDATED TEMPPT AS INPUT BUT DOES GENERATE SOME INFO THROUGH ITSELF 
// IN THIS CASE ALSO WE NEEED TO ADD ALL THE SUCCESORS OF THAT BB INTO WORKLIST
// THUS IF FOR ANY INSTRN OF THIS BB INSET != OUTSET THEN ADD SUCCESORS(CURRENT BB) 

// need to check this union with current BB's first instrn inset
auto firstInstrn = &(l1->front()); // return s Instruction *
auto fipt1 = Inset.find(firstInstrn);
auto fipt2 = &(fipt1->second); // inset points to of first instrn
//outs() << "\n04";
zz2 = 0;
for (auto pp3 : pointer_vars_vec) {
  zz2 = 0;
  while (zz2 < zz1) {
    if (((tempPT.find(pp3))->second)[zz2] != (((*fipt2).find(pp3))->second)[zz2]) {
      // then there is change hence we need to add all the successors of this
      // basicblock in the worklist else do nothing
    //  outs() << "IM IN\n";
      WYAS = '1'; // since a change was detected in the TempPT and old inset of first instrn of BB hence add all succesors of this BB  
      //for (auto *pp4 :successors(l1)) // its not ncessary that a BB has succesors
     // {
     //   list.push_back(pp4);
     // }
      // this means that we have find a change in tempPT and earlier inset hence DO NOT HALT and add the successors of current BB in the list
      break;

    }    
    //else
     // HALT = '2';// if the above if is not true for a pointer variable tehn HALT=2
    // after whgole tempPT check if for not even one tym if is true then yu will
    // come out of loop with HALT=2;
    zz2++;
  }
  if(WYAS=='1')
      break;
}
      if(WYAS=='1') 
      {
          for (auto *pp4 :successors(l1)) // its not ncessary that a BB has succesors
      {
        list.push_back(pp4);
      }
      //WYAS = '0';
      }

        } // if this BB is not entry BB




//if(HALT=='1'|| HALT=='0')
//{
  //HALT = '0';
  //  outs() << "\n07\n";
  auto firstInstrn = &(l1->front());
  SmallVector<Instruction *> load_instrn_list;
  Instruction *PredInst;
  // process this current bb
  // copy tempPT into inset points to of the first instruction of this BB
  for (auto inspp1 = l1->begin(), inspp2 = l1->end(); inspp1 != inspp2;++inspp1) 
  { // iterating over all instrns of this bb
    //outs() << "\n08\n";
    //.(*inspp1).dump();

  
    if (auto ldins = dyn_cast<LoadInst>(inspp1)) {
      // this instrn is a load instrn
      load_instrn_list.push_back(&*inspp1);
    }

    // printing final union of all preds
   // outs() << " final unioned tempPT is: \n";

     for (auto pp3 : pointer_vars_vec) {
       //   outs() << "\n08\n";
          zz2 = 0;
          while (zz2 < zz1) {
   //         outs() << "@@::: "<<((tempPT.find(pp3))->second)[zz2];
            zz2++;
          }
    //      outs() << "\n";
     }

    //.outs() << "\nLoad_Instrn_lst size:" << load_instrn_list.size()<<"\n";
    if (&(*inspp1) == firstInstrn)
     {
  //      outs() << "##IM FIRST##\n";
      zz2 = 0;
      auto fipt1 = Inset.find(&*inspp1);
      auto fipt2 = &(fipt1->second); // inset points to of first instrn
   
      // copy temPT into inset
      for (auto pp3 : pointer_vars_vec) {
       //   outs() << "\n08\n";
          zz2 = 0;
          while (zz2 < zz1) {
            (((*fipt2).find(pp3))->second)[zz2] =((tempPT.find(pp3))->second)[zz2];

    //        outs() << "\n!!!@@::: "<<(((*fipt2).find(pp3))->second)[zz2]<<"\n";
            zz2++;
          }
      }
      PredInst = firstInstrn;
    }

    else // if this instrn is not first instrn
    {
      //  outs() << "\n10\n";
      // copy the outset of PredInst into Inset of this instrn
   //   outs() << " dumping pred inst: ";
     // PredInst->dump();
    //  outs() << "dumping current inst: ";
     // (*inspp1).dump();
      auto piot1 = &((Outset.find(PredInst))->second); // points to map
      auto crinst = &((Inset.find(&*inspp1))->second); // points to map
      zz2 = 0;
      for (auto pp3 : pointer_vars_vec) {
        zz2 = 0;
        while (zz2 < zz1) {
           // outs() << "\n11\n";
          (((*crinst).find(pp3))->second)[zz2]=(((*piot1).find(pp3))->second)[zz2] ;
          zz2++;
        }
        zz2 = 0;
  //      outs() << "for varaible:" << pp3->getNameOrAsOperand() << "\n";
   //     outs() << "print current instrn inset\n";
        while (zz2 < zz1) {
    //      outs() << (((*crinst).find(pp3))->second)[zz2] << " ,";
          zz2++;
}
//outs() << "\n";
      }
          }

    // till here we have checked the halt condition of killdall's and correspondingly mantained te worklist
    // for a basic block maped teh outset of predcessor instrn to inset of current instrn

      auto crinst= &((Inset.find(&(*inspp1)))->second);// pointer to Inset points to map of current instrn
      auto crinstOUT = &((Outset.find(&*inspp1))->second); // pointer to Inset points to map of current instrn
      // ########## apply transfer fn ##############
   // outs() << "\n12\n";
     if(auto stins=dyn_cast<StoreInst>(&*inspp1))
     {
        //outs() << "\n13\n";
         // strip this store instrn
         auto stpo = stins->getPointerOperand();
         auto stvo = stins->getValueOperand();
         auto stpoty = stins->getPointerOperandType();
         auto stvoIns = dyn_cast<Instruction>(stvo);
         auto stpoIns = dyn_cast<Instruction>(stpo);
         //auto stvoty = (stvo->getType())->getPointerElementType();
         //outs() << "\n15\n";
        // stins->dump();
         Type *stvoty;

         if ((stvo->getType())->isPointerTy()) // if store instrn value operand is pointer type
         // if this value is not pointer type then it is of no use. i.e this instrn maps to identity function. 
         {
             //outs() << "\n13\n";
           stvoty = (stvo->getType())->getPointerElementType();
           
           
         
         //outs() << "\n16\n";
         //auto stvoIns = dyn_cast<Instruction>(stvo);
         //auto stpoIns = dyn_cast<Instruction>(stpo);

         if (load_instrn_list.size() == 0) 
         {
            //outs() << "\n14\n";
           if(stvoty->isPointerTy()==false)// value operand is a scalor
           {
               //stvoty->print(outs());
             //  outs() << "\n";
               // thus it is x=&a;7
           if(scalors_vars.find(stvoIns)!=scalors_vars.end())
           {
               //outs() << "\n14\n";
               // thus gen set is x->a
               //check for the presence of '1' in inset points to of ths instrn
               //auto scalorindexit =prog_vars.find(stvoIns); // this returns iterator to the
               int scalorindexit=-1;
               
               for (auto xx : prog_vars) {
                 scalorindexit++;
                 if (xx == stvoIns)
                   break;
               }
//outs() << "index is : "<<scalorindexit<<"\n";
//outs() << "####"<<prog_vars.size()<<"\n";

//// ##### the effect of killing should not update the inset of this instrn cause inset is union of all the outset of predescessor instrn

// first copy the inset onto outset

auto crinstIN = crinst; // points to map
               //auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

               zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                   zz2++;
                 }}



// kill the prior points to info of this stpo
auto yy1 = (*crinstOUT).find(stpoIns);
zz2 = 0;
while (zz2 < zz1) {
  (yy1->second)[zz2] = '0';
  //outs() << "\n20\n";
  zz2++;
               }
// after killing copy the whole updated outset         
////////////////////////////////////////////////////               

   /// now update the gen set info in the outset
   // stpo is of Value* type hence need Instruction* corresponding to it
                 auto rr = dyn_cast<Instruction>(stpo);
                 auto xxx1 = &((crinstOUT->find(rr))->second);
                 //outs() << "!!!@@" << scalorindexit;
                 //outs() << "###@@" << prog_vars.size();
                 (*xxx1)[scalorindexit] = '1';

                 //outs() << "\n22\n";
               

////////////////////////////////////////////////////  
               zz2 = 0;
                 while (zz2 < zz1) {
                 //  outs() << (*xxx1)[zz2] << " ,";
                   zz2++;
                 }
               //  outs() << "\n";

///#####################################################################
// HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET
                
 zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   if(((crinstOUT->find(pp3))->second)[zz2] !=((crinstIN->find(pp3))->second)[zz2])
                   {
                     if(WYAS!='1') // WYAS= WHY ADD SUCCESORS
                     {
                     WYAS = '2'; // succesors are added because of THERE WAS CHANGE DUE INFO GENERATED BUT NO NEW INFO CAME IN AT ENTRY OF THIS BB
                     break;
                     }                     
                   }
                   zz2++;
                 }
                 if(WYAS='2')
                       break;
                 }
if(WYAS=='2')
{
    for(auto xx: successors(l1))
    {
      list.push_back(xx);
    }
    WYAS = '0';
}
           }

           } // if value operand is scalor
           else // if first level dereference of store inst value operand is not primitive type
           { // thus this means that x=&y; y is a pointer


  // stvoty->print(outs());
      //         outs() << "\n";
               // thus it is x=&a;7
           if(pointer_vars.find(stvoIns)!=pointer_vars.end())
           {
               //outs() << "\n14\n";
               // thus gen set is x->a
               //check for the presence of '1' in inset points to of ths instrn
               //auto  pointerindexit =prog_vars.find(stvoIns); // this returns iterator to the
               int pointerindexit=-1;
               
               for (auto xx : prog_vars) {
                 pointerindexit++;
                 if (xx == stvoIns)
                   break;
               }
//outs() << "index is : "<<pointerindexit<<"\n";
//outs() << "####"<<prog_vars.size()<<"\n";

//// ##### the effect of killing should not update the inset of this instrn cause inset is union of all the outset of predescessor instrn

// first copy the inset onto outset ,for current instrn

auto crinstIN = crinst; // points to map
               //auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

               zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                   zz2++;
                 }}



// kill the prior points to info of this stpo
auto yy1 = (*crinstOUT).find(stpoIns);
zz2 = 0;
while (zz2 < zz1) {
  (yy1->second)[zz2] = '0';
  //outs() << "\n20\n";
  zz2++;
               }
// after killing  update the  outset         
////////////////////////////////////////////////////               

   /// now update the gen set info in the outset
   // stpo is of Value* type hence need Instruction* corresponding to it
                 auto rr = dyn_cast<Instruction>(stpo);
                 auto xxx1 = &((crinstOUT->find(rr))->second);
                 //outs() << "!!!@@" << scalorindexit;
                 //outs() << "###@@" << prog_vars.size();
                 (*xxx1)[pointerindexit] = '1';

                 //outs() << "\n22\n";
               

////////////////////////////////////////////////////  
               zz2 = 0;
                 while (zz2 < zz1) {
         //          outs() << (*xxx1)[zz2] << " ,";
                   zz2++;
                 }
          //       outs() << "\n";

///#####################################################################
// HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET
                
 //zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   if(((crinstOUT->find(pp3))->second)[zz2] !=((crinstIN->find(pp3))->second)[zz2])
                   {
                     if(WYAS!='1') // WYAS= WHY ADD SUCCESORS
                     {
                     WYAS = '2'; // succesors are added because of THERE WAS CHANGE DUE INFO GENERATED BUT NO NEW INFO CAME IN AT ENTRY OF THIS BB
                     break;
                     }                     
                   }
                   zz2++;
                 }
                 if(WYAS='2')
                       break;
                 }
if(WYAS=='2')
{
    for(auto xx: successors(l1))
    {
      list.push_back(xx);
    }
    WYAS = '0';
}


           }







             // then also outset=inset
       // this is identity transfer function    
 //auto crinstIN = crinst; // points to map
   //        auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

     //          zz2 = 0;
         ///      for (auto pp3 : pointer_vars_vec) {
       //          zz2 = 0;
            //     while (zz2 < zz1) {
                     // outs() << "\n21\n";
              //     ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                //   zz2++;
              //   }
              //   outs() << "for variable: " << pp3->getNameOrAsOperand()<< "\n";
              //   outs() << " current instrn OUTSET is:\n";
              //   zz2 = 0;
              //   while (zz2 < zz1) {
                     // outs() << "\n21\n";
               //     outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
               //      zz2++;

                 } // if first level dereference of store inst value operand is not primitive type

                 } // if load_instrn_list.size()==0


            
        

else // if load_instrn_list.size()>0
if(load_instrn_list.size()==1)
////////////////////////////////////                 .i.e x=y //////////////////////
{
  
  if (stvoIns == load_instrn_list.front()) {
    //outs()<<"yessssssssssssssssssssssssssssssssssssssssssssssss\n";
    auto ll = load_instrn_list.front();
    // thus it mean that the above load instrn is used as value operand in this
    // store instrn and hence if stvoTY==stpoTY then it is surely x=y
    // in pointer_vars check for pointer level and base primitive type
    // equivalence
   // outs() << "\nSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(ll))->second)[1];
   // outs() << "\nSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(stpoIns))->second)[1];
   // outs() << "\nSSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(ll))->second)[2];
  //  outs() << "\nSSSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(stpoIns))->second)[2];

    if ((((pointer_vars.find(ll))->second)[1] ==((pointer_vars.find(stpoIns))->second)[1]) &&(((pointer_vars.find(ll))->second)[2] ==((pointer_vars.find(stpoIns))->second)[2])) {
   //   outs() << "\n!!@@\n";
      // GEN SET WI BE FOR STPO AND  STVO BOTH
      // NEED LOAD INSTRN OPERAND
      auto llo = ll->getOperand(0);
      auto lloInsOp = dyn_cast<Instruction>(llo); // load instruction's operand as instruction
      // since load_instrn_list.size()==1 the llo should be present in
      // pointer_vars_vec
      if (pointer_vars.find(lloInsOp) !=
          pointer_vars.end()) { // this wiill always be true
        // do change in the outset of this load instrn
        auto lloIns1 = &((Outset.find(ll))->second);
        auto lloIns2 =
            &(((*lloIns1).find(lloInsOp))->second); // extract out the points to
        // info of load instrn operand
        // this info will be copied onto the points to info load instrn
        ///////// ###### there is inherent killing also happeinig here.
        auto llIns2 = &(((*lloIns1).find(ll))->second);
        zz2 = 0;
        while (zz2 < zz1) {
          // outs() << "\n21\n";
          // outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
          (*llIns2)[zz2] = (*lloIns2)[zz2];
       //   outs() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                // << (*lloIns2)[zz2] << "\n";
          zz2++;
        }

        // copy this load instrn's outset into store instrn's inset.
        auto stInsin = &((Inset.find(&*inspp1))->second);
        zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            ((stInsin->find(pp3))->second)[zz2] =
                ((lloIns1->find(pp3))->second)[zz2];
            zz2++;
          }
        }
        // copy this instrn inset into its outset
        auto stInsout = &((Outset.find(&*inspp1))->second);
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            ((stInsout->find(pp3))->second)[zz2] =
                ((stInsin->find(pp3))->second)[zz2];
            zz2++;
          }
        }

        // kill set
        // for outset of this store instrn  for stpo i.e store instrn pointer
        // operand kill the prior info.
        zz2 = 0;

        while (zz2 < zz1) {
          // outs() << "\n21\n";
          ((stInsout->find(stpoIns))->second)[zz2] = '0';
          zz2++;
        }
        // update teh outset of this store instrn by gen set
        zz2 = 0;

        while (zz2 < zz1) {
          // outs() << "\n21\n";
          ((stInsout->find(stpoIns))->second)[zz2] =
              ((stInsout->find(ll))->second)[zz2];
          zz2++;
        }
        ///#####################################################################
        // HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET

        // zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            if (((crinstOUT->find(pp3))->second)[zz2] !=
                ((crinst->find(pp3))->second)[zz2]) {
              if (WYAS != '1') // WYAS= WHY ADD SUCCESORS
              {
                WYAS = '2'; // succesors are added because of THERE WAS CHANGE
                            // DUE INFO GENERATED BUT NO NEW INFO CAME IN AT
                            // ENTRY OF THIS BB
                break;
              }
            }
            zz2++;
          }
          if (WYAS = '2')
            break;
        }
        if (WYAS == '2') {
          for (auto xx : successors(l1)) {
            list.push_back(xx);
          }
          WYAS = '0';
        }

      } // if load instrn operand is not pointer operand in pointer_vars
    }   //  if stpo and stvo base type and pointer level are same

    else // if type of stpo and stvo are pointer type but differ in derefrencing
         // level;
    {    //  think this else is not possible

      // then also outset=inset
      // this is an identity transfer function
      auto crinstIN = crinst;                              // points to map
      auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

      zz2 = 0;
      for (auto pp3 : pointer_vars_vec) {
        zz2 = 0;
        while (zz2 < zz1) {
          // outs() << "\n21\n";
          ((crinstOUT->find(pp3))->second)[zz2] =
              ((crinstIN->find(pp3))->second)[zz2];
          zz2++;
        }
     //   outs() << "for variable: " << pp3->getNameOrAsOperand() << "\n";
     //   outs() << " current instrn OUTSET is:\n";
        zz2 = 0;
        while (zz2 < zz1) {
          // outs() << "\n21\n";
       //   outs() << ((crinstOUT->find(pp3))->second)[zz2] << ",";
          zz2++;
        }
      }
    }

  } // if only instrn in load_instrn _list is  used as value operand  in beneath
    // store instrn
  else // if the only instrn in load_instrn _list is used as ponter operand in  beneath store
  if(stpoIns == load_instrn_list.front())     // instrn
  {    // i thnk this also not possible

   //outs()<<"yessssssssssssssssssssssssssssssssssssssssssssssss\n";
    auto ll = load_instrn_list.front();
    // thus it mean that the above load instrn is used as value operand in this
    // store instrn and hence if stvoTY==stpoTY then it is surely x=y
    // in pointer_vars check for pointer level and base primitive type
    // equivalence
   // outs() << "\nSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(ll))->second)[1];
   // outs() << "\nSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(stpoIns))->second)[1];
   // outs() << "\nSSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(ll))->second)[2];
  //  outs() << "\nSSSSSSSSSSSSSSSSSSSS@@" << ((pointer_vars.find(stpoIns))->second)[2];
    


    //if ((((pointer_vars.find(ll))->second)[1] ==((stvoIns) &&
   // (((pointer_vars.find(ll))->second)[2] ==((pointer_vars.find(stvoIns))->second)[2])) 
    //{
   //   outs() << "\n!!@@\n";
      // GEN SET WI BE FOR STPO AND  STVO BOTH
      // NEED LOAD INSTRN OPERAND
      auto llo = ll->getOperand(0);
      auto lloInsOp = dyn_cast<Instruction>(llo); // load instruction's operand as instruction
      // since load_instrn_list.size()==1 the llo should be present in
      // pointer_vars_vec
      if (pointer_vars.find(lloInsOp) !=pointer_vars.end()) 
      { // this wiill always be true
        // do change in the outset of this load instrn
        auto lloIns1 = &((Outset.find(ll))->second);
        auto lloIns2 = &(((*lloIns1).find(lloInsOp))->second); // extract out the points to
        // info of load instrn operand
        // this info will be copied onto the points to info load instrn
        ///////// ###### there is inherent killing also happeinig here.
        auto llIns2 = &(((*lloIns1).find(ll))->second);
        zz2 = 0;
        while (zz2 < zz1) {
          // outs() << "\n21\n";
          // outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
          (*llIns2)[zz2] = (*lloIns2)[zz2];
       //   outs() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                // << (*lloIns2)[zz2] << "\n";
          zz2++;
        }

        // copy this load instrn's outset into store instrn's inset.
        auto stInsin = &((Inset.find(&*inspp1))->second);
        zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            ((stInsin->find(pp3))->second)[zz2] =
                ((lloIns1->find(pp3))->second)[zz2];
            zz2++;
          }
        }
        // copy this instrn inset into its outset
        auto stInsout = &((Outset.find(&*inspp1))->second);
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            ((stInsout->find(pp3))->second)[zz2] =((stInsin->find(pp3))->second)[zz2];
            zz2++;
          }
        }

        // kill set
        // for outset of this store instrn  for stpo i.e store instrn pointer
        // operand kill the prior info.
        zz2 = 0;
// ///////@@@@#### here actually we will not kill ponts to of stpoins but the points to of its elements
        while (zz2 < zz1) {
          // outs() << "\n21\n";
          if(((stInsout->find(stpoIns))->second)[zz2] == '1')
          {
            // acess instrn
            auto xx5 = prog_vars[zz2];
            int zz3=0;
            while (zz3<zz1)
            {
              ((stInsout->find(xx5))->second)[zz3] = '0';
              zz3++;
            }
          }
          zz2++;
        }
        // update teh outset of this store instrn by gen set
        zz2 = 0;

        while (zz2 < zz1) {
          // outs() << "\n21\n";
          if(((stInsout->find(stpoIns))->second)[zz2] == '1')
          {
            // acess instrn
            auto xx5 = prog_vars[zz2];
            int zz3=0;
            while (zz3<zz1)
            {
            // need to determine pointer level of stvoIns
            auto tt10 = (stvoIns->getType())->isPointerTy();
            if (tt10) 
            {
              auto tt11 = ((stvoIns->getType())->getPointerElementType());
              if ((tt11->isPointerTy()) == false) // it is scalor
              {
                // acess indes of stvoinS IN PROGVARS
                int zz4 = 0;
                while (zz4 < zz1) {
                  if (prog_vars[zz4] == stvoIns)
                    break;
                  zz4++;
                }
                ((stInsout->find(xx5))->second)[zz4] = '1';
              } 
              else {
                ((stInsout->find(xx5))->second)[zz3] = ((stInsout->find(stvoIns))->second)[zz3];
              }
            }
            
             
          
          zz3++;
            }
            
          }  
          
        zz2++;
        }
        ///#####################################################################
        // HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET

        // zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            if (((crinstOUT->find(pp3))->second)[zz2] !=
                ((crinst->find(pp3))->second)[zz2]) {
              if (WYAS != '1') // WYAS= WHY ADD SUCCESORS
              {
                WYAS = '2'; // succesors are added because of THERE WAS CHANGE
                            // DUE INFO GENERATED BUT NO NEW INFO CAME IN AT
                            // ENTRY OF THIS BB
                break;
              }
            }
            zz2++;
          }
          if (WYAS = '2')
            break;
        }
        if (WYAS == '2') {
          for (auto xx : successors(l1)) {
            list.push_back(xx);
          }
          WYAS = '0';
        }

      } // if load instrn operand is not pointer operand in pointer_vars
     //}  //  if stpo and stvo base type and pointer level are same

  // else // if type of stpo and stvo are pointer type but differ in derefrencing
         // level;
   // {    //  think this else is not possible

      // then also outset=inset
      // this is an identity transfer function
    //  auto crinstIN = crinst;                              // points to map
    //  auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

   //   zz2 = 0;
     // for (auto pp3 : pointer_vars_vec) {
     //   zz2 = 0;
      //  while (zz2 < zz1) {
          // outs() << "\n21\n";
      //    ((crinstOUT->find(pp3))->second)[zz2] =
     //         ((crinstIN->find(pp3))->second)[zz2];
     //     zz2++;
      //  }
     //   outs() << "for variable: " << pp3->getNameOrAsOperand() << "\n";
     //   outs() << " current instrn OUTSET is:\n";
      //  zz2 = 0;
      //  while (zz2 < zz1) {
          // outs() << "\n21\n";
       //   outs() << ((crinstOUT->find(pp3))->second)[zz2] << ",";
      //    zz2++;
     ///   }
     // }
   // }

    // then also outset=inset
    // this is an identity transfer function
    auto crinstIN = crinst;                              // points to map
    auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

    zz2 = 0;
    for (auto pp3 : pointer_vars_vec) {
      zz2 = 0;
      while (zz2 < zz1) {
        // outs() << "\n21\n";
        ((crinstOUT->find(pp3))->second)[zz2] =
            ((crinstIN->find(pp3))->second)[zz2];
        zz2++;
      }
     // outs() << "for variable: " << pp3->getNameOrAsOperand() << "\n";
     // outs() << " current instrn OUTSET is:\n";
      zz2 = 0;
      while (zz2 < zz1) {
        // outs() << "\n21\n";
      //  outs() << ((crinstOUT->find(pp3))->second)[zz2] << ",";
        zz2++;
      }
    }
  } // if stpoins== previous load nstrn

// then also outset=inset
// this is an identity transfer function
//auto crinstIN = crinst; // points to map
  //         auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

    //           zz2 = 0;
      //         for (auto pp3 : pointer_vars_vec) {
        //         zz2 = 0;
          ///       while (zz2 < zz1) {
                     // outs() << "\n21\n";
             //      ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
             //      zz2++;
            //     }
            //     outs() << "for variable: " << pp3->getNameOrAsOperand()<< "\n";
            //     outs() << " current instrn OUTSET is:\n";
             //    zz2 = 0;
              //   while (zz2 < zz1) {
                     // outs() << "\n21\n";
               //     outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
               //      zz2++;
              //   }               
               //  }
/// important to clear out the load instrn list
/// once the list has been processed
load_instrn_list.clear();

} // if load_instrn_list.size()==1
else // if load_instrn_list.size>1
{   //////////////////////////////////// ########## x=*y or x=**y or x=***y
/// %0 =load <ty2> <ty1>*%x
/// %1= load <ty3> <ty2>*%0
/// %2= load <ty4> <ty3>*%1
//
//%n =load <tyn> <tyn-1>*%n 
//store <tyn>%n <tyn>* point
//outs() << "$$$$$$$$$$$$$\n";
//outs() << "load_inst_list size" << load_instrn_list.size()<<"\n";
auto predload = load_instrn_list.front();

for (auto loins : load_instrn_list) {
  auto predloadop = dyn_cast<Instruction>(predload->getOperand(0));
  auto predloadopty = predload->getOperand(0)->getType();
  auto predloadty = predload->getType();
  auto curloadop = dyn_cast<Instruction>(loins->getOperand(0));
  auto curloadopty=(loins->getOperand(0))->getType();

 // outs() << predload->getNameOrAsOperand()<<"\n";
 // outs() << curloadop->getNameOrAsOperand()<<"\n";

  // for current load instrn whatever info is generated(inherent killing) by its operand is updated into this instrns outset accordingly
//  outs() << "current lload instrn is:";
  //loins->dump();
  if (curloadop != predload) {
  //  outs() << "I am FIRSTTTTTT\n";
    
    if (pointer_vars.find(curloadop) !=pointer_vars.end()) { // this wiill always be true
      // do change in the outset of this load instrn
      auto lloIns1 = &((Outset.find(loins))->second);
      auto lloIns2 =
          &(((*lloIns1).find(curloadop))->second); // extract out the points to
      // info of load instrn operand
      // this info will be copied onto the points to info load instrn
      auto llIns2 = &(((*lloIns1).find(loins))->second);
      zz2 = 0;
      while (zz2 < zz1) {
        // outs() << "\n21\n";
        // outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
        (*llIns2)[zz2] = (*lloIns2)[zz2];
    //    outs() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
     //          << (*lloIns2)[zz2] << "\n";
        zz2++;
      }
    }

  }
   else // if current load value operand is previous load ins
  // this else check is just to check for the detection of laod use-def
  // continous chains untill we hit store
  {
    // auto llo = loins->getOperand(0);
    // auto lloInsOp =dyn_cast<Instruction>(llo); // load instruction's operand
    // as instruction
    //  since load_instrn_list.size()==1 the llo should be present in
    //  pointer_vars_vec
    /////////////// // first need to copy the outset of predscessor load instrn
    ///into current load insrn inset
    auto predloadout = &((Outset.find(predload))->second);
    auto curloadin = &((Inset.find(loins))->second);
    for (auto pp3 : pointer_vars_vec) {
      zz2 = 0;
      while (zz2 < zz1) {
        // outs() << "\n21\n";
        ((curloadin->find(pp3))->second)[zz2] =((predloadout->find(pp3))->second)[zz2];
        zz2++;
      }
    }

    // then we need to do copy current load instrnm inset to the outset

    auto curloadout = &((Outset.find(loins))->second);
    for (auto pp3 : pointer_vars_vec) {
      zz2 = 0;
      while (zz2 < zz1) {
        // outs() << "\n21\n";
        ((curloadout->find(pp3))->second)[zz2] =
            ((curloadin->find(pp3))->second)[zz2];
        zz2++;
      }
    }
     ///#########@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@##############################
    // then we need to do gen set updation in current instrn outset
    //here just don't blindly copy the points to set of operand into instrn 
    // because then there is no concept of indirection or derfrencing
    // need to go inside teh points to set of the elements in teh points to set of opernad 
    // and that is one level derefrencing
    if (pointer_vars.find(curloadop) != pointer_vars.end()) { // this wiill always be true
      // do change in the outset of this load instrn
      auto lloIns1 = &((Outset.find(loins))->second);
      auto lloIns2 = &(((*lloIns1).find(curloadop))->second); // extract out the points to
      // info of load instrn operand
      // this info will be copied onto the points to info load instrn
      auto llIns2 = &(((*lloIns1).find(loins))->second);
      int count3 = 0;
      for (auto xx3 : *lloIns2)
      {
      if((*lloIns2)[count3]=='1')
      {
        // acces correspondingh instruction
        auto xx4= prog_vars[count3];
        zz2 = 0;
        auto xx5= &(((*lloIns1).find(xx4))->second);     
      while (zz2 < zz1) {
        // outs() << "\n21\n";
        // outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
        (*llIns2)[zz2] = (*xx5)[zz2];
      //  outs() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
       //        << (*xx5)[zz2] << "\n";
        zz2++;
      }

      }
        count3++; 
        }

      
    }
  

///#####################################################################
        // HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET

        // zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            if (((crinstOUT->find(pp3))->second)[zz2] !=
                ((crinst->find(pp3))->second)[zz2]) {
              if (WYAS != '1') // WYAS= WHY ADD SUCCESORS
              {
                WYAS = '2'; // succesors are added because of THERE WAS CHANGE
                            // DUE INFO GENERATED BUT NO NEW INFO CAME IN AT
                            // ENTRY OF THIS BB
                break;
              }
            }
            zz2++;
          }
          if (WYAS = '2')
            break;
        }
        if (WYAS == '2') {
          for (auto xx : successors(l1)) {
            list.push_back(xx);
          }
          WYAS = '0';
        }


  }





  // this is identity transfer function
  //auto crinstIN = crinst;                              // points to map
  //auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

  //zz2 = 0;
  //for (auto pp3 : pointer_vars_vec) {
   // zz2 = 0;
   // while (zz2 < zz1) {
      // outs() << "\n21\n";
     // ((crinstOUT->find(pp3))->second)[zz2] =
     //     ((crinstIN->find(pp3))->second)[zz2];
    //  zz2++;
   // }
   // outs() << "for variable: " << pp3->getNameOrAsOperand() << "\n";
   // outs() << " current instrn OUTSET is:\n";
   // zz2 = 0;
    //while (zz2 < zz1) {
      // outs() << "\n21\n";
     // outs() << ((crinstOUT->find(pp3))->second)[zz2] << ",";
     // zz2++;
   // }
        predload = loins; // put current instrn in predload
} // whole load instrn list is processed

  /// important to clear out the load instrn list
/// once the list has been processed

if(stvoIns==predload) // when yu hit the store inst and the last load ins in thi schain is used as the value operand in that store ins
{ // the stvo points to =stpo points to
  auto predloadout = &((Outset.find(predload))->second);
  // copy this load instrn's outset into store instrn's inset.
  auto stInsin = &((Inset.find(&*inspp1))->second);

  for (auto pp3 : pointer_vars_vec) {
    zz2 = 0;
    while (zz2 < zz1) {
      // outs() << "\n21\n";
      ((stInsin->find(pp3))->second)[zz2] = ((predloadout->find(pp3))->second)[zz2];
      zz2++;
    }
        }
        // copy this instrn inset into its outset
        auto stInsout = &((Outset.find(&*inspp1))->second);
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            ((stInsout->find(pp3))->second)[zz2] =
                ((stInsin->find(pp3))->second)[zz2];
            zz2++;
          }
        }
   
    // kill set
        // for outset of this store instrn  for stpo i.e store instrn pointer
        // operand kill the prior info.
        zz2 = 0;

        while (zz2 < zz1) {
          // outs() << "\n21\n";
          ((stInsout->find(stpoIns))->second)[zz2] = '0';
          zz2++;
        }
        // update teh outset of this store instrn by gen set
        zz2 = 0;

        while (zz2 < zz1) {
          // outs() << "\n21\n";
          ((stInsout->find(stpoIns))->second)[zz2] =((stInsout->find(predload))->second)[zz2];
          zz2++;
        }

        ///#####################################################################
        // HERE DETECT WHETHER THERE IS A CHANGE IN OUTSET

        // zz2 = 0;
        for (auto pp3 : pointer_vars_vec) {
          zz2 = 0;
          while (zz2 < zz1) {
            // outs() << "\n21\n";
            if (((crinstOUT->find(pp3))->second)[zz2] !=
                ((crinst->find(pp3))->second)[zz2]) {
              if (WYAS != '1') // WYAS= WHY ADD SUCCESORS
              {
                WYAS = '2'; // succesors are added because of THERE WAS CHANGE
                            // DUE INFO GENERATED BUT NO NEW INFO CAME IN AT
                            // ENTRY OF THIS BB
                break;
              }
            }
            zz2++;
          }
          if (WYAS = '2')
            break;
        }
        if (WYAS == '2') {
          for (auto xx : successors(l1)) {
            list.push_back(xx);
          }
          WYAS = '0';
        }




load_instrn_list.clear();
}// if stvoIns == last load instrn in the chain
else 
if(predload==stpoIns)// if last load instrn in the chain is pointer operand of the current store instrn 
{
// then also inset needs to be flown out to outset
// this is identity transfer function





    auto crinstIN = crinst; // points to map
           auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

               zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                   zz2++;
                 }
            //     outs() << "for variable: " << pp3->getNameOrAsOperand()<< "\n";
            //     outs() << " current instrn OUTSET is:\n";
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
             //       outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
                     zz2++;
                 }               
                 } 
}


} // if load_instrn_list.size>1
}// store instrn value operand is pointer at 0 dereference level  
 //}// if store instrn value operand's first level derefrence type is non pointer

else // if store instrn value operand is non pointer type ex: store <int/char/double/float> <ty>* %x
{   
  // then also inset needs to be flown out to outset
// this is identity transfer function
    auto crinstIN = crinst; // points to map
           auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

               zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                   zz2++;
                 }
              //   outs() << "for variable: " << pp3->getNameOrAsOperand()<< "\n";
             //    outs() << " current instrn OUTSET is:\n";
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                //    outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
                     zz2++;
                 }               
                 } 
}


     }// if instrn is a store instrn

     else // if instructon is not the store instrn
     // then also the inset of current instruction is needed to be copied to its outset.
     {
       // this is identity transfer function
           auto crinstIN = crinst; // points to map
           auto crinstOUT = &((Outset.find(&*inspp1))->second); // points to map

               zz2 = 0;
               for (auto pp3 : pointer_vars_vec) {
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
                   ((crinstOUT->find(pp3))->second)[zz2] =((crinstIN->find(pp3))->second)[zz2];
                   zz2++;
                 }
            //     outs() << "for variable: " << pp3->getNameOrAsOperand()<< "\n";
            //     outs() << " current instrn OUTSET is:\n";
                 zz2 = 0;
                 while (zz2 < zz1) {
                     // outs() << "\n21\n";
             //       outs()<< ((crinstOUT->find(pp3))->second)[zz2]<<",";
                     zz2++;
                 }               
                 }              
                 }

      
        // transfer function wll only decide what should a pointer variable must point to
        // the content in the load_instrn_list the transfer d=function will work.
        // all the parameters of this function are of refrence type to save memory and to do reflect back the changes 
        // after this transfer_func returns the changes has already made in the outset of the current instrn 

    PredInst = &(*inspp1); // catch the predecessor instrn
   
  } // iteration of the basic block is over
// outs() << "BB: " << l1->getNameOrAsOperand() << "is OVER!!!!"
           //<< "\n";

 //} // if halt='0' is over
    //else 
    //if(HALT=='2')
   // {
 // HALT = 0;
  // if halt=='1' break out of while loop
 // continue;
    //}
}// end of while loop for worklist algo

//need to print for the last BB last instrn outset
    
    //auto lbbinstrn = &(lastBB_BFS->back());
auto lbbinstrn = &((F.back()).back());
auto linstrnoutset = &(Inset.find(lbbinstrn)->second); // pointstomap
////////// the issue is in the previous line outset wqas not getting updated
///thus print inset.
//outs() << " last instrn is: ";
//lbbinstrn->dump();
///@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// need to print ths points to map
// auto lpt = linstrnoutset.back();
int ss1 = prog_vars.size();

int ss2 = 0;

//for (auto xx : pointer_vars_vec) {
  //outs() << ((pointer_vars.find(xx))->second)[0] << " ";
   // }
   /// for(auto xx: scalors_vec)
   // {
        //outs() << ((scalors_vars.find(xx))->second)[0]<<" ";
    //}
   // outs() << "\n";
   // for (auto xx : pointer_vars_vec) {
   //   outs() << ((pointer_vars.find(xx))->second)[0]<<" ";
   //   auto xx1 = (*linstrnoutset).find(xx);
   //   ss2 = 0;
   //   while (ss2 < ss1) {
   //   outs()<<" "<<(xx1->second)[ss2]<<" ,";
   //   ss2++;
   //   }
    //  outs() << "\n";
   // }

// printing the may points to info
// modified printing of pointstoset

//for (auto xx : pointer_vars_vec) {
 // outs() << ((pointer_vars.find(xx))->second)[0] << " ";
  //  }
  //  for(auto xx: scalors_vec)
   // {
     //   outs() << ((scalors_vars.find(xx))->second)[0]<<" ";
   // }
   // outs() << "\n";
outs() << "Points-to information as observed at the last program point in "
          "function Foo:"
       << "\n\n";
for (auto xx : pointer_vars_vec) {
  outs() << "Pointer Var " << ((pointer_vars.find(xx))->second)[0] << "={";
  auto xx1 = (*linstrnoutset).find(xx);
  ss2 = 0;
  while (ss2 < ss1) {
    if ((xx1->second)[ss2] == '1') {
      auto zz = prog_vars[ss2];
      if (pointer_vars.find(zz) != pointer_vars.end()) {
        outs() << ((pointer_vars.find(zz))
                       ->second)[0]; // prining label of each pointer
      } else if (scalors_vars.find(zz) != scalors_vars.end()) {
        outs() << ((scalors_vars.find(zz))
                       ->second)[0]; // prining label of each pointer
      }
      outs() << ",";
    }
    // outs() << " " << (prog_vars[ss2]) << " ,";

    ss2++;
  }
  outs() << "\b";
  outs() << "}";
  outs() << "\n";
}

// printing may points to matrix
    outs() <<"Alias relationships between the pointers in function Foo:" << "\n\n";
    char maypoints = 'N';
    int c = 0;
    //outs() << "\n";
    outs() << "\t\t";
    for (auto xx : pointer_vars_vec) {
      outs() <<((pointer_vars.find(xx))->second)[0] << "\t";
    }
    outs() << "\n";
    for (auto xx : pointer_vars_vec) {
      outs() << "Pointer Var "<< ((pointer_vars.find(xx))->second)[0]<<"\t";
      c = 0;
      auto xxr = &(((*linstrnoutset).find(xx))->second);
      for (auto xxxx : pointer_vars_vec) {
        maypoints = 'N';
        auto xxrr = &(((*linstrnoutset).find(xxxx))->second);
        ss2 = 0;
        if (xx == xxxx && c == 0) // if both the pointer varaiables are same
        {
          outs() << "Yes\t";
          maypoints = 'F'; // forced for reflexivity
          c = 1;
        }
else
{
        while (ss2 < ss1) {
            if (((*xxr)[ss2] == '1') && ((*xxrr)[ss2] == '1')) 
           {
            // outs() << (*xxr)[ss2] <<"  ,  ";
            // outs() << (*xxrr)[ss2];
            outs() << "Yes\t";
            maypoints = 'Y';
            break;
          }
          ss2++;
        }
        if (maypoints == 'N')
          outs() << "No\t";
     }
      }
     outs() << "\n";
    }





       // a matrix of size pointer_vars.size()*pointer_vars.size()

     } // if function has pointers
    // outset and inset population loop working fine now can access both the
    // set.

    else {
     // outs() << "  no pointer variable in the Function "<< "\n";
    }



      return false;
    
 }// end of bool runOn Function
}; // end of class;
char FlowSensitiveAA::ID = 10;
static RegisterPass<FlowSensitiveAA> X("fsaa","may points to analysis for certain transfer func like x=&a ; a could be pointer or scalor, x=y, x=*y where any level derefrencing can happen, *x=&b"); 

}