// Cutshort algo using MPI  
//Using MergeSort
#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include<time.h>
#include<limits.h>
int bitcount(int num);
void merge_sort(int *,int ,int );
void merge(int *,int,int,int);
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
        	//quicksort(resultant,bitband[i-1],bitband[i]-1);
             merge_sort(resultant,bitband[i-1],bitband[i]-1);
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
