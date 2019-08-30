#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a[10][10],c[10][10],t[10][10],i,j,k,n;
	printf("enter the num of nodes:\n");
	scanf("%d",&n);
	printf("enter the adjacency matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}

	printf("enter the cost matrix:\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&c[i][j]);
		}
	}
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

	for(i=0;i<n;i++)
	{

		printf("from node %d ",i);
		for(j=0;j<n;j++)
		{
			printf("%d\t",t[i][j]);
		}
		printf("\n");
	}


return 0;
}