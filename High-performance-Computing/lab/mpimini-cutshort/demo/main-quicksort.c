// Cutshort algo using MPI  
//Using Quick Sort
#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include<time.h>
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
	printf("\n Hello world");
	int a[60001];
	//int a[20]={15,10,19,49,13,2,7,4,1,3,10,20,17,15,46,16,53,0,5,9};
	int a2[60001],pos,num;
	int bitmap[32]={0};
	int bitband[32]={0};
	int b2[32]={0};
	int resultant[60001]={0};
	int number_of_elements;
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0)
    {
    	
    	int count=0;
    	FILE *fptr;
    	fptr = fopen("integers", "r");
		printf("\nReading the File:\n");
		while ( (num = getw(fptr)) != EOF ) 
		{
    		a[count]=num;
    		count++;

  		}
  		fclose(fptr);
  		number_of_elements=count;
	    clock_t start,stop;
    	start=clock();
    	MPI_Send(&number_of_elements,1,MPI_INT,1,0,MPI_COMM_WORLD);
    	MPI_Send(&a[number_of_elements/2],number_of_elements/2,MPI_INT,1,1,MPI_COMM_WORLD);
    	for(int i=0;i<number_of_elements/2;i++)
        {
        	bitband[ bitcount(a[i]) ] += 1 ;
        }
        MPI_Recv(&b2,32,MPI_INT,1,2,MPI_COMM_WORLD,&status);
        for (int i = 0; i < 32; ++i)
        {
        	bitband[i]=bitband[i]+b2[i];
        	printf("\n %d ",bitband[i]);
        }
        for(int i=1;i<=32;i++)
        {
        	bitband[i] += bitband[i-1];
        }
    
         for(int i=0;i<number_of_elements;i++)
    	{
        	pos=bitcount(a[i]);
        	resultant[ ((pos==0)?0:bitband[pos-1]) + bitmap[pos] ] = a[i];
        	bitmap[pos] += 1;
    	}
    	
    	for(int i=1;i<=32;i++)
    	{
        	quicksort(resultant,bitband[i-1],bitband[i]-1);
    	}
    	
    	stop=clock();

    	printf("CLOCKS PER SECOND = %ld\n",CLOCKS_PER_SEC);
    	printf("START CLOCK = %ld \nSTOP CLOCK = %ld \n",start,stop);
    	printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);
        for(int i=0;i<number_of_elements;i++)
        {
          //printf("%d  ",resultant[i]);
        }

        
    }
    if(rank==1)
    {
    	MPI_Recv(&number_of_elements,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
    	MPI_Recv(&a2[0],number_of_elements/2,MPI_INT,0,1,MPI_COMM_WORLD,&status);
    	for(int i=0;i<number_of_elements/2;i++)
        {
        	b2[ bitcount(a2[i]) ] += 1 ;
        }
       	MPI_Send(&b2,32,MPI_INT,0,2,MPI_COMM_WORLD);


    }


    	
     

	

MPI_Finalize();


	
	return 1;
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
