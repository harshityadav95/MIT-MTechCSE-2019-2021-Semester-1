x`  #include<stdio.h>
#include<stdlib.h>
#define MAX 100



int S[100];

int top=-1;

int count = 0;


//Pushing the elements

void Push(int S[],int x)

{

    if(top == MAX - 1)

    {

        printf("Stack Overflow\n");

    }

    else

    {
        count++;

        S[++top] = x;

    }

}



//Popping the elements

void Pop(int S[])

{

    if(top == -1)

    {

        printf("Stack underflow\n");

    }

    else

    {
        count++;

        printf("Element that is popped = %d\n",S[top]);

        top--;

    }

}



//Display the contents

void Display()

{

    int i;

    if(top >= 0)

    {

        printf("Stack elements are\n");

        for(i = top;i >= 0;i --)

        {

            printf("%d ",S[i]);

        }

    }

    else

    {

        printf("Stack is empty\n");

    }

}



void Stackempty(int S[])

{

    if(top <= -1)

    {

        printf("Stack is empty\n");

    }

    else

    {

        printf("Stack is not empty\n");

    }

}


void Multipop(int S[],int k)
{
    while(top != -1 && (k-1) > -1)
    {
        Pop(S);
        k = k - 1;
    }
}

//Main Program

int main()

{

    int choice,data,k;

    

    printf("1:Push 2:Pop 3:Display 4:Stack-empty 5:Multipop 6:Cost 7:Exit\n");

    

    while(1)

    {

        printf("\nEnter the choice\n");

        scanf("%d",&choice);

        switch(choice)

        {

            case 1:

                printf("Enter the element to be pushed\n");

                scanf("%d",&data);

                Push(S,data);

                break;

                

            case 2:

                Pop(S);

                break;

                

            case 3:

                Display();

                break;

                

            case 4:

                Stackempty(S);

                break;

            case 5:
                if(top == -1)
                {
                    printf("Stack is empty\n");
                }
                else
                {

                    printf("Enter the elements to be popped\n");
                    scanf("%d",&k);
                    Multipop(S,k);
                }
                break;

            case 6:
                printf("Cost = %d",count);
                break;

		case 7:exit(0);



            default:

                printf("Invalid choice\n");

        }

    }

    //printf("Cost = %d",count);

    return 0;

}

    

