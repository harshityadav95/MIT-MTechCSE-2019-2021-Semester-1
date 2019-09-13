#include<stdio.h>
#include<stdlib.h>
void dijkstra(int a[][],int n, int start)
{
	g
	
}
int main()
{
	int n,a[10][10], start;
	printf("\nEnter the Number of Nodes");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			scanf("%d",&a[i][j]);
	}
	//	now printing the output
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			printf("%d ",a[i][j]);
		printf("\t");
	
	}
	printf("\n Enter the Source Node : " );  
	scanf("%d",start);
	dijkstra(a,n,start);		
    return 1;

}
