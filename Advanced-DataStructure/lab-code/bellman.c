#include<stdio.h>
#include<stdlib.h>
void Bellmanford(int graph[10][10],int V, int E,int edge[10][10]);
void main()
{
	int i,j,k=0,edge[10][10],graph[10][10],V;
	printf("No.of nodes :");
	scanf("%d",&V);
	printf("Graph weights:\n");
	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
		{
			scanf("%d",&graph[i][j]);
			if(graph[i][j]!=0)
			edge[k][0]=i,
			edge[k++][1]=j;
		}
	}
	Bellmanford(graph,V,k,edge);
}
void Bellmanford(int graph[10][10],int V, int E,int edge[10][10])
{
	int u,v,i,k;
	int dist[10],s;
	for(i=0;i<V;i++)
	{
		dist[i]=1000;
	}
	printf("Source is 1 enter the destination:\n");
	scanf("%d",&s);
	dist[s-1]=0;
	for(i=0;i<V-1;i++)
	{
		for(k=0;k<E;k++)
		{
			u=edge[k][0], v=edge[k][1];
			if(dist[u] + graph[u][v] < dist[v])
			{	
				dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	for(i=0;i<V;i++)
	{
		printf("Distance from vertex = %d to destination %d = %d",i+1,s,dist[i]);
		printf("\n");
	}
}
