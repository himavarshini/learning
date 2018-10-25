#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "<%s> string\n", argv[0]);
        return -1;
    }

    fprintf(stderr, "length of string [%s] is %d\n", argv[1], strlen(argv[1]));
    return 0;
}

