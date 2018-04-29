/**
 * Program to generate sha256 using openssl
 *
 * Dev Naga (devendra.aaru@gmail.com)
 */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <openssl/sha.h>

int main(int argc, char **argv)
{
	if (argc != 2) {
		return -1;
	}

	int fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		return -1;
	}

	SHA256_CTX ctx;

	SHA256_Init(&ctx);
	int i;

	int ret;

	for (;;) {
		char data[2000];

		memset(data, 0, sizeof(data));
		ret = read(fd, data, sizeof(data));
		if (ret <= 0) {
			break;
		}
		SHA256_Update(&ctx, data, ret);
	}

	uint8_t md[64];

	SHA256_Final(md, &ctx);

	printf("[%s] sha256sum: ", argv[1]);
	for (i = 0; i < SHA256_DIGEST_LENGTH; i ++) {
		printf("%02x", md[i]);
	}
	printf("\n");
}

