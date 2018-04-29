/**
 * Program to generate rand num @ linux OS
 *
 * Dev Naga (devendra.aaru@gmail.com)
 */
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int fd;
    uint8_t rand[64];
    int ret;
    int no_bytes;
    int i;

    if (argc != 2) {
        return -1;
    }

    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        return -1;
    }

    no_bytes = atoi(argv[1]);

    if (no_bytes > sizeof(rand)) {
        return -1;
    }

    memset(rand, 0, sizeof(rand));
    ret = read(fd, rand, no_bytes);
    if (ret != no_bytes) {
        return -1;
    }

    for (i = 0; i < no_bytes; i ++) {
        printf("%02x", rand[i]);
    }
    printf("\n");

    return 0;
}

