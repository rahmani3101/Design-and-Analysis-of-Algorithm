#include<stdio.h>
int main()
{
	int a,c=0;
	printf("Enter a number");
	scanf("%d",&a);
	for(int i =1;i<=a/2;i++)
	{
		if(a%i==0)
		{
			c++;
		}
	}
	if(c==1)
		printf("prime number");
	else
		printf("not a prime");
	return 0;
}
