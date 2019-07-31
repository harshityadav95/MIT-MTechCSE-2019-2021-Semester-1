#include<stdio.h>
#include<stdlib.h>
void push();
void pop();
void display();
struct node
{
	int data;
	struct node *next;
}*head;
int main()
{
	int choice=0;	
	printf("\nStack Operations Using Linked List ");
	while(choice!=4)
	{
		printf("\n1. PUSH");
		printf("\n2. POP");
		printf("\n3. Display")
		printf("\n4. Exit");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				push();
				break;

			}
			case 2:
			{
				pop();
				break();
				
			}
			case 3:
			{
				display();
				break();
	
			
			}
			case 4:
			{
				printf("Exiting");
				break;
			}
			default:
			{
				printf("\n please Enter a valid Choice");
			}
			
		}		

	}
}
