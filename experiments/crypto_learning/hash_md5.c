#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <getopt.h>
#include "polarssl/md5.h"

int main(int argc, char *argv[])
{
	int fd;
	uint8_t *data = NULL;
	char buf[1024];
	int totlen;
	char *f = NULL;
	int off = 0;
	char *input = NULL;
	int opt;

#define usage_md5()	"learn_md5 -f <filename> -t <text input>\n" \
			"          with -f this program reads the file contents as the input\n" \
                        "          with -t it just takes the text that's preceding -t (thus not considering spaces\n"

	if (argc != 3) {
		printf("%s\n", usage_md5());
		return -1;
	}

	while ((opt = getopt(argc, argv, "t:f:")) != -1) {
		switch (opt) {
			case 'f':
				f = optarg;
			break;
			case 't':
				input = optarg;
			break;
			default:
				printf("%s\n", usage_md5());
				return -1;
		}
	}

	if (input) {
		data = (uint8_t *)input;
		totlen = strlen(input);
	} else {
		fd = open(f, O_RDONLY);
		if (fd < 0) {
			return -1;
		}

		totlen = 0;
		int ret;
		struct stat s;

		ret = stat(f, &s);
		if (ret < 0) {
			goto fail_open;
		}
		totlen = s.st_size;
		data = calloc(1, totlen);
		if (!data) {
			goto fail_open;
		}
		while (1) {
			int ret;

			memset(buf, 0, sizeof(buf));
			ret = read(fd, buf, sizeof(buf));
			if (ret < 0) {
				goto fail_alloc;
			} else if (ret == 0) {
				break;
			}
			memcpy(data + off, buf, ret);
			off += ret;
		}
	}
	uint8_t digest[16];
	md5(data, totlen, digest);

	printf("digest :");

	int i;
	for (i = 0; i < sizeof(digest); i++) {
		printf("%02x", digest[i] & 0xff);
	}

	printf("\n");
	return 0;
fail_alloc:
	free(data);
fail_open:
	close(fd);
	return -1;
}

