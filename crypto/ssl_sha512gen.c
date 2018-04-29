#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char **argv)
{
    int fd;
    int i;
    int ret;

    if (argc != 2) {
        return -1;
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        return -1;
    }

    SHA512_CTX ctx;

    SHA512_Init(&ctx);
    for (;;) {
        char data[2000];

        memset(data, 0, sizeof(data));
        ret = read(fd, data, sizeof(data));
        if (ret <= 0) {
            break;
        }

        SHA512_Update(&ctx, data, ret);
    }

    uint8_t md[64];

    SHA512_Final(md, &ctx);

    printf("[%s] sha512sum:  ", argv[1]);
    for (i = 0; i < SHA512_DIGEST_LENGTH; i ++) {
        printf("%02x", md[i]);
    }
    printf("\n");

    return 0;
}
