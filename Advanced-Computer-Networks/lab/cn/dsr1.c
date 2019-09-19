#include <stdio.h>
#include <stdlib.h>

int p[10][10],q[10];



void findpred(int parent[],int v,int i)
{
int count=0;
int j=0;
while(v>=0)
{

p[i][j]=v+1;
v=parent[v];
j++;
count++;
}

q[i]=p[i][count-2];

}



void Bellman_Ford(int G[20][20] , int V, int E, int edge[20][2])
{
    int i,u,v,k,distance[20],parent[20],S;
    for(i=0;i<V;i++)
        distance[i] = 1000 , parent[i] = -1 ;
        printf("Enter destination: ");
        scanf("%d",&S);
        distance[S-1]=0 ;
    for(i=0;i<V-1;i++)
    {
        for(k=0;k<E;k++)
        {
            u = edge[k][0] , v = edge[k][1] ;
            if(distance[u]+G[u][v] < distance[v])
                distance[v] = distance[u] + G[u][v] , parent[v]=u ;
        }
    }
for(i=0;i<V;i++)
findpred(parent,i,i);
q[S-1]=S;
            for(i=0;i<V;i++)
{
                printf("Vertex %d -> cost = %d successor = %d  pred = %d",i+1,distance[i],parent[i]+1,q[i]);

printf("\n");
}
           
           

           
       
}
void main()
{
    int V,edge[20][2],G[20][20],i,j,k=0;
    printf("Enter no. of vertices: ");
    scanf("%d",&V);
    printf("Enter graph in matrix form:\n");
    for(i=0;i<V;i++)
        for(j=0;j<V;j++)
        {
            scanf("%d",&G[i][j]);
            if(G[i][j]!=0)
                edge[k][0]=i,edge[k++][1]=j;
        }

    Bellman_Ford(G,V,k,edge);
   
}