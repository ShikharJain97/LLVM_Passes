#include<stdio.h>
int main()
{

int i,j,k,l;
float y=9.2;
for(i=0;i<10;i++)
{
	for(j=0;j<10;j++)
	{
		y++;
	}
}

for(i=0;i<10;i++)
{
	for(k=0;k<100;k++)
	{
		for(l=0;l<10;l++)
		{
			y--;
		}
		for(j=0;j<19;j++)
		{
			y++;
		}

	}
	for(k=0;k<10;k++)
	{
		y--;
	}
}


}
