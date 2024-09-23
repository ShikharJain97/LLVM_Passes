echo 'Assign 1 bash file. this file has all the commands needed to generate all the files present in the Assign1 folder'
printf "\n"
echo 'the file will use soft links to cope with long path names'
printf "\n"
echo 'All the visual file are just rendered using xdot . they are not saved hence it may happn that many visual files instantly pop up on the screen'
printf "\n"
echo 'it is assumed that the llvm-project folder in your machone is present in /home . if it isnt than pls change accordingly the commands in bash file.'
printf "\n"
echo 'unzip the tarball in your home directory cause it will serve as base location of source files'.
printf "\n"
echo 'the directory structure present their is assumed . the generated output files will be stored in a similar directory structure with added TEST_ before their name and T_ for files.'
printf "\n"
echo 'first task of generating and understanding llvm ir for 5 no trivial programs is based on folder Simple_c_Progs'
printf "\n"
echo 'corresponding .ll files will be stored in that folder only'
printf "\n"
echo ' for task 2 NameMangle folder has a .cpp file and will contain corresponding .ll file'
printf "\n"
echo ' for task 3 i.e to generate all intermediate files for a set of programs , the base folder is SourceToBinary in that the c source files are present in folder c_source_files.'
 
echo ' generating soft links '
printf " llvm build \n"
echo 'ln -s /home/shikharj/llvm-project/build/bin Base0'
printf " .c source files \n"
echo 'ln -s /home/shikharj/CS5863_Program_Analysis_work SBase0'
printf " output files \n"
echo 'ln -s /home/CS22MTECH02002/CS5863_Program_Analysis/Assign1/ OBase0'
printf "\n"





cd /home
cd shikharj

mkdir CSMTECH02002_CS5863_Out
cd CSMTECH02002_CS5863_Out
mkdir Assign_1
cd Assign_1

mkdir Simple_c_Progs
mkdir Source_to_binary


cd /home
cd shikharj
cd llvm-project
cd build
cd bin 

echo 'generating LLVM - IR for five non - trivial programs'
printf "\n"


./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/Simple_c_Progs/MultOf3.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_MultOf3.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/Simple_c_Progs/Fibonacci.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_Fibonacci.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/Simple_c_Progs/Multi_func_call.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_Multi_func_call.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/Simple_c_Progs/ExpressionEval.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_ExpressionEval.c.ll
 
./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/Simple_c_Progs/array_right_circular_shift.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_array_right_circular_shift.ll

echo 'generating LLVM -IR for NameMangling'
printf"\n"

./clang++ -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/NameMangle/NameMangle.cpp -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Simple_c_Progs/T_NameMangle.ll


echo 'generating output --> 1) by preprocessor(.p) 2)--> AST (- ast-view) 3)--> LLVM-IR (OPTNONE)(-S -emit-llvm) 4)-->CFG & DOMTREE view 5)--> LLVM-IR Disable OPTNONE 6)-->OPT->mem2Reg 7)-->OPT->mem2Reg->dce 8)-->OPT->mem2Reg->sccp 9)-->opt->mem2Reg->sccp->dce.'

printf "\n"

echo 'preprocessed'

./clang -E /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_1.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1.i

./clang -E /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_2.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2.i

./clang -E /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_3.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3.i

./clang -E /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_4.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4.i

printf "\n"

echo 'AST' 
./clang -fsyntax-only -Xclang -ast-view /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_1.c
./clang -fsyntax-only -Xclang -ast-view /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_2.c
./clang -fsyntax-only -Xclang -ast-view /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_3.c
./clang -fsyntax-only -Xclang -ast-view /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_4.c

echo 'LLVM -IR(OPTNONE)'

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_1.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_ll_NoOPT.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_2.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_ll_NoOPT.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_3.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_ll_NoOPT.ll

./clang -S -emit-llvm /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_4.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_ll_NoOPT.ll

printf "\n"

echo 'LLVM - IR(OPTNONE DISABLE)'

