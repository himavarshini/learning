#include <stdio.h>
#include <stdlib.h>

int (*add_two_num)(int a, int b);

int add(int a, int b)
{
    return a + b;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "<%s> a b\n", argv[0]);
        return -1;
    }

    add_two_num = add;

    printf("result %d\n", add_two_num(atoi(argv[1]), atoi(argv[2])));
    return 0;
}

