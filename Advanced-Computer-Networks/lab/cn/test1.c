#include<stdio.h>
#include<stdlib.h>
int a[10][10],n,d,b;
float c[10][10];
float t[10][10];
void func();
void dsdv();
int main()
{
	int i,j,k;
	printf("no of nodes:\n");
	scanf("%d",&n);
	printf("adjacency\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	
	printf("Cost:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%f",&c[i][j]);

		}
	}

    func();

	dsdv();
	// taking the sample node 1 -5
	//scanf("%d %d",&d,&b);
	a[0][4]=1;
	a[4][0]=1;
	c[0][4]=2.0;
	c[4][0]=2.0;
	func();
	dsdv();
	return 0;

}


void dsdv()
{
	int i,j,k;


	
for(k=0;k<n;k++)
{
	for(i=0;i<n;i++)
{
	for(j=0;j<n;j++)
	{
		if(t[i][j]>t[i][k]+t[k][j])
			t[i][j]=t[i][k]+t[k][j];
	}
}
}

	printf("The routing table:\n");
	printf("%.2f\t",t[0][4]);
		
		
	



}
void func()
{
	int i,j;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[i][j]==1)
			{
			 	if(i==j)
			 		t[i][j]=0;
			 	else

				t[i][j]=c[i][j];
			}
			else
				t[i][j]=999;
		}
	}
}