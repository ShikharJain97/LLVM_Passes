// for asm check
// will have all the branching constructs defined for c 
// 1)if-else ladder 2) switch case 
#include <stdio.h>

int main()
{
int aa=10;
int bb=20;
int cc;


if(aa>bb)
{
cc=aa*bb+100;
}
else
{
cc=aa-bb;
}

aa=(char)((aa+75)%26);

switch(aa)
{
case('K'):
printf("a is %c and c is %d ",aa,cc); 
case('A'):
printf("a is not %c c is %d ",aa,cc);
default:
printf("oops");
}



}



