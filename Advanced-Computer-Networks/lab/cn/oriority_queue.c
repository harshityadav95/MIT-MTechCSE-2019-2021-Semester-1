#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[5][6];
	int count=5;
	int time=0;


	printf("\nENter the Priority, AT -- BT");
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			scanf("%d",&a[i][j]);
		}
	}
	for (int t = 0; count>0; ++t)
	{
		int id,min=0;
		for (int i = 0; i <5; ++i)
		{
			if(a[i][1]<=t && a[i][0]>min)
			{	min=a[i][0];
				id=i;
			}

		}
		if (t>time)
		{
			time+=t-time;
		}
		time+=a[id][2];
		a[id][3]=time;
		a[id][4]=a[id][3]-a[id][1];
		a[id][5]=a[id][4]-a[id][2];
		a[id][0]=-1;
		count--;
	}
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			printf("%d--",a[i][j] );
		}
		printf("\n");
	}


	
}