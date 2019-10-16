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
int i;
char RT[11][20];
char check_addr[16];
int status;
int main()
{
    rreq.rreq_ID = 3024;
    rreq.reserved = 0;
    rreq.hop_count = 3;
    rreq.seq_num = 23;
    strcpy(rreq.dest_IP,"192.168.5.6");
    strcpy(rreq.source_IP, "191.168.3.4");
    strcpy(check_addr, rreq.dest_IP);
    strcpy(RT[1], "192.168.2.3");
    strcpy(RT[2], "192.168.3.4");
    strcpy(RT[3], "192.168.4.5");
    strcpy(RT[4], "192.168.5.6");
    strcpy(RT[5], "192.168.6.7");
    strcpy(RT[6], "192.168.7.8");
    strcpy(RT[7], "192.168.8.9");
    strcpy(RT[8], "192.168.9.10");
    strcpy(RT[9], "192.168.10.11");
    strcpy(RT[10], "192.168.11.12");
    printf("Routing Table for intermediate node:");
    for(i=0; i<=10; i++)
    {
        printf("%s\n", RT[i]);
    }
    for(i=0; i<=10; i++)
    {
        status = strcmp(check_addr, RT[i]);
        if(status == 0)
        {
            printf("The destination IP is present, packet will be forwarded!\n");
        }
    }
    return 0;
}