#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/rtc.h>
#include <linux/ioctl.h>
#include <getopt.h>

#define RTC_DEV "/dev/rtc"
#define Y_OFFSET 1900
#define M_OFFSET 1

main(int a, char **c)
{
	struct rtc_time t;
	int get_opt;
	char *format = NULL;
	char *per_irq = NULL;
	char *set_freq = NULL;
	int rtc_path_fd;

	while ((get_opt = getopt(a, c, "g:f:s:")) != -1) {
		switch (get_opt) {
		case 'g':
			format = optarg;
			break;
		case 'f':
			per_irq = optarg;
			break;
		case 's':
			set_freq = optarg;
			break;
		default:
			return;
		}
	}

	rtc_path_fd = open(RTC_DEV, O_RDWR);
	if (rtc_path_fd < 0) {
		printf("failed to get the rtc dev\n");	
		return 1;
	}
	if (format) {
		if (ioctl(rtc_path_fd, RTC_RD_TIME, &t) < 0) {
			printf("can't get time\n");
			return 1;
		}

		if (strcasecmp(format, "12Hour") == 0) {
			t.tm_hour = t.tm_hour%12;
		}

		printf("TIME: %d/%d/%d %d:%d:%d\n", t.tm_mon + M_OFFSET, t.tm_mday,
									  t.tm_year + Y_OFFSET, t.tm_hour,
									  t.tm_min, t.tm_sec);
	}
	if (per_irq) {
		int data;
		if (ioctl(rtc_path_fd, RTC_IRQP_READ, &data) < 0) {
			printf("can't get peridic irq\n");
			return 1;
		}

		printf("Freq. of Periodic IRQ's %dHz\n", data);
	}
	if (set_freq) {
		int data;
		printf("Enter Freq:");
		scanf("%d", &data);

		if (ioctl(rtc_path_fd, RTC_IRQP_SET, data) < 0) {
			printf("can't set f\n");
			return 1;
		}
		printf("Freq set check with ./a.out -f <getfreq>\n");
	}
}
