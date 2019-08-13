#include <stdio.h>
#include <string.h>

void main()
{
	char str[100];
	int length,i,j,n,k;
	int count,count1;
	//int cost = 0;
	printf("Enter the value of k for k-bit counter\n");
	scanf("%d",&k);

	for(i=0;i<k;i++)
	{
		str[i] = '0';
	}

	printf("%s",str);

	printf("\nEnter the number of increments\n");
	scanf("%d",&n);

	length = strlen(str);

	i = length - 1;

	count=0;
	
	for(j=0;j<n;j++)
	{
		while(str[i] == '1')
		{
			count++;
			str[i] = '0';
			i--;
		}
		
		if(i >= 0)
		{	
			count++;
			str[i] = '1';
			printf("%s\n",str);
			i = length - 1;
		}

	}

	printf("Total cost = %d",count);
}