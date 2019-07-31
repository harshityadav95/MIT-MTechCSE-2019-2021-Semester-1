#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int selectionsort(int *arr,int size)
{
    int min=INT_MAX;
    for (int i = 0; i < size-1; i++)
    {
        
            min=*(arr+i);
            for (int j = i+1; j < size; j++)
            {
                if (*(arr+j)<min)
                {
                   min=*(arr+j);
                    int temp=*(arr+j);
                    *(arr+j)=*(arr+i);
                    *(arr+i)=temp;
                    
                }
                
            }
         
    }
    return 1;

}
int main()
{
    int size,*array,swap;
    printf("\nEnter the Size of the array :");
    scanf("%d",&size);
    array=(int*)malloc(size*sizeof(int));
    for (int i = 0; i < size; i++)
    {
        scanf("%d",(array+i));
    }
    swap=selectionsort(array,size);
    for (int i = 0; i < size; i++)
    {
        printf("\n%d",*(array+i));
    }
    


    

}