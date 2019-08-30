#include <stdio.h> 
#include <limits.h> 
#include <stdlib.h>
  
#define bool int
#define true 1
#define false 0
 
#define V 5 
  
 
int minDistance(int dist[],  
                bool sptSet[]) 
{ 
       
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < V; v++) 
        if (sptSet[v] == false && 
                   dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 
  
void printPath(int parent[], int j) 
{ 
       
    if (parent[j] == - 1) 
        return; 
  
    printPath(parent, parent[j]); 
  
    printf("%d ", j); 
	
} 
  
 
void printSolution(int dist[], int n,  
                      int parent[],int src) 
{ 
    //int src = 0;
	int i;
	int arr[V],dest;
    printf("Ënter the destination\n");
	scanf("%d",&dest);
	printf("\n");
	printf("Shortest path from source %d to destination %d : ",src,dest);
	printf("%d ",src);
    printPath(parent, dest); 
	for(i=0;i<V;i++)
	{
		arr[i] = dist[i];
    }
	printf("\n");
	printf("Cost is : %d\n",arr[dest]);
} 
  
 
void dijkstra(int graph[V][V], int src) 
{ 
      
     
    int dist[V];  
 
    bool sptSet[V];  
    int parent[V]; 
  
    for (int i = 0; i < V; i++) 
    { 
        parent[src] = -1; 
        dist[i] = INT_MAX; 
        sptSet[i] = false; 
    } 
   
    dist[src] = 0; 
   
    for (int count = 0; count < V - 1; count++) 
    {  
        int u = minDistance(dist, sptSet); 
  
        sptSet[u] = true; 
   
        for (int v = 0; v < V; v++)  
            if (!sptSet[v] && graph[u][v] && 
                dist[u] + graph[u][v] < dist[v]) 
            { 
                parent[v] = u; 
                dist[v] = dist[u] + graph[u][v]; 
            }  
    }  
    printSolution(dist, V, parent, src); 
} 
  
// Driver Code 
void main() 
{ 
   
	int src,graph[V][V],i,j;
                 
	printf("Enter the adjacency matrix\n");

	for(i=0;i<V;i++)
		for(j=0;j<V;j++)
			scanf("%d",&graph[i][j]);
  
	printf("Enter the source\n");
	scanf("%d",&src);
    dijkstra(graph, src); 
	system("pause");
    //return 0; 
} 
