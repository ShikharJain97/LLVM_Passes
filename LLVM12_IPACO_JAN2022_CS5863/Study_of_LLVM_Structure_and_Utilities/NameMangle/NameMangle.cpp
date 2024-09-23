// functio overloading
// to see the effects of name mangling(mapping original function identifier into compiler generated name that has coded information for call resolution) done in cpp code
#include <iostream>
using namespace std;

int func1(int a, int b );
int func1(int a);
double func1(double a , float b);

int func1(int a, int b)
{
    return a+b;
}

int func1(int a)
{
return a*a*a;
}

double func1(double a, float b)
{
return a-b;
}
int main()
{
    int a=10,b=20;
    float c=6.78f;
    double d=88.66565;
cout<<"This is func1(int a,int b) call "<< func1(a,b)<<"\n";
cout<<"This is func1(int a) call "<< func1(a)<<"\n";
cout<<"This is func1(double a, float b) call "<< func1(d,c)<<"\n";
}
