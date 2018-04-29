#ifndef __LOGD_INTF_H__
#define __LOGD_INTF_H__

typedef enum {
    LOGD_FILE_TYPE_CSV,
    LOGD_FILE_TYPE_DEBUGLOG,
} Logd_file_type;

typedef enum {
    LOGD_MSG_TYPE_OPEN_FILE,
    LOGD_MSG_TYPE_FILE_DATA,
    LOGD_MSG_TYPE_SYNC_TO_DISK,
    LOGD_MSG_TYPE_CLOSE_FILE,
} Logd_msg_type;

#define DEFAULT_SOCK_PATH "/var/logd.sock"

struct logd_msg {
    Logd_file_type file_type;
    Logd_msg_type msg_type;
    int len;
    char data[0];
} __attribute__((__packed__));

#define LOGD_FORMAT_OPEN_CSV(filename, buf, buflen) {         \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;       \
    logd_msg->file_type = LOGD_FILE_TYPE_CSV;                 \
    logd_msg->msg_type  = LOGD_MSG_TYPE_OPEN_FILE;            \
    logd_msg->len       = buflen;                             \
    strcpy(logd_msg->data, filename);                         \
}

#define LOGD_GET_MSG_LEN(buf, msglen) {                          \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;       \
    msglen = sizeof(struct logd_msg) + logd_msg->len;            \
}

#define LOGD_FORMAT_OPEN_DEBUGLOG(filename, buf, buflen) {    \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;       \
    logd_msg->file_type = LOGD_FILE_TYPE_DEBUGLOG;            \
    logd_msg->msg_type  = LOGD_MSG_TYPE_OPEN_FILE;            \
    logd_msg->len       = buflen;                             \
    strcpy(logd_msg->data, filename);                         \
}

#define LOGD_GET_DATA_PTR(buf) (buf + sizeof(struct logd_msg))

#define LOGD_FORMAT_DATA_CSV(buf, buflen) {                    \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_CSV;                  \
    logd_msg->msg_type  = LOGD_MSG_TYPE_FILE_DATA;             \
    logd_msg->len       = buflen;                              \
}

#define LOGD_FORMAT_DATA_DEBUGLOG(buf, buflen) {               \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_DEBUGLOG;             \
    logd_msg->msg_type  = LOGD_MSG_TYPE_FILE_DATA;             \
    logd_msg->len       = buflen;                              \
}

#define LOGD_FORMAT_CLOSE_CSV(filename, buf, buflen) {         \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_CSV;                  \
    logd_msg->msg_type  = LOGD_MSG_TYPE_CLOSE_FILE;            \
    logd_msg->len       = buflen;                              \
    strcpy(logd_msg->data, buf);                               \
}

#define LOGD_FORMAT_CLOSE_DEBUGLOG(filename, buf, buflen) {    \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_DEBUGLOG;             \
    logd_msg->msg_type  = LOGD_MSG_TYPE_CLOSE_FILE;            \
    logd_msg->len       = buflen;                              \
    strcpy(logd_msg->data, buf);                               \
}

#define LOGD_FORMAT_SYNC_MSGCSV(buf) {                         \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_CSV;                  \
    logd_msg->msg_type  = LOGD_MSG_TYPE_SYNC_TO_DISK;          \
    logd_msg->len       = 0;                                   \
}

#define LOGD_FORMAT_SYNC_MSGDEBUGLOG(buf) {                    \
    struct logd_msg *logd_msg = (struct logd_msg *)buf;        \
    logd_msg->file_type = LOGD_FILE_TYPE_DEBUGLOG;             \
    logd_msg->msg_type  = LOGD_MSG_TYPE_SYNC_TO_DISK;          \
    logd_msg->len       = 0;                                   \
}

#endif
