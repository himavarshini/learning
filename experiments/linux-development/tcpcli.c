#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

main()
{
	char buf[65535];
	int s;
	struct sockaddr_in serv;
	socklen_t len;
	int ret;
	struct sockaddr_in client;

	s = socket(AF_INET, SOCK_STREAM, 0);

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = INADDR_ANY;
	serv.sin_port = htons(1242);

	connect(s, (struct sockaddr *)&serv, sizeof(serv));

	while (1) {
		write(s, buf, sizeof(buf));
		read(s, buf, sizeof(buf));
	}
}

