#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int set_bits = 0;
	int set;
	int size;
	int i;
	int n;

#define usage_dec_to_bin() "learn_dec_to_bin <number>"

	if (argc != 2) {
		printf("%s\n", usage_dec_to_bin());
		return -1;
	}

	n = atoi(argv[1]);

	if (n & 0xff000000) {
		size = 32;
	} else if (n & 0x00ff0000) {
		size = 24;
	} else if (n & 0x0000ff00) {
		size = 16;
	} else {
		size = 8;
	}

	// this must be written in arch depedent manner :-(
	for (i = size - 1; i >= 0; i--) {
		set = (n & (1 << i))? 1: 0;
		if (set)
			set_bits++;
		printf("%d", set);
	}

	printf("\n");

	printf("no of bits set: %d\n", set_bits);
	return 0;
}

