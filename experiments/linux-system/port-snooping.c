#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>

main(int argc, char **argv)
{
	int max = 3000;
	int s;
	int ret;
	int i;
	struct sockaddr_in serv;

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("sock fail\n");
		return -1;
	}

	serv.sin_addr.s_addr = inet_addr(argv[1]);
	serv.sin_family = AF_INET;

	for (i = 1; i < max; i++) {
		serv.sin_port = htons(i);
		ret = connect(s, (struct sockaddr *)&serv, sizeof(serv));
		if (ret == 0) {
			printf("service on %d\n", i);
		}
	}

	close(s);
}
