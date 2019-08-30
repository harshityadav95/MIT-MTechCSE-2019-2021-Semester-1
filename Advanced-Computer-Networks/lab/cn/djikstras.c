#include<stdio.h>
//#include<stdlib.h>

void dj(int D[10][10],int n,int start,int end);
 
void main()
{
  int D[10][10],i,j,n,u,s;
  printf("Enter num of vetices:\t");
 scanf("%d",&n);
 printf("enter the matrix:\n");
 for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
    {
      scanf("%d",&D[i][j]);
    }
  }

 printf("enter the start node:\t");
 scanf("%d",&s);
 dj(D,n,s);
 
}

void dj(int D[10][10],int n,int start)
{

 int cost[10][10],p[20],dist[20],i,j,visited[20],count,mindistance,nextnode;
 for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
     {
       if(D[i][j]==0)
         {
           cost[i][j]==9999;
          }
       else
          {
            cost[i][j]=D[i][j];
           }
       }
   }
for(i=0;i<n;i++)
{
  dist[i]=cost[start][i];
  p[i]=start;
  visited[i]=0;
  
}

dist[start]=0;
visited[start]=1;
count=1;

while(count<n-1)
{
  mindistance=999;

 for(i=0;i<n;i++)
   {
     if(dist[i]<mindistance && !visited[i])
        {
           mindistance=dist[i];
           nextnode=i;
         }
}
visited[nextnode]=1;
for(i=0;i<n;i++)
{
 if(!visited[i])
{
 if(mindistance+cost[nextnode][i] < dist[i])
   {
     dist[i]=mindistance+cost[nextnode][i];
     p[i]=nextnode;
   }

}

}
count++;
}  

for(i=0;i<n;i++)
 {
 if(i!=start)
   {
 printf("\ndistance of node %d is %d\n",i,dist[i]);
     printf("\n path = %d",i);
     j=i;
   
     do{     
 
        j=p[j];
 printf(" <-%d",j);
    }while(j!=start);

   }
 }

}           

 




