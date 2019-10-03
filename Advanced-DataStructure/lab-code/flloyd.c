#include<stdio.h> 
#include<stdlib.h>
#define V 4 
#define INF 999 
void floydWarshall (int graph[][V]); 
int main() 
{ 
	int i,j,graph[V][V];
	printf("Enter Value :\n");
	for(i=0;i<V;i++)
	{
		for(j=0;j<V;j++)
	   	 {
			scanf("%d",&graph[i][j]);
		 }
	}
	
	floydWarshall(graph); 
	return 0; 
}
void floydWarshall (int graph[][V]) 
{ 
	int dist[V][V], i, j, k; 
	for (i = 0; i < V; i++) 
	{
		for (j = 0; j < V; j++)dist[i][j] = graph[i][j]; 
	}		
	for (k = 0; k < V; k++) 
	{		
		for (i = 0; i < V; i++) 
		{ 
			for (j = 0; j < V; j++) 
			{ 
				if (dist[i][k] + dist[k][j] < dist[i][j]) dist[i][j] = dist[i][k] + dist[k][j]; 
			} 
		} 
	} 
	printf ("shortest distances \n"); 
	for (int i = 0; i < V; i++) 
	{ 
		for (int j = 0; j < V; j++) 
		{ 
			if (dist[i][j] == 999) 
			{
				printf("%s", "INF"); 
			}
				
			else
			{
				printf ("%d      ", dist[i][j]);
			}
				 
		} 
		printf("\n"); 
	} 
} 
 
