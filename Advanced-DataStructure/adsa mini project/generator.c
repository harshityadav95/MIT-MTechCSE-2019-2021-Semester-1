#include<stdlib.h>
#include<stdio.h>
// code to write the digits to a file  
void writedigits(int n,int lower,int upper)
{
	// creating a FILE variable
  	FILE *fptr;
  	 // open the file in write mode
  	fptr = fopen("integers", "w");
  	if (fptr != NULL)
  	{
  		printf("File created successfully!\n");
  	}
  	else
  	{
  	    printf("Failed to create the file.\n");
  	}
  	for (int i = 0; i < n; ++i)
  	{
  		int num=(rand()%(upper-lower+1))+lower;
  		printf("%d ",num );
  		putw(num, fptr);

  	}
  	// close connection
  	fclose(fptr);

}
int main()
{
	int num;
	FILE *fptr;
	printf("\nStarting the Number Genertaror .....");
	int n,lower,upper;
	printf("\nEnter the the number of Digits :");
	scanf("%d",&n);
	printf("Enter the lower Range of Digits :");
	scanf("%d",&lower);
	printf("Enter the Upper Range of Digits");
	scanf("%d",&upper);
	writedigits(n,lower,upper);
	fptr = fopen("integers", "r");
	printf("\nReading the File:\n");
	while ( (num = getw(fptr)) != EOF ) 
	{
    	printf("%d\n", num);
  	}

  // close connection
  	fclose(fptr);






	return	1;

}