#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int key;
	int degree;
	struct node *p,*c,*s;
}NODE;
NODE* makeBinomialHeap()
{
	NODE* n;
	n=((NODE*)malloc(sizeof(NODE)));
	return n;
}
NODE* binomialHeapMinimum(NODE *h)
{
	NODE *x=h;
	NODE *y;
	int min=10000;
	while(x!=NULL)
	{
		if(x->key<=min)
		{
			min=x->key;
			y=x;
		}
		x=x->s;
	}
	return y;
}

void binomialHeapLink(NODE* y,NODE* z)
{
	y->p=z;
	y->s=z->c;
	z->c=y;
	z->degree++;
}

NODE* binomialHeapMerge(NODE* h1,NODE* h2) 
{
    NODE* h=makeBinomialHeap();
	NODE *y,*z,*a,*b;
    y=h1;
    z=h2;
    if (y!=NULL)
    {
        if(z!=NULL && y->degree<=z->degree)
            h=y;
        else if(z!=NULL && y->degree>z->degree)
           h=z;
        else
            h=y;
    } 
    else
        h=z;
    while(y!=NULL && z!=NULL)
    {
        if(y->degree<z->degree)
        {
            y=y->s;
        }
        else if(y->degree==z->degree)
        {
            a=y->s;
            y->s=z;
            y=a;
        } 
        else
        {
            b=z->s;
            z->s=y;
            z=b;
        }
    }
    return h;
}


NODE* binomialHeapUnion(NODE *h1,NODE *h2)
{
	NODE *prev,*next,*x;
	NODE *h=makeBinomialHeap();
	h=binomialHeapMerge(h1,h2);
	if(h==NULL)
		return h;
	prev=NULL;
	x=h;
	next=x->s;
	while(next!=NULL)
	{
		if((x->degree!=next->degree)||(next->s!=NULL && x->degree==(next->s)->degree))
		{
			prev=x;
			x=next;
		}
		else 
		{
			if(x->key<=next->key)
			{
				x->s=next->s;
				binomialHeapLink(next,x);
			}
			else
			{
				if(prev==NULL)
					h=next;
				else
					prev->s=next;
				binomialHeapLink(x,next);
				x=next;
			} 
		}
		next=x->s;
	}
	return h;
}

NODE* binomialHeapInsert(NODE *h,int k)
{
	NODE *x=makeBinomialHeap();
	x->p=NULL;
	x->s=NULL;
	x->degree=0;
	x->key=k;
	x->c=NULL;
	h=binomialHeapUnion(h,x);
	return h;
}

void display(NODE *h)
{
	NODE *x=h;
	if(x==NULL){
		return;
	}
	printf("%d\t",x->key);
	printf("\n");
	display(x->s);
	printf("\n");
	display(x->c);
	printf("--");
}

int main()
{
	NODE *head=makeBinomialHeap();
	head=NULL;
	NODE *m;
	int n,val,ch;
	int ele;
	printf("\nNo.of elements :");
	scanf("%d",&ele);
	for(int i=0;i<ele;i++)
	{	printf("\nInput :");
		scanf("%d",&val);
		head=binomialHeapInsert(head,val);
		display(head);
		
	}
	m=binomialHeapMinimum(head);
	printf("\nMin:%d",m->key);
	return 0;
}
