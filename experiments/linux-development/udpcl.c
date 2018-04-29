#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

main()
{
	char buf[65535];
	int s;
	struct sockaddr_in serv;
	socklen_t len;

	s = socket(AF_INET, SOCK_DGRAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(1243);

	len = sizeof(struct sockaddr_in);

	while (1) {
		sendto(s, buf, sizeof(buf), 0, (struct sockaddr *)&serv, len);
	}
}
