#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>

#define BUFSIZE 1500

unsigned short in_cksum(unsigned short *addr, int len);

main()
{
int res;
char sendbuf[BUFSIZE];
struct icmphdr *icmp;
int len = 56;
int sockfd;
struct sockaddr_in target;
int datalen=56;
target.sin_family = AF_INET;
inet_aton("127.0.0.1",&target.sin_addr);
icmp = (struct icmp *)sendbuf;
icmp->type = ICMP_ECHO;
icmp->un.echo.sequence = 50;
icmp->un.echo.id = 48;
icmp->checksum = in_cksum((unsigned short *)icmp, sizeof(struct icmphdr));

len = datalen;
sockfd=socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
res = sendto(sockfd, icmp, sizeof(struct icmphdr), 0, (struct sockaddr*)&target, sizeof(struct sockaddr_in));
perror("sendto");
}

unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
 *      * Our algorithm is simple, using a 32 bit accumulator (sum), we add
 *           * sequential 16 bit words to it, and at the end, fold back all the
 *                * carry bits from the top 16 bits into the lower 16 bits.
 *                     */
    while (nleft > 1)
    {
      sum += *w++;
      nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1)
    {
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);       /* add hi 16 to low 16 */
    sum += (sum >> 16);               /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}
