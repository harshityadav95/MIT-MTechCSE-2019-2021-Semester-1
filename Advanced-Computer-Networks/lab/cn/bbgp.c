#include<stdio.h>
#include<stdlib.h>
void main()
{
int a[10][10],b[10][10],n,i,j,k;
printf("enter the num of elements:");
scanf("%d",&n);
for(i=0;i<n;i++)
{
 for(j=0;j<n;j++)
 {
  scanf("%d",&a[i][j]);
 }
}
for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
   {
    b[i][j]=a[i][j];
    if(i==j)
      b[i][j]=0;
   }
 }

 
  for(i=0;i<n;i++)
   {
    for(j=0;j<n;j++)
    {
     for(k=0;k<n;k++)
      {
       if(b[i][j]>b[i][k]+b[k][j])
        {
          b[i][j]=b[i][k]+b[k][j];
        }
      }
    }
 }
printf("after :\n");
for(i=0;i<n;i++)
{
 for(j=0;j<n;j++)
 {
  printf("%d\t",b[i][j]);
 }
 printf("\n");
}
}

