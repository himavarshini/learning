#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <net/if.h>

int get_ethmac(char *ifname, uint8_t *mac)
{
	struct ifreq ifreq;

	int sd;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0) {
		*mac = 0;
		return -1;
	}


	strncpy(ifreq.ifr_name, ifname, IFNAMSIZ);
	ifreq.ifr_addr.sa_family = AF_INET;
	if (ioctl(sd, SIOCGIFHWADDR, &ifreq) < 0) {
		close(sd);
		*mac = 0;
		return -1;
	}

	memcpy(mac, ifreq.ifr_addr.sa_data, 6);
	close(sd);
	return 1;
}

void usage()
{
	printf("./a.out interface_name[ex. eth0, or eth1 or wlan0]\n");
}

int main(int a, char **v)
{
	int ret = -1;
	uint8_t mac[6];

	if (a != 2) {
		usage();
		return ret;
	}
	ret = get_ethmac(v[1], mac);

	if (ret > 0) {
		printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
					 mac[0], mac[1], mac[2], 
					 mac[3], mac[4], mac[5]);
	} else {
		printf("Failed to get MAC .. pls check u r root and running this code\n");
	}
	return ret;
}
