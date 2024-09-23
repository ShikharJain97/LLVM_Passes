//for asm
// 1) for loop 2) while loop 3) do-while loop 4) looping via goto

#include <stdio.h>
int main()
{
int start=0,end=10,jump1=1,jump2=2,jump3=3,end_goto_flag=0,work=0;

for(;start<end;start+=start+jump1)
work+=start;

printf(" For loop work %d",work);

work=0;
while(start<end)
work-=jump2;

printf(" while loop work %d",work);

work=0;
do
{
work*=jump3;
}while(start<end);

printf(" do-while loop work %d",work);

l1:
if(start < end)
{
printf(" goto %d",start);
start+=2;
}
else
goto l2;

goto l1;

l2:
return 0;
}

