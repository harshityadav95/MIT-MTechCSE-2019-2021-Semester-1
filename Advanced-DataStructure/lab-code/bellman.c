#include<stdio.h>
#include<stdlib.h>

void Bellmanford(int graph[20][20],int V, int E,int edge[20][20]);

void main(){
int i,j,k=0,edge[20][20],graph[20][20],V;
printf("enter the no. of vertices:\n");
scanf("%d",&V);
printf("enter the graph in matrix form:\n");
for(i=0;i<V;i++)
{
for(j=0;j<V;j++)
{
scanf("%d",&graph[i][j]);
if(graph[i][j]!=0)
edge[k][0]=i, edge[k++][1]=j;
}
}
Bellmanford(graph,V,k,edge);
}

void Bellmanford(int graph[20][20],int V, int E,int edge[20][20])
{
int u,v,i,k;
int dist[20],s;
for(i=0;i<V;i++)
{
dist[i]=1000;
}
printf("enter the destination:\n");
scanf("%d",&s);
dist[s-1]=0;
for(i=0;i<V-1;i++)
{
	for(k=0;k<E;k++)
	 {
		u=edge[k][0], v=edge[k][1];
		if(dist[u] + graph[u][v] < dist[v])
		dist[v] = dist[u] + graph[u][v];
	}
}
for(i=0;i<V;i++)
{
printf("vertex = %d -> cost = %d",i+1,dist[i]);
printf("\n");
}
}