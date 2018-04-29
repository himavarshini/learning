#include <stdio.h>
#include <string.h>

#define OS_TYPE "/proc/sys/kernel/ostype"
#define HOSTNAME "/proc/sys/kernel/hostname"
#define OS_RELEASE "/proc/sys/kernel/osrelease"
#define OS_VERSION "/proc/sys/kernel/version"
#define DOMAIN "/proc/sys/kernel/domainname"

#define MAX_BUF BUFSIZ
#define LAST_SLASH_R_TO_NULL(buf) \
	buf[strlen(buf) - 1] = '\0';

#define os_type() { \
\
		fp = fopen(OS_TYPE, "r"); \
		fgets(uname_str, MAX_BUF,fp); LAST_SLASH_R_TO_NULL(uname_str);\
		printf("%s ", uname_str); \
		fclose(fp); \
}

#define host_name() { \
		fp = fopen(HOSTNAME, "r"); \
		fgets(uname_str, MAX_BUF,fp); LAST_SLASH_R_TO_NULL(uname_str);\
		printf("%s ", uname_str); \
		fclose(fp); \
}
#define os_release() { \
		fp = fopen(OS_RELEASE, "r");\
		fgets(uname_str, MAX_BUF,fp); LAST_SLASH_R_TO_NULL(uname_str);\
		printf("%s ", uname_str); \
		fclose(fp); \
}

#define os_version() { \
		fp = fopen(OS_VERSION, "r"); \
		fgets(uname_str, MAX_BUF,fp); LAST_SLASH_R_TO_NULL(uname_str);\
		printf("%s ", uname_str); \
		fclose(fp); \
}

#define domain_name() { \
		fp = fopen(DOMAIN, "r"); \
		fgets(uname_str, MAX_BUF,fp); LAST_SLASH_R_TO_NULL(uname_str);\
		printf("%s ", uname_str); \
		fclose(fp); \
}

void usage()
{
	printf("./a.out -a | -s | -n | -r | -v\n");
}

int main(int a, char **v)
{
	int ret = -1;
	FILE *fp;
	char uname_str[MAX_BUF];
	int A = 0, S = 0, N = 0, R = 0, V = 0;

	while ((ret = getopt(a, v, "asnrv")) != -1) {
		switch(ret) {
		case 'a':
			A = 1;
			break;
		case 's':
			S = 1;
			break;
		case 'n':
			N = 1;
			break;
		case 'r':
			R = 1;
			break;
		case 'v':
			V = 1;
			break;
		default:
			usage();
			return ret;
		}
	}

	if (A ) {
		os_type();
		host_name();
		os_release();
		os_version();
		domain_name();
	}
	if (S) {
		os_type();
	}
	if (N) {
		host_name();
	}
	if (R) {
		os_release();
	}
	if (V) {
		os_version();
	}
	printf("\n");
	return ret;
}
