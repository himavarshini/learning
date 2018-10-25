#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    char *str1 = "brexit";
    char final_string[40];

    if (argc != 2) {
        fprintf(stderr, "<%s> string\n", argv[0]);
        return -1;
    }

    strcpy(final_string, str1);
    strcat(final_string, " ");
    strcat(final_string, argv[1]);

    printf("concatenated string [%s] len [%d]\n", final_string, strlen(final_string));

    return 0;
}

