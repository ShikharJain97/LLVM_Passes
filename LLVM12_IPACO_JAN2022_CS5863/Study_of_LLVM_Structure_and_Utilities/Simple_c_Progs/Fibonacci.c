// nth fibonacci-number
// to see effect over tail recursion 
#include<stdio.h>
#include<stdlib.h>

#define n 2

int fibo(int a)
{
if(a<=0)
return -1;
else
if(a==1)
return 0;
else
if(a==2)
return 1;
else
return (fibo(a-1)+fibo(a-2));

}


int main()
{
int a=0,b=1; // invariants to start the sequence
printf("n = %d and fibo(n) = %d ",n,fibo(n));

}