#include<iostream>
#include<stdlib.h>
using namespace std;
int chunk[11];
int main()
{
	cout<<"\n w73";
	cout<<"Enter the 8 bit hamming code:";
	for (int i = 0; i < 11; ++i)
	{
		if(i==3||i==7||i==9||i==10)
			chunk[i]=9;
		else
			cin>>chunk[i];

	}
	// now printing the array  
	for (int i = 0; i < 11; ++i)
	{
		cout<<chunk[i]<<" ";
	}
	return 1;
}