#include<stdio.h>
#include<stdlib.h>
int sort(int *arr,int size)
{
    int swapped,i,j;
    for (int i = 0; i < size; i++)
    {
        
        for (int j = 0; j < size-i-1; j++)
        {
            swapped++;
            if(*(arr+j)>*(arr+j+1))
            {
                int c=*(arr+j+1);
                *(arr+j+1)=*(arr+j);
                *(arr+j)=c;
                
            }
        }
        
    }
    return swapped;
    

}
int main()
{
    int size,*array,swap;
    printf("\n Enter the Size of the Array :");
    scanf("%d",&size);
    array=(int*)malloc(size*sizeof(int));
    for(int i=0;i<size;i++)
    {
        scanf("%d",(array+i));
    }
    swap=sort(array,size);
    printf("\n Now Displaying the Array you Entered ");
    for (int i = 0; i < size; i++)
    {
        printf("%d \n",*(array+i));
    }
    printf("\nThe Theoretical notation: %d",size*size);
    printf("\nThe Practical notation: %d",swap);
    return 1;

}

// Also look into optimised case for bubble sort algorithm