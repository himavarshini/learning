#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>

int main()
{
	int sock;

	sock = nn_socket(AF_SP, NN_PULL);
	if (sock < 0) {
		fprintf(stderr, "nn:socket open fail\n");
		return -1;
	}

	if (nn_bind(sock, "ipc:///tmp/test.ipc") < 0) {
		fprintf(stderr, "failed to bind\n");
		return -1;
	}

	for (;;) {
		char buff[1024];
		int ret;

		ret = nn_recv(sock, buff, sizeof(buff), 0);
		if (ret < 0) {
			fprintf(stderr, "failed to recv\n");
			return -1;
		}

		printf("receveid message %s\n", buff);
	}

	nn_close(sock);
	return 0;
}

