#include <stdio.h>
#include <libgen.h>

char *path_name = "/usr/include/";
char *file_name = "/usr/include/abc.h";

int main(void)
{
    printf("%s\n", basename(path_name));
    printf("%s\n", basename(file_name));

    return 0;
}
