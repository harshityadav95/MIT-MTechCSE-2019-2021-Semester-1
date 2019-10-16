#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[5][8];
	a[0][0]=1;a[0][1]=0;a[0][2]=11;a[0][3]=2;
	a[1][0]=2;a[1][1]=5;a[1][2]=28;a[1][3]=0;
	a[2][0]=3;a[2][1]=12;a[2][2]=2;a[2][3]=3;
	a[3][0]=4;a[3][1]=2;a[3][2]=10;a[3][3]=1;
	a[4][0]=5;a[4][1]=9;a[4][2]=16;a[4][3]=4;
int b[5];
b[0]=11;
b[1]=28;
b[2]=2;
b[3]=10;
b[4]=16;




	//p
	/*for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; i < 4; ++i)
		{
			scanf("%d",a[i][j]);
		}
	}*/

	printf("\n PID -- AT-- BT-- Priority--FT--TAT--CT");
	printf("\n");
	for (int i = 0; i < 5; ++i)
	 {
			   	for (int j=0 ; j < 4; j++)
				   	{
				   		printf("%d -- ",a[i][j]);
				   	}
				   	printf("\n");

	}	
		printf("\n");	printf("\n");

	int n=5;
	int count=n;
	int time=0;
	int atat=0;
	int act=0;
	int time_qunatum=1,waiting_time;
	for(int t=0;count>0;t++)
	{
		int min=999;
		int pid=0;
		for(int i=0;i<5;i++ )
		{
			if(a[i][1]<=t && a[i][2]!=0 && a[i][3]<min)
			{
				min=a[i][3];
				pid=i;

			}
		}
		if(t>time)
		{
			time+=t-time;
		}
		if(a[pid][2]!=0)
		{
			a[pid][2]=a[pid][2]-time_qunatum;
			time+=time_qunatum;
			if(a[pid][2]==0)
			{
				a[pid][4]=time;

				a[pid][5]=a[pid][4]-a[pid][1];
				atat+=a[pid][5];
				a[pid][6]=a[pid][5]-b[pid];
				act+=a[pid][6];
				a[pid][7]=a[pid][6]-b[pid]-a[pid][1];

				count--;
			}
		}
	
	}
	printf("\n PID -- AT-- BT-- Priority--FT--TAT--CT");
	printf("\n");	printf("\n");
	for (int i = 0; i < 5; ++i)
	   {
			   	for (int j=0 ; j < 8; ++j)
				   	{
				   		printf("%d -- ",a[i][j]);
				   	}
				   	printf("\n");

	}
	
	   float temp1=(atat*0.1)/(5.0);  
	  printf("\n avg TAT=%f",temp1);
	
	    temp1=(act*0.1)/(5.0);    
	 printf("\n avg CAT=%f",temp1);
	
	return 0;
}