
#include <stdio.h>
// function prototypes
int func1(int a , int b);
double func2(int*a, int* b);
int func3(int a);

//function definitions
int func1(int a, int b)
{
    int x;
    x=a*b+(b-10)/71;
    return x;
}

double func2(int *a, int *b)
{
    
    *a=func1(*a,*b)+(*b-*a);
    return (*a*(5.66));
}

int func3(int a)
{
return 65+((a+10)*77)%26;
}

int main()
{
    int a=20;
    int b=300;
printf("%f",func2(&a,&b));
printf("\n");
printf("%c",func3(a));
return 0;
}
