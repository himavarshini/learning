daemonizer_src = daemon.c
test_src = test.c

override INCLUDES +=

test_bin:
	gcc -Wall test.c -o testdaemon

daemonizer_bin:
	gcc -Wall -I$(INCLUDES) daemon.c -lsysapi -pthread -o daemonizer

all: daemonizer_bin test_bin
clean:
	rm -rf daemonizer testdaemon
