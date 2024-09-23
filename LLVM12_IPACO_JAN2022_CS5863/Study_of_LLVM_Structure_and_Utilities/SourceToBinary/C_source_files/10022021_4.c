// for asm
// 1) statically allocated memory 2) dynamically allocated memory 3) pointer indirection (single and double) 4) C -type  structres  

#include<stdio.h>
#include<stdlib.h>

typedef struct Dummy_struct{
int x;
} DS;





int main()
{

int St_ar[5]={1,2,3,4,5};
int *S_p=NULL;
int c=100;
int** D_p=NULL;
S_p=&c;
D_p=&S_p;

DS ob1;


int *Dy_ar=(int*)malloc(sizeof(int)*5);
Dy_ar[0]=10;
Dy_ar[1]=20;
Dy_ar[2]=30;
Dy_ar[3]=40;
Dy_ar[4]=50;

printf(" %d %d %d",c,*S_p,**D_p);

for(int i=0;i<5;i++)
printf("%d ",St_ar[i]+Dy_ar[i]);

ob1.x=1000;
printf("%d",ob1.x);

}

