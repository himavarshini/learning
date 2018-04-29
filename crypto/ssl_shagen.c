/**
 * Program to generate sha1 - using openssl libs
 *
 * Dev Naga (devendra.aaru@gmail.com)
 */
#include <stdio.h>
#include <sys/types.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char **argv)
{
	int fd;
	uint8_t sha1sum[40];

	if (argc != 2) {
		fprintf(stderr, "generate sha1 for a file\n\n <%s> filename>\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		fprintf(stderr, "failed to open %s \n", argv[1]);
		return -1;
	}

	SHA_CTX c;

	SHA1_Init(&c);

	for (;;) {
		char data[2000];
		int ret;

		memset(data, 0, sizeof(data));
		ret = read(fd, data, sizeof(data));
		if (ret <= 0) {
			break;
		}
		SHA1_Update(&c, data, ret);
	}
	SHA1_Final(sha1sum, &c);

	int i;

	printf("[%s] sha1sum: ", argv[1]);
	for (i = 0; i < SHA_DIGEST_LENGTH; i ++) {
		printf("%02x", sha1sum[i]);
	}
	printf("\n");

	return 0;
}

