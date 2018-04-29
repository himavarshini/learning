#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

// demo of signals with respect to the sleep involved in a process
// this lets us visualise that if a process is under sleep,
// it can be woken up as soon as the signal occurs (for now its SIGINT)
// we try adding more signals and see if that works ! and its true!
// 
int signals;
void signal_hdl(int s)
{
	printf("signalled\n");
	signals=  1;
}

int main(void)
{
	int ret = -1;
	struct sigaction act;
	struct timeval old, now;

	memset(&act, 0, sizeof(act));
	act.sa_handler = signal_hdl;

	ret = sigaction(SIGUSR1, &act, 0);
	if (ret) {
		printf("Cannot install signal handler\n");
		return -1;
	}

	while (1) {
		// these time measurements will tell us
		// that the sleep gets interrupted by a signal (atleast SIGINT as of now)
		//
	    gettimeofday(&old, 0);
		sleep(10);
		gettimeofday(&now, 0);
		printf("only slept %ld: %ld\n", now.tv_sec - old.tv_sec,
										now.tv_usec - old.tv_usec);
		if (signals) {
			printf("Quitting\n");
			return 0;
		}
	}

	return 0;
}

