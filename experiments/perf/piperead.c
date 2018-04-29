#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

main()
{
	char *path = "/home/dev/dev.sock";

	int fp;

	fp = open(path, O_RDWR);
	if (fp < 0) {
		printf("failed to open %s\n", path);
		return 0;
	}

	int flags;

	flags = fcntl(fp, F_GETFL, 0);
	fcntl(fp, F_SETFL, flags | O_NONBLOCK);
	perror("fcntl");
	char buff[65535];

	struct timeval t, t1;

	while (1) {
		gettimeofday(&t, 0);
		memset(buff, 1, 65535);
		write(fp, buff, 65535);
		read(fp, buff, 65535);
		gettimeofday(&t1, 0);
		printf("%d\n", t1.tv_usec - t.tv_usec);
	}
}
