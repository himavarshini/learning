#include <stdio.h>
#include <string.h>

int main()
{
    char string1[] = "String example";
    char dest[20];

    strcpy(dest, string1);

    printf("string [%s] len [%d] destination [%s] len [%d]\n", string1, strlen(string1), dest, strlen(dest));

    return 0;
}

