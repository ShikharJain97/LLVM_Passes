//simple programs to undestand LLVM -IR 
// loop: for
#include<stdio.h>
int main()
{
int i;
for(i=1;i<=30;i++)
{
if(i%3==0)
printf("Multiple of three %d",i);
}
}


