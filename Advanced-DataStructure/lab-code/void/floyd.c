#include<stdio.h> 
#define V 4 
#define INF 999 

void floydWarshall (int graph[][V]) 
{ 
	int dist[V][V], i, j, k; 

	for (i = 0; i < V; i++) 
		for (j = 0; j < V; j++) 
			dist[i][j] = graph[i][j]; 

	for (k = 0; k < V; k++) 
	{ 
		
		for (i = 0; i < V; i++) 
		{ 
			for (j = 0; j < V; j++) 
			{ 
				
				if (dist[i][k] + dist[k][j] < dist[i][j]) 
					dist[i][j] = dist[i][k] + dist[k][j]; 
			} 
		} 
	} 

	printf ("The following matrix shows the shortest distances"
			" between every pair of vertices \n"); 
	for (int i = 0; i < V; i++) 
	{ 
		for (int j = 0; j < V; j++) 
		{ 
			if (dist[i][j] == 999) 
				printf("%7s", "INF"); 
			else
				printf ("%7d", dist[i][j]); 
		} 
		printf("\n"); 
	} 
} 

 
int main() 
{ 
	int i,j,graph[V][V];
	printf("enter the weighted graph:\n");
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
