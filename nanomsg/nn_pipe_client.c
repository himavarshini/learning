#include <stdio.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int sock;

	sock = nn_socket(AF_SP, NN_PUSH);
	if (sock < 0) {
		fprintf(stderr, "failed to nanomsg:sock\n");
		return -1;
	}

	if (nn_connect(sock, "ipc:///tmp/test.ipc") < 0) {
		fprintf(stderr, "failed to nnconnect\n");
		return -1;
	}

	for (;;) {
		char *msg = "Hello";
		int ret;

		sleep(1);

		ret = nn_send(sock, msg, strlen(msg) + 1, 0);
		if (ret < 0) {
			return -1;
		}
	}
}

