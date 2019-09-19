#include<iostream>
#include<stdlib.h>
using namespace std;
int pkt1[10][10];
int pkt2[10][10];
int pktno,pktsize;
int main()
{
	 cout<<"\n W72";
	 cout<<"\nEnter the Number of pkts:";
	 cin>>pktno;
	 cout<<"\nEnter the packet size:";
	 cin>>pktsize;
	 for (int i = 0; i <pktno; ++i)
	 {
	 	for (int j = 0; j < pktsize; ++j)
	 	{
	 		cin>>pkt1[i][j];
	 	}
	 	
	 }
	 // printing the pkt recieved

	 // reconstructing the interleaving pkt
	 int del;
	 cout<<"\nEnter the pkt to be deleted:";
	 cin>>del;
	 for (int i = 0; i <pktno; ++i)
	 {
	 	for (int j = 0; j < pktsize; ++j)
	 	{
	 		if(i==del-1)
	 		{
	 			pkt1[i][j]=0;
	 		}
	 	}
	 
	 }

	 for (int i = 0; i <pktno; ++i)
	 {
	 	for (int j = 0; j < pktsize; ++j)
	 	{
	 		
	 		pkt2[i][j]=pkt1[j][i];
	 		
	 		
	 	}
	}
	 

	 	 // printing the pkt recieved
	 for (int i = 0; i <pktno; ++i)
	 {
	 	for (int j = 0; j < pktsize; ++j)
	 	{
	 		cout<<pkt2[i][j]<<" ";
	 	}
	 	cout<<"\n";
	 }


}