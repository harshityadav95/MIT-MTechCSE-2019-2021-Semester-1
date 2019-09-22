#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void InsertionSort(int[],int,int);

int main()
{
  int n,i;
  int *A;
  clock_t start,stop;
  scanf("%d",&n);
  A = (int *) malloc(sizeof(int)*n);
  printf("\n Sorting :\n");
  for(i=0;i<n;i++)
    scanf("%d",&A[i]);
  start=clock();
  InsertionSort(A,0,n);
  stop=clock();
  printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
  printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
  printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);

  //for(i=1;i<100001;i++)
    //printf("%d  ",A[i]);
  return 0;
}

void InsertionSort(int *arr,int low,int high)
{
    int x,y,temp;
    for(x=low+1;x<=high;x++)
    {
            y = x-1;
            temp=arr[x];
            while(y>=low && arr[y]>temp)
            {
                arr[y+1]=arr[y];
                y=y-1;
            }
            arr[y+1]=temp;
    }
}

