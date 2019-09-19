#include<iostream>
#include<stdlib.h>
using namespace std;
int pkt[10][10];
int pktsize,pktno;
int main()
{
	cout<<"test";
	cout<<"\nEnter the bit size of pkt :";
	cin>>pktsize;
	cout<<"Enter the no.pf pkts";
	cin>>pktno;
	//reading the user values
	for (int i = 0; i < pktno; ++i)
	{
		for (int j = 0; j < pktsize; ++j)
			{
				cin>>pkt[i][j];
			}	
	}
	// creating the redundant pkt
	for(int i=0;i<pktsize;i++)
	{
		int count=0;
		int val;
		for(int j=0;j<pktno;j++)
		{

				if(pkt[j][i]==1)
					count++;


		}
		if (count%2!=0)
		{
			val=1;
		}
		else
			val=0;
		pkt[pktno][i]=val;

	}
	cout<<"\n";
	//printing the bits along with the redundant ones
	for (int i = 0; i <=pktno; ++i)
	{
		for (int j = 0; j<pktsize; ++j)
		{
			cout<<pkt[i][j]<<" ";

		}
		cout<<"\n";
	}
	int del;
	cout<<"\nEnter the pkt to be lost :";
	cin>>del;
	for(int i=0;i<pktsize;i++)
	{
		pkt[del-1][i]=999;
	}
	//displaying the pkt after deleting
	for (int i = 0; i <=pktno; ++i)
	{
		for (int j = 0; j<pktsize; ++j)
		{
			cout<<pkt[i][j]<<" ";

		}
		cout<<"\n";
	}
	//Reconstructing the lost packet
	for (int i = 0; i <pktsize; ++i)
	{
		int count=0;
		int val,crc;
		for (int j = 0; j<pktno; ++j)
		{
			if(j!=del-1)
			{
				if(pkt[j][i]==1)
					count++;
			}
			crc=pkt[pktno][i];
			


		}

		if (count%2==0)
		{
			if(crc==1)
			{
				val=1;
			}
			else
				val=0;


		}
		else
		{
			if(crc==0)
			{
				val=1;
			}
			else
				val=0;

		}
			pkt[del-1][i]=val;
	}
			


		cout<<"\n";
	


	//displaying the pkt after reconstru
	for (int i = 0; i <=pktno; ++i)
	{
		for (int j = 0; j<pktsize; ++j)
		{
			cout<<pkt[i][j]<<" ";

		}
		cout<<"\n";
	}
		
	return 1; 

}