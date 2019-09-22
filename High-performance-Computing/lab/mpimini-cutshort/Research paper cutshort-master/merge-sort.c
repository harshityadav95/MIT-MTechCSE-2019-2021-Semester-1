#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<limits.h>

void merge_sort(int *,int,int);
void merge(int *,int,int,int);

int main()
{
    int num,i;
    int *arr;
    clock_t start,stop;
    scanf("%d",&num);
    arr = (int *) malloc(  sizeof( int ) * num );
    for(i=0;i<num;i++)
    {
        scanf("%d",&arr[i]);
    }
    start=clock();
    merge_sort(arr,0,num-1);
    stop=clock();
    printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
    printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
    printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);

/*    for(i=0;i<num;i++)
    {
        printf("%d\t",arr[i]);
    }
    return 0;
*/
}

void merge_sort(int *a,int p,int r)
{
    if(p<r)
    {
        int q;
        q = (p+r)/2;
        merge_sort(a,p,q);
        merge_sort(a,q+1,r);
        merge(a,p,q,r);
    }
}


void merge(int *a,int p,int q,int r)
{
    int n1,n2,*b,*c;
    int i,j,k;
    n1=q-p+1;
    n2=r-q;
    b=(int *) malloc(  sizeof(int) * (n1+1));
    c=(int *) malloc(  sizeof(int) * (n2+1));
    for(i=0;i<(n1);i++)
        b[i] = a[p+i];
    for(i=0;i<(n2);i++)
        c[i] = a[q+1+i];

    b[n1]=INT_MAX;
    c[n2]=INT_MAX;
    for(i=0,j=0,k=p;k<=r;k++)
    {
        if( b[i]<c[j] )
        {
            a[k]=b[i];
            i++;
        }
        else
        {
            a[k]=c[j];
            j++;
        }
    }

}
