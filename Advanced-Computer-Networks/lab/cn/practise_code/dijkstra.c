#include<stdio.h>
#include<stdlib.h>
int n=6, start=0;
int a[7][7]={
		{0,1,0,0,2,0},
		{1,0,1,0,0,4},
		{0,1,0,2,0,0},
		{0,0,2,3,0,3},
		{2,0,0,0,0,3},
		{0,4,0,3,3,0}};

void dijkstra()
{
	int cost[10][10],p[20],dist[20],i,j,visited[20],count,mindistance,nextnode;
 for(i=0;i<n;i++)
  {
    for(j=0;j<n;j++)
     {
       if(a[i][j]==0)
         {
           cost[i][j]==9999;
          }
       else
          {
            cost[i][j]=a[i][j];
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
int main()
{
	 
	//printf("\nEnter the Number of Nodes");
	//scanf("%d",&n);
		//n=6;
		//int a[n][n];
	//for(int i=0;i<n;i++)
	//{
	//	for(int j=0;j<n;j++);
			//scanf("%d",&a[i][j]);
	//}
	// hardcoding the number of the nodes

	// hardcoding the cost matrix 
	
	//	now printing the output
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
			printf("%d ",a[i][j]);
		printf("\n");
	
	}
	//printf("\n Enter the Source Node : " );  
	//scanf("%d",&start);
	dijkstra();		
    return 1;

}
