#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int var;

    if (argc != 2) {
        fprintf(stderr, "<%s> integer\n", argv[0]);
        return -1;
    }

    var = atoi(argv[1]);

    printf("var %d string [%s]\n", var, argv[1]);
    return 0;
}

