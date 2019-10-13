// Cutshort algo using MPI  

#include<stdlib.h>
#include<stdio.h>
#include<mpi.h>
#include<time.h>
#define arm 32
int bitcount(int num);


int main(int argc,char* argv[])
{
	int size,rank;
	printf("\n Hello world");
	//int a[60001];
	//int a[20]={15,10,19,49,13,2,7,4,1,3,10,20,17,15,46,16,53,0,5,9};
	int a2[60001]={0},pos,num;
	int a[20];    
    int a3[60001];
    int a5[60001]={0};
    int a6[60001]={0};
    //int a4[arm]={0};
	int bitmap[32]={0};
	int bitband[32]={0};
	int b2[32]={0};
	int resultant[60001]={0};
	int number_of_elements=20;
	
	MPI_Status status;
	MPI_Init(&argc,&argv);
    int count;
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank == 0)
    {
    	
    	count=20;
       ///a[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        for (int i = 0; i < count; ++i)
        {
            a[i]=i+1;
        }
    	/*FILE *fptr;
    	fptr = fopen("integers", "r");
		printf("\nReading the File:\n");
		while ( (num = getw(fptr)) != EOF ) 
		{
    		a[count]=num;
    		count++;

  		}
  		fclose(fptr);*/
  		//number_of_elements=count;
        //number_of_elements=20;

        
    }
	//
        
    //MPI_Send(&number_of_elements,1,MPI_INT,1,0,MPI_COMM_WORLD);
    MPI_Bcast(&count,1,MPI_INT,0,MPI_COMM_WORLD);    
    //MPI_Send(&a[number_of_elements/2],number_of_elements/2,MPI_INT,1,1,MPI_COMM_WORLD);
    MPI_Scatter(&a[0],count/size,MPI_INT,&a2,count/size,MPI_INT,0,MPI_COMM_WORLD);

    printf("\nElements Recieved :");
    for(int i=0;i<number_of_elements/size;i++)
    {
        //printf("[ %d--%d--%d ]",number_of_elements/size,rank,a2[i]) ;
    }
     int a4[arm]={0};
    for(int i=0;i<count/size;i++)
    {
        a4[ bitcount(a2[i]) ] += 1 ;
    	//a4[i]=a2[i];
        printf("[ %d-%d-%d ]",i,a2[i],bitcount(a2[i]));
    }
    printf("\n");
    printf("\nIndividual Bitband:");
    for(int i=0;i<arm;i++)
    {
       	//a4[ bitcount(a2[i]) ] += 1  ;
       	printf(" [%d] ",a4[i]);
    }
    
        
    //for(int i=0;i<number_of_elements/size;i++)
    {
     //   printf("[ # %d--%d--%d ]",number_of_elements/size,rank,a2[i]) ;
    }
     //MPI_Barrier(MPI_COMM_WORLD);
      //MPI_Alltoall(&a4[0],number_of_elements/size,MPI_INT,&a6[0],number_of_elements/size,MPI_INT,MPI_COMM_WORLD);
         for (int i = 0; i < number_of_elements/size; ++i)
        {
            
            //printf("%d--",a4[i]);

        }
     MPI_Barrier(MPI_COMM_WORLD);
     MPI_Gather(&a4[0],arm,MPI_INT,&a3[0],arm*size,MPI_INT,0,MPI_COMM_WORLD);
        //MPI_Recv(&b2,32,MPI_INT,1,2,MPI_COMM_WORLD,&status);
/*int MPI_Alltoall(void *sendbuf,int sendcount,MPI_Datatype sendtype,void *recvbuf,int recvcount,MPI_Datatype recvtype,MPI_Comm comm
);*/
    // MPI_Alltoall(&a4[0],number_of_elements/size,MPI_INT,&a4[0],number_of_elements/size,MPI_INT,0,MPI_COMM_WORLD);


     if (rank==0)
     {
        clock_t start,stop;
        start=clock();
        /*printf("\n"); 
            for (int i = 0; i < number_of_elements*size; ++i)
        {
            
            printf(" %d--%d ",i,a3[i]);

        }*/
        for (int i = 0; i<number_of_elements/size; ++i)
        {
        	//printf("%d--",a3[i]);
        	/*for (int j = 0;j<size;j++)
        	{
        		int temp=i+((number_of_elements/size)*j);
        		printf("[ %d=%d+%d ]",i,temp,a3[temp]);
        		a5[i]+=a3[temp];
        	}
            //printf("%d--",a5[i]);
        	printf("\n");
            //bitband[a3[i]]++;
            //*/

        }
        //printf("\nThe valus is  : %d",(number_of_elements/size)*size);
        printf("\n");
        printf("\n Collected :%d",arm*size);
        for (int i = 0; i < arm*size*size; ++i)
        {
        	
            printf("\n%d--%d",i,a3[i]);

        }
        for (int i = 0; i < 32; ++i)
        {
            //bitband[i]=bitband[i]+b2[i];
           // printf("\n %d ",bitband[i]);
        }
        /*for(int i=1;i<=32;i++)
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
        for(int i=0;i<number_of_elements;i++)
        {
          //printf("%d  ",resultant[i]);
        }
        printf("CLOCKS PER SECOND = %ld\n",CLOCKS_PER_SEC);
        printf("START CLOCK = %ld \nSTOP CLOCK = %ld \n",start,stop);
        printf("TIME TAKEN = %f\n",(float)(stop-start)/CLOCKS_PER_SEC);*/
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
