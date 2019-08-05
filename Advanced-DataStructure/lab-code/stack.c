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
void push(int data)
{
	struct node *temp;
	temp=new node();
	if (!temp)
	{
		cout<<"\n Heap Overflow";
		exit(1);
	}
	temp->data=data;
	temp->next=head;
	head=temp;
	

}
void display()
{
	struct node	*temp
	if(top==NULL)
	{
		cout<<"\nStack Undeflow";
	}
	else
	{
		temp=top;
		while (temp!=NULL)
		{
			cout<<" "<<temp->data;
			temp=temp->next;
		}
		
	}
	
}
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
				cout<<"\n Enter the Number you want to Enter : ";
				int a ;
				cin>>a;
				push(a);
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
