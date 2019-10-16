#include<stdio.h>
#include<string.h>
struct Route_Request
{
    int rreq_ID;
    int reserved;
    int hop_count;
    int seq_num;
    char dest_IP[16];
    char source_IP[16];
} rreq;
struct Route_Reply
{
    int reserved;
    int hop_count;
    int seq_num;
    char dest_IP[16];
    char source_IP[16];
    int lifetime;
} rrep;
int main()
{
    rreq.rreq_ID = 3113;
    rreq.reserved = 0;
    rreq.hop_count = 3;
    rreq.seq_num = 28;
    strcpy(rreq.dest_IP,"191.168.1.2");
    strcpy(rreq.source_IP, "191.168.3.4");
    printf("Route Request packet:\n");
    printf("RREQ ID:%d\t", rreq.rreq_ID);
    printf("\n");
    printf("Reserved:%d\t", rreq.reserved);
    printf("\n");
    printf("Hop Count:%d\t", rreq.hop_count);
    printf("\n");
    printf("Destination IP Address:%s\t", rreq.dest_IP);
    printf("\n");
    printf("Source IP Address:%s\t", rreq.source_IP);
    printf("\n");
    rrep.reserved = 0;
    rrep.hop_count = 2;
    rrep.seq_num = 28;
    strcpy(rrep.dest_IP, "191.168.3.4");
    strcpy(rrep.source_IP, "191.168.1.2");
    rrep.lifetime = 30;
    printf("Route Reply packet:\n");
    printf("Reserved:%d\t", rrep.reserved);
    printf("\n");
    printf("Hop Count:%d\t", rrep.hop_count);
    printf("\n");
    printf("Destination IP Address:%s\t", rrep.dest_IP);
    printf("\n");
    printf("Source IP Address:%s\t", rrep.source_IP);
    printf("\n");
    printf("Lifetime in milliseconds:%d\t", rrep.lifetime);
    printf("\n");

    return 0;
}
