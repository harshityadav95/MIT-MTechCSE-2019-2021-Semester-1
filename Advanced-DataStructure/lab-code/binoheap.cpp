#include<iostream>
#include<stdio.h>
using namespace std;
// week 6 insertion in a binomial heap 
struct node
{
	int n;
	int degree;
	node* child;
	node* sibling
	node* parent;
}
class BinomialHeap
{
	private:
		node* H;
		node* Hr;
		int count;
	public:
		node* Initializeheap()
		{
			node *np;
			np=NULL;
			return np;
		}
		node* CreateNode(int value)
		{
			node *p=new node;
			p->n=value;
			return p;
		}
		node* InsertNode(node* H, node* p)
		{
			node* H1=Initializeheap();
			p->parent=NULL;
			p>child=NULL;
			p->sibling=NULL;
			p->degree=0;
			H1=Union(H,H1);
			return H;
		}
		node* Union(node* H1,node* H2)
		{
			node *H=Initializeheap();
			H=Merge(H1,H2);

		}
		node* Merge(node* H1,node *H2)
		{
			node* H=Initializeheap();
			node *y,*z,*a,*b;
			y=H1;
			z=H2;
			if(y!=NULL)
			{
				if(z!=NULL)
				{
					if (y->degree<=z->degree)
					{
						H=y;
					}
					else if(y->degree>z->degree)
					{
						H=z;
					}
				}
				H=y;
			}
			else
				H=z;

			while(y!=NULL && z!=NULL)
			{
				if
			}
		}

}
class 
int main()
{
	BinomialHeap bh;
	node *p;
	node *H;
	H=bh.Initializeheap();

	cout<<"checking thee library";
	while(1)
	{
		cout<<"\n-- Binomial Heap Operations--";
		int ch;
		cout<<"\n1. Enter the Element ";
		cout<<"\n2. Display heap";
		cout<<"\n3.Exit";
		switch(ch)
		{
			case 1:
			{
				cout<<"\n Enter the Value of the Element :";
				int value;
				cin>>value;
				p=bh.CreateNode(value);
				H=bh.InsertNode(H,p);

				break;
			}
		}
	}
	return 1;
}


//https://www.sanfoundry.com/cpp-program-implement-binomial-heap/

