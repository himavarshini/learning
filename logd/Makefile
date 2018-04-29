SRC += logd_main.c

TEST_SRC += logd_client.c

TARGET := Logd
TEST_TARGET := logd_test

CC := gcc
CC_CFLAGS := -Wall -g -ggdb #-Werror
CC_INCLUDES := -I../libsysapi/
CC_LDFLAGS := -lsysapi -pthread

all: logd_main.o logd_client.o
	$(CC) $(CC_INCLUDES) -o $(TARGET) logd_main.o $(CC_LDFLAGS)
	$(CC) $(CC_INCLUDES) -o $(TEST_TARGET) logd_client.o $(CC_LDFLAGS)
logd_main.o:
	$(CC) $(CC_CFLAGS) $(CC_INCLUDES) -c $(SRC)
logd_client.o:
	$(CC) $(CC_CFLAGS) $(CC_INCLUDES) -c $(TEST_SRC)
clean:
	rm -rf *.o $(TARGET) $(TEST_TARGET)
