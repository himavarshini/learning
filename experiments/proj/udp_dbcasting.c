#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

#define MAX_BUF 1024

int done;
void signal_handler(int a)
{
	done = 1;
}

void usage()
{
	printf("./a.out port broadcast_ipv4_addr\n");
}

int main(int argc, char **argv)
{
	int sd;
	int ret = -1;
	struct sockaddr_in serv;
	int i = 0;
	int opt = 1;
	uint8_t *tx_buf;

	if (argc != 3) {
		usage();
		return 1;
	}
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		return -1;
	}

	ret = setsockopt(sd,
		   SOL_SOCKET,
		   SO_BROADCAST,
		   &opt,
		   sizeof(opt));
	if (ret < 0) {
		return -1;
	}
	serv.sin_family = AF_INET;
	serv.sin_port = htons(atoi(argv[1]));
	serv.sin_addr.s_addr = inet_addr(argv[2]);
	signal(SIGINT, signal_handler);
	while (done == 0) {
		if (i == 64) i = 0;
		tx_buf = calloc(i, MAX_BUF);
		memset(tx_buf, 1, i * MAX_BUF);
		usleep(1);
		sendto(sd,
		       tx_buf,
		       i * MAX_BUF,
		       0,
		       (const struct sockaddr *)&serv,
		       sizeof(struct sockaddr_in));
		free(tx_buf);
		i++;
	}
	close(sd);
	return 0;
}
