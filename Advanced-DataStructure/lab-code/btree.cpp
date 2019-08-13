#include<iostream>
using namespace std;
int main()
{	
	return 1;  

}
class  BTreeNode
{
	// an array for keys  
	int *keys;
	// minimum degress fron  (t-1) to (2t-1)
	int t;
	// current number of keys  
	int n;
	// Is true when node is leaf otherwise false
	bool leaf;
	// an array of child pointers of same class
	BTreeNode **c;

public:

	// constructor accepting degree t and wether leaf  or not  
	BTreeNode(int a, bool l)
	{
		t=a;
		leaf=l;

		// allocating memory for the max number of possible keys 
		keys = new int[2*t-1];
		// for 2t-1 keys 2t nodes are possible
		c=new BTreeNode *[2*t];

		//since during the time of construction the numnber of keys is zero  
		n=0;


	}
	// function to traverse all the nodes in a tree
	void traverse()
	{
		int i;
		for (i = 0; i < n; ++i)
		{
			if(leaf==false)
			{
				c[i]->traverse();
			}
			cout<<" "<<keys[i];
		}
		//[dry run needed] subtree rooted with last child
		if (leaf==false)
		{
			c[i]->traverse();
		}
	}
	// a function to search in a key in the subtre
};
// B tree 
class Btree : public BTreeNode
{
	//Pointer to root node  
	BTreeNode *root;
	// minimum degree
	int t;

	// constructor to initialise empty tree
	Btree(int a)
	{
		root=NULL;
		t=a;
	}
	void traverse()
	{
		if(root!=NULL)
		{
			root->traverse();
		}
	}

	// 



};

