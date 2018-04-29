#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
main()
{
	int s;
	int opt = 1;
	struct sockaddr_in serv;
	char *ip = "192.168.20.166";
	struct sockaddr_in m;

	s = socket(AF_INET, SOCK_DGRAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = inet_addr("224.0.0.1");
	serv.sin_port = htons(1111);

	memset(&m, 0, sizeof(m));
	m.sin_addr.s_addr = inet_addr(ip);
	setsockopt(s, IPPROTO_IP, IP_MULTICAST_IF, &m, sizeof(m));

	while (1) {
		sendto(s, ip, strlen(ip), 0, (struct sockaddr *)&serv, sizeof(serv));
		sleep(1);
	}
}
