#include<stdio.h>
#include<conio.h>
#define max 10
int top=-1;
int stack[max];
void push()
{
	int n;
	printf("enter the no");
	scanf("%d",&n);
	if(top==max-1)
	{
		printf("stack is full");
	}
	else
	{
		stack[++top]=n;
	}
	
}
void pop()
{
	if(top==-1)
	{
		printf("list is empty");
	}
	else
	{
		top--;
		printf("%d element is deleted",stack[top+1]);
	}
}
void display()
{
	int i;
	if(top==-1)
	{
		printf("stack is empty");
	}
	else
	{
		for(i=top;i>=0;i--)
		{
			printf("%d",stack[i]);
		}
	}
}
void main()
{
	int choice;
	printf("1 . push\n");
	printf("2 .  pop\n");
	printf("3 . Display\n");
	printf("4 . exit\n");
	while(1)
	{
		printf("\nEnter ur choice\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				push();
				break;
			case 2:
				pop();
				break;  	
			case 3:
				display();
				break;
			case 4:
			    exit(0);
			  
			default:
			printf("Ïnvalid");		
		}
	}
}




















