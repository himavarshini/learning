#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "sysapi.h"

void usage()
{
    printf("./daemon <directory>"
           " <lock filename> <processpath> <args1> <args2> ...\n");
    printf("\t a simple daemon maker of any (linux) program\n");
}

int main(int argc, char **argv)
{
    int ret;
    char *directory = NULL;
    char *filename = NULL;

    if (argc < 4) {
        usage();
        exit(1);
    }

    directory = argv[1];
    filename = argv[2];

    if (!directory)
        directory = "/";

    ret = sysapi_daemonize(directory, filename);
    if (ret < 0) {
        exit(1);
    }

    char **args;

    args = calloc(1, argc - 3);
    if (!args) {
        return -1;
    }

    int i;

    for (i = 0; i < argc - 3; i++) {
        args[i] = strdup(argv[i + 3]);
    }

    ret = execve(args[0], args, NULL);
    if (ret < 0) {
        return ret;
    }

    return 0;
}

