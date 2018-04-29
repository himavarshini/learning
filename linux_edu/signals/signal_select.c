#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>

void signal_hdl(int sig)
{
	printf("Signalled\n");
}

int main(void)
{
	int ret;
	fd_set rdfd;
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));

#ifdef SIGNAL_HDL
	sa.sa_handler = signal_hdl;

	ret = sigaction(SIGINT, &sa, 0);
	if (ret) {
		printf("failed to install a signal handler\n");
		return -1;
	}
#endif

	while (1) {
		FD_ZERO(&rdfd);
		FD_SET(0, &rdfd);
#ifdef SLEEP_IN_SELECT
		struct timeval tv = {
			.tv_sec = 1,
			.tv_usec = 0
		};
		printf("sleeping for %ld:%ld\n", tv.tv_sec, tv.tv_usec);
		ret = select(1, &rdfd, NULL, NULL, &tv);
#else
		ret = select(1, &rdfd, NULL, NULL, NULL);
#endif
		if (ret > 0) {
			printf("read on the socket\n");
			char buf[100];

			ret = read(0, buf, sizeof(buf));
			if (ret > 0)
				printf("read %d bytes \n", ret);
			else
				return -1;
		} else if (ret < 0) {
			if (errno == EINTR) {
				printf("interrupted!\n");
				return -1;
			}
		}
	}

	return -1;
}

