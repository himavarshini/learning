#include <stdio.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

main()
{
	int fd;
	int size = 0;
	char buff[1024];
	struct timeval tv, i;
	uint64_t timed;

	fd = creat("test", 0666);
	if (fd < 0) {
		return -1;
	}

	memset(buff, 1, 1024);
	gettimeofday(&tv, 0);
	while (1) {
		if (write(fd, buff, sizeof(buff)) < 0) {
			break;
		}
		size += sizeof(buff);
		if (size >= 1024 * 1024 * 24) {
			break;
		}
	}
	gettimeofday(&i, 0);

	timed = ((uint64_t)i.tv_sec * 1000 + i.tv_usec / 1000) - ((uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000);
	unlink("test");
	printf("%ju\n", timed);
}
