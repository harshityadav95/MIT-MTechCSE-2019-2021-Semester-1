#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[4][10];
	int pro;
	printf("Enter the number of process :");
	scanf("%d",&pro);
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<2;j++)
			scanf("%d",&a[i][j]);

	}
	int count=pro;
	int time=0;
	for(int t=0;count>0;t++)
	{
		for(int i=0;i<pro;i++)
		{
			if(a[i][0]==t)
			{
				count--;
				//printf("\n %d Arrival time at clock %d ",a[i][0],time);
				if(t>time)time+=(t-time);
				time+=a[i][1];
				a[i][3]=time-a[i][1]-a[i][0];
				//printf("%d Time elapsed",time);
				a[i][2]=time-a[i][0];
		


			}
		}

	}
	printf("\n AT -- BT -- TAT -- WT \n");
	for(int i=0;i<pro;i++)
	{
		for(int j=0;j<=3;j++)
			printf("%d -- ",a[i][j]);
		printf("\n");

	}
}