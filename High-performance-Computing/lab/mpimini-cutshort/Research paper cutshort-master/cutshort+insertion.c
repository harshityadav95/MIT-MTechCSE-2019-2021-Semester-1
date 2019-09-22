#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<limits.h>

void InsertionSort(int *,int,int);
int * cutshort(int *,int);
int bitcount(int);

int main()
{
    int num,i;
    int *arr,*res;
    scanf("%d",&num);
    clock_t start,stop;
    arr = (int *) malloc(  sizeof( int ) * num );
    for(i=0;i<num;i++)
    {
        scanf("%d",&arr[i]);
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
/*    for(i=1,max=a[0];i<n;i++)
    {
        if(max<a[i])
        {
            max=a[i];
        }
    }     */
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

    for(i=1;i<=bitmax;i++)
        bitband[i] += bitband[i-1];

   for(i=0;i<n;i++)
    {
        pos=bitcount(a[i]);
        resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = a[i];
        bitmap[pos] += 1;
    }

    printf("bit dividing is done");
 /*   stop=clock();

    printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
    printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
    printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);     */

    for(i=1;i<=bitmax;i++)
    {
        InsertionSort(resultant,bitband[i-1],bitband[i]-1);
    }

    stop=clock();

    printf("CLOCKS PER SECOND = %d\n",CLOCKS_PER_SEC);
    printf("START CLOCK = %d \nSTOP CLOCK = %d \n",start,stop);
    printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);

    // freeing the memory
    free(bitband);
    free(bitmap);
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


void InsertionSort(int * arr,int low,int high)
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

