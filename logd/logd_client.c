#include <stdio.h>
#include <string.h>
#include "sysapi.h"
#include "logd_intf.h"

int sock;
char *temp_data = "This is test data";
char *filename = "../../test_file.debug";

int main(int argc, char **argv)
{
    int ret;
    char msg[200];
    char *data;
    int msg_len;
    char *path = DEFAULT_SOCK_PATH;

    if (argv[1]) {
        path = argv[1];
    }

    sock = sapi_unix_tcp_client_create(path);
    if (sock < 0)
        return -1;

    memset(msg, 0, sizeof(msg));

    LOGD_FORMAT_OPEN_DEBUGLOG(filename, msg, strlen(filename) + 1);
    LOGD_GET_MSG_LEN(msg, msg_len);
    sapi_unix_tcp_transmit(sock, msg, msg_len);

    data = LOGD_GET_DATA_PTR(msg);
    int i;

    for (i = 0; i < 20000000; i++) {
        int len;

        len = sprintf(data, "%s, %d\n", temp_data, i);
        LOGD_FORMAT_DATA_DEBUGLOG(msg, len);
        LOGD_GET_MSG_LEN(msg, msg_len);
        sapi_unix_tcp_transmit(sock, msg, msg_len);
    }

    LOGD_FORMAT_CLOSE_DEBUGLOG(filename, msg, strlen(filename) + 1);
    LOGD_GET_MSG_LEN(msg, msg_len);
    sapi_unix_tcp_transmit(sock, msg, msg_len);

    return 0;
}
