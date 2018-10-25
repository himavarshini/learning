#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *comma;
    char delim = ',';

    if (argc != 2) {
        fprintf(stderr, "<%s> string\n", argv[0]);
        return -1;
    }

    comma = strchr(argv[1], delim);
    if (comma) {
        printf("comma %s\n", comma);
    }

    return 0;
}

