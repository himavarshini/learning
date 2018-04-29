#include <stdio.h>
#include <signal.h>

void signal_handler(int n)
{
	printf("crash!!\n");
}

int main(void)
{
	int *p = NULL;

	signal(SIGSEGV, signal_handler);

	*p = 10;

	printf("%s\n", p);
}
