#include<stdio.h>

void main()
{
	int i, n, j ;


    n = 1;
	for(i = 0; i < 2; i++)
	{  n = n * 2;
		for(j = 0; j <= n; j++)
			{
		        printf("\nwait for %d time units", j);		
			}
			printf("\nSend the packet");
	}

	printf("\nStop sending\n");
}
