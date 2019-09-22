#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<limits.h>

int partition(int *,int,int);
void quicksort(int *,int,int);
int * cutshort(int *,int);
int bitcount(int);

int main()
{
    int num,i;
    int *arr,*res;
    printf("\nCut Sort Algo :");
    printf("\nEnter the no. of elements enter 20 to use hardcoded values:");
    scanf("%d",&num);
    clock_t start,stop;
    printf("\nNow Enter the Elements :");
    arr = (int *) malloc(  sizeof( int ) * num );
    int a[20]={15,10,19,49,13,2,7,4,1,3,10,20,17,15,46,16,53,0,5,9};
    for(i=0;i<num;i++)
    {
        arr[i]=a[i];
    }
    start=clock();
    res=cutshort(arr,num);
    stop=clock();
  //  printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
  //  printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
  //  printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);
  /*  for(i=0;i<num;i++)
    {
        printf("%d\t",res[i]);
    }   */
    return 0;
}


int * cutshort(int *a,int n)
{
    int i,max,bitmax,pos;
    int *bitband,*resultant,*bitmap;
    clock_t start,stop;
 /*   for(i=1,max=a[0];i<n;i++)
    {
        if(max<a[i])
        {
            max=a[i];
        }
    }    */
    bitmax = 32;        //  bitcount(max);
    bitband = (int *) malloc(sizeof(int) * (bitmax + 1));
    for(i=0;i<=bitmax;i++)
        bitband[i]=0;
    bitmap = (int *) malloc(sizeof(int) * (bitmax + 1));
    for(i=0;i<=bitmax;i++)
        bitmap[i]=0;
    resultant = (int *) malloc(sizeof(int) * n);
    for(i=0;i<n;i++)
        resultant[i]=0;

    start=clock();
    for(i=0;i<n;i++)
    {
        bitband[ bitcount(a[i]) ] += 1 ;
    }
    printf("\nPrinting the Bitband Array :");
    for(i=0;i<n;i++)
    {
        printf("%d ",bitband[i] );
    }

 /*   printf("\n\n\n");
    for(i=0;i<=bitmax;i++)
        printf("count of %d bit numbers : %d \n",i,bitband[i]);
*/


    for(i=1;i<=bitmax;i++)
        bitband[i] += bitband[i-1];


 printf("\nModified Bitband Array :");
    for(i=0;i<n;i++)
    {
        printf("%d ",bitband[i] );
    }

   for(i=0;i<n;i++)
    {
        pos=bitcount(a[i]);
        resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = a[i];
        bitmap[pos] += 1;
    }

    printf("\nresultant array is :\n");
    for(i=0;i<n;i++)
    {
        printf("%d ",resultant[i] );
    }



 /*   stop=clock();
    printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
    printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
    printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);     */

  /*  for(i=1;i<=bitmax;i++)
    {
        quicksort(resultant,bitband[i-1],bitband[i]-1);
    }

    stop=clock();

    printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
    printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
    printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);


    // freeing the memory
    free(bitband);
    free(bitmap);8\*/
    return resultant;

}


int bitcount(int num)
{


    unsigned int count1=0,count2=0, tmp,value=4278190080U,result;
    // checking the byte no. of register
    if(num==0)
        return 0;
    while(!(num & value))
    {
       value = value >> 8;
       count1++;
    }

    value = 2147483648U;
    tmp=count1;

    // moving the first bit to proper byte
    while(tmp--)
    {
        value = value >> 8;
    }

    // moving the bit in a particular byte
    while(!(num & value))
    {
        value = value >> 1;
        count2++;
    }
    result = 32 - (count1 * 8 + count2);
    return result;
}

int partition(int *a,int p,int r)
{
    int pivot,i,j,tmp;
    pivot=a[r];
    for(i=p,j=p;j<r;j++)
    {
        if(a[j]<pivot)
        {
            tmp=a[j];
            a[j]=a[i];
            a[i]=tmp;
            i++;
        }
    }
    a[r]=a[i];
    a[i]=pivot;
    return i;
}

void quicksort(int *a,int p,int r)
{
    if(p<r)
    {
        int q;
        q = partition(a,p,r);
        quicksort(a,p,q-1);
        quicksort(a,q+1,r);
    }
}
