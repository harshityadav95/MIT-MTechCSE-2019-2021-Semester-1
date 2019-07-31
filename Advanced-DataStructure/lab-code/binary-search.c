#include<stdio.h>
#include<stdlib.h>
int binary(int *arr, int size,int element)
{
	int first,last,mid,flag=0;
	first=0;
	last=size-1;
	mid=(first+last)/2;
	while(first<=last)
	{
		if(*(arr+mid)<element)
		{
			first=mid+1;
			
		}
		else if(*(arr+mid)==element)
		{
			flag=1;
			break;
		}
		else if(*(arr+mid)>element)
		{
			last=mid-1;
		}
		mid=(first+last)/2;
	}	
	return flag;
}
int main()
{
	int size,*array,element,result;
	printf("\nEnter the Size of the Array :");
	scanf("%d",&size);
	printf("\n Now enter the elements in Ascending Order");
	array=(int*)malloc(size*sizeof(int));
	for(int i=0;i<size;i++)
	{
		scanf("%d",(array+i));
	}
	printf("\nEnter the Element you want Search :");
	scanf("%d",&element);
	result=binary(array,size,element);
	if(result==0)
	{
		printf("\n Element Not Found");
	}
	else
	{
		printf("\n Element  found");
	}	

	return 1;	
	
}
