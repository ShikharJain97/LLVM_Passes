#include<stdio.h>

int main()
{
int arr[]={1,2,3,4,5};
int i;
int temp;
temp=arr[4];
for(i=3;i>=0;i--)
{
arr[i+1]=arr[i];
}
arr[0]=temp;

printf(" Array elements are %d %d %d %d %d ", arr[0],arr[1],arr[2],arr[3],arr[4]);
}


