#include<stdio.h>

void main()
{
  int seq, src, dest, ttl; 
  int n, a[10];
  int node;

  //Route Request Packet
  printf("Enter the sequence no., source addr, destination addr &  Ttl:\n");
  scanf("%d %d %d %d", &seq, &src, &dest, &ttl);

  printf("\nRoute request packet :\n");
  printf("Source\tDestination\tSeqNo.\tTTL\n");
  printf("%d\t%d\t\t%d\t%d", src, dest, seq, ttl);
  printf("\n");

  //Route Reply Packet
  printf("\nEnter the number of nodes to reach the destination:");
  scanf("%d", &n);

  printf("\nEnter the address of %d hops:\n",n);
  for(int i = 0; i < n; i++)
  	scanf("%d", &a[i]);

  printf("\nRoute Reply packet\n"); 
  printf("\nSourceaddr:\t%d\n", src);
  for(int i = 0; i < n; i++)
  	printf("%d hop:\t\t%d\n",i, a[i]);
  printf("Destaddr:\t%d\n", dest);


  //Check whether receiving node should forward or reply
  printf("\nEnter the address of a receiving node:\n");
  scanf("%d", &node);
  
  if(node == dest)
  	printf("\nReply with Route Reply packet\n");
  else
  	printf("\nForward the Route Request packet\n");

}