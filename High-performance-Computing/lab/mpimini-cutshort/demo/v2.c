// Cutshort algo using MPI  

#include<stdlib.h>
#include<stdio.h>
#include<malloc.h>
#include<mpi.h>
#include<time.h>
#define arm 32
int bitcount(int num);
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
void quicksort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quicksort(arr, low, pi - 1); 
        quicksort(arr, pi + 1, high); 
    } 
} 

int main(int argc,char* argv[])
{
	int size,rank;
	//printf("\n Hello world");
	//int a[60001];
	//int a[20]={15,10,19,49,13,2,7,4,1,3,10,20,17,15,46,16,53,0,5,9};
	int arr2[50000]={0};
    int arr[50000]={0};
    int resultant[50000]={0};
    int pos;
	int a[20];    
    int bitband[arm]={0};
    //int a4[arm]={0};
	int bitmap[arm]={0};
	//int bitband[32]={0};
	int b2[32]={0};
	//int resultant[60001]={0};
   int count=0,index=0;

	
	MPI_Status status;
	MPI_Init(&argc,&argv);
    //int count;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0)
    {
    	
    	//count=20;
      
        int num;
       ///a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        /*for ( i = 0; i < count; ++i)
        {
            a[i]=i+1;
        }*/
    	FILE *fptr;
    	fptr = fopen("integers", "r");
		printf("\ncounting the File:\n");
		while ( (num = getw(fptr)) != EOF ) 
		{
    		arr[count]=num;
    		count++;

  		}
  		fclose(fptr);
        //count=20;
        //arr = (unsigned long *) malloc(  sizeof( unsigned long ) * count );
        //resultant = (unsigned long *) malloc(  sizeof( unsigned long ) * count );
        //num=0;
        //FILE *fptr;
        /*fptr = fopen("integers", "r");
        printf("\nREading the File:\n");
        while ( (num = getw(fptr)) != EOF ) 
        {
            arr[index]=num;
            index++;

        }
        fclose(fptr);
        for (unsigned long i = 0; i < count; ++i)
        {
            arr[i]=i+1;
        }*/
        /*printf("\nValues genertated :");
        for (int i = 0; i < count; ++i)
        {
            printf("%d--",arr[i]);
        }*/


        
    }

    MPI_Bcast(&count,1,MPI_INT,0,MPI_COMM_WORLD);    

    MPI_Scatter(&arr[0],count/size,MPI_INT,&arr2,count/size,MPI_INT,0,MPI_COMM_WORLD);

    printf("\nElements Recieved :");

    int a4[arm]={0};
    for(int i=0;i<count/size;i++)
    {
        a4[ bitcount(arr2[i]) ] += 1 ;
    	//a4[i]=a2[i];
        //printf("[ %d-%d-%d ]",i,arr2[i],bitcount(arr2[i]));
    }
    printf("\n");
    printf("\nIndividual Bitband:");
    /*for(int i=0;i<arm;i++)
    {
       	//a4[ bitcount(a2[i]) ] += 1  ;
       	printf(" [%d] ",a4[i]);
    }*/


     MPI_Barrier(MPI_COMM_WORLD);

     MPI_Reduce(&a4[0],&bitband[0],arm,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

     if (rank==0)
     {
        clock_t start,stop;
        start=clock();
        printf("\n");
        //printf("\n Collected :%d",arm*size);
        for (int i = 0; i < arm; ++i)
        {
        	
            printf("\n%d",bitband[i]);

        }
        for(int i=1;i<=arm;i++)
        {
            bitband[i] += bitband[i-1];
        }
         for(int i=0;i<count;i++)
        {
            pos=bitcount(arr[i]);
            resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = arr[i];
            bitmap[pos] += 1;
        }
        
        for(int i=1;i<=32;i++)
        {
            quicksort(resultant,bitband[i-1],bitband[i]-1);
        }
        stop=clock();
        for(int i=0;i<count;i++)
        {
          printf("%d  ",resultant[i]);
        }
        printf("CLOCKS PER SECOND = %ld\n",CLOCKS_PER_SEC);
        printf("START CLOCK = %ld \nSTOP CLOCK = %ld \n",start,stop);
        printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);
     }
        
    	
        
    	
    	
    	

        
    


    	
     

	

MPI_Finalize();


	
	return 1;
}
int bitcount(int num)
{
    int count1=0,count2=0, tmp,value=4278190080U,result;
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
    return ((int)result);
}