./clang -S -emit-llvm -Xclang -disable-O0-optnone /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_1.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_ll_OPT_En.ll

./clang -S -emit-llvm -Xclang -disable-O0-optnone /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_2.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_ll_OPT_En.ll

./clang -S -emit-llvm -Xclang -disable-O0-optnone /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_3.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_ll_OPT_En.ll

./clang -S -emit-llvm -Xclang -disable-O0-optnone /home/shikharj/CS5863_Program_Analysis_work/Assign_1/SourceToBinary/C_source_files/10022021_4.c -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_ll_OPT_En.ll

printf "\n"
echo 'CFG and DOMTREE'
./opt --view-cfg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_ll_NoOPT.ll
./opt --view-cfg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_ll_NoOPT.ll
./opt --view-cfg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_ll_NoOPT.ll
./opt --view-cfg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_ll_NoOPT.ll

./opt --view-dom /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_ll_NoOPT.ll
./opt --view-dom /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_ll_NoOPT.ll
./opt --view-dom /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_ll_NoOPT.ll
./opt --view-dom /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_ll_NoOPT.ll

printf "\n"

echo 'opt->mem2Reg'

./opt -mem2reg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_ll_OPT_En.ll -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_M2R.bc
 
./opt -mem2reg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_ll_OPT_En.ll -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_M2R.bc

./opt -mem2reg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_ll_OPT_En.ll -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_M2R.bc

./opt -mem2reg /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_ll_OPT_En.ll -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_M2R.bc

echo ' opt-->mem2Reg->dce'

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_dce.bc
 
./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_dce.bc

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_dce.bc

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_dce.bc

printf "\n"

echo 'opt->mem2Reg-->sccp'

./opt -sccp /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp.bc

./opt -sccp /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp.bc

./opt -sccp /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp.bc

./opt -sccp /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_M2R.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp.bc

printf "\n"

echo 'opt->mem2Reg->sccp->dce'

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.bc

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp_dce.bc

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp_dce.bc

./opt -dce /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.bc

printf "\n"

echo ' choosing 10022021_1 for all of its optmized .bc files and same with 10022021_4 for transformation pass comparison'
printf "\n"
echo 'disassembling mem2reg .bc file'
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_M2R.bc
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_M2R.bc
printf "\n"

echo 'disassembling mem2reg->dce .bc file'
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_dce.bc
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_dce.bc

printf "\n"

echo 'disassembling mem2reg->sccp .bc file'
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp.bc
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp.bc

printf "\n"

echo 'disassembling mem2reg->sccp->dce .bc file'
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.bc
./llvm-dis /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.bc
printf "\n"

echo 'applying llc over all the 4 .bc files corresponding to 10022021_1_sccp_dce.bc 10022021_2_sccp_dce.bc 10022021_3_sccp_dce.bc 10022021_4_sccp_dce.bc to generate .s files with machine dependent assembly code'

./llc /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.bc
./llc /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp_dce.bc
./llc /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp_dce.bc
./llc /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.bc

printf "\n"

echo 'applying llvm-link over all the 4 .bc files corresponding to 10022021_1_sccp_dce.bc 10022021_2_sccp_dce.bc 10022021_3_sccp_dce.bc 10022021_4_sccp_dce.bc to generate .out executables'

./llvm-link /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.out 

./llvm-link /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp_dce.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp_dce.out 

./llvm-link /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp_dce.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp_dce.out 

./llvm-link /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.bc -o /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.out 

printf "\n"

echo 'applying lli to above mentioned .bc files'
./lli /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_1_sccp_dce.bc
./lli /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_2_sccp_dce.bc
./lli /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_3_sccp_dce.bc
./lli /home/shikharj/CSMTECH02002_CS5863_Out/Assign_1/Source_to_binary/T_10022021_4_sccp_dce.bc

printf "\n"

echo " @@@@@@@@@ A request if on execution of some command output file is not found in expected folder then pls check in your /llvm-project/build/bin @@@@@@@@@@@"
 


