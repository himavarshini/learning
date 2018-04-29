#ifndef __LOGD_INTERNAL_H__
#define __LOGD_INTERNAL_H__

#include <sys/socket.h>
#include <sys/un.h>

struct cmd_opts {
    char *local_path;
    char *remote_path;
    int remote_port;
    char *directory;
    int maxconn;
};

#define  LOCAL_SOCK  1
#define  REMOTE_SOCK 2

#define LOGD_DEBUG_SIZE (8 * 1024)
#define LOGD_DEBUG_SIZE_MB  LOGD_DEBUG_SIZE * 1024

#define LOGD_MAX_CONN 200
#define LOGD_DEF_CONN LOGD_MAX_CONN

#define LOGD_DFL_DIR "/var/log"

struct logd_client_table {
    int client_sock;
    char *filename;
    void *fdata;
    void *fdata_ptr;
    int file_size;
    int file_offset;
    int written;
    struct timeval last_synced, last_rcvd;
    void *priv;
};

#define LOGD_SET_PRIV(__tbl, __logd) ((__tbl->priv = __logd))
#define LOGD_GET_PRIV(__tbl) ((__tbl->priv))

struct logd {
    int sock;
    int sock_type;
    union {
        struct sockaddr_un local_addr;
        struct sockaddr_in remote_addr;
    } u;
    struct cmd_opts opts;
    void *client_table_list;
    fd_set rdfds;
};

void exit_application(int signal);

void set_default_opts(struct cmd_opts *opts);

int logd_create_server(struct logd *logd);

void logd_destroy_server(struct logd *logd);

static int max_fd(struct logd *logd);

int logd_accept_client_conn(int fd, struct logd *logd);

struct logd_client_table *logd_get_client_table_from_fd(int fd,
                                                        struct logd *logd);

int logd_print_tstamp(char *fdata, int size);

int logd_free_table_data(void *client_table_list, void *data);

int logd_debuglog_close_file(int fd, struct logd_msg *msg, struct logd *logd);

int logd_debuglog_sync_file(int fd, struct logd_msg *msg, struct logd *logd);

int logd_debuglog_write(int fd, struct logd_msg *msg, struct logd *logd);

int logd_debuglog_create(int fd, struct logd_msg *msg, struct logd *logd);

int logd_process_client_req(int fd, struct logd *logd);

int logd_check_fdset(fd_set *setfd, struct logd *logd);

void logd_loop(struct logd *logd);

#endif
