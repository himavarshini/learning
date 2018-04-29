#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "sysapi.h"
#include "logd_intf.h"
#include "logd_internal.h"

static int exiting = 0;

#define USAGE    "-l <local unix socket path>" \
                 "-r <remote ip> -c <remote port>"

int main(int argc, char **argv)
{
    struct logd logd;
    struct cmd_opts *opts = &logd.opts;
    int ret;
    int opt;

    memset(&logd, 0, sizeof(struct logd));

    set_default_opts(opts);

    while ((opt = getopt(argc, argv, "n:l:r:c:d:")) != -1) {
        switch (opt) {
        case 'l':
            opts->local_path = optarg;
            break;
        case 'r':
            opts->remote_path = optarg;
            break;
        case 'c':
            opts->remote_port = atoi(optarg);
            break;
        case 'n':
            opts->maxconn = atoi(optarg);
            break;
        case 'd':
            opts->directory = optarg;
            break;
        default:
            printf("%s %s\n", argv[0], USAGE);
            return -1;
        }
    }

    if (opts->remote_path && (opts->remote_port == -1)) {
        printf("remote ip needs a port to prepare and fire up the server\n");
        printf("%s %s\n", argv[0], USAGE);
        return -1;
    } else if ((opts->remote_port != -1) && !opts->remote_path) {
        printf("remote port needs an ip to prepare and fire up the server\n");
        printf("%s %s\n", argv[0], USAGE);
        return -1;
    }

    ret = sysapi_chroot_dir(logd.opts.directory);
    if (ret < 0)
        return -1;

    logd.client_table_list = sapi_list_init();
    if (!logd.client_table_list)
        return -1;

    ret = logd_create_server(&logd);
    if (ret < 0)
        goto err;

    sysapi_install_sighandler(SIGINT, exit_application);
    
    logd_loop(&logd);
    
    logd_destroy_server(&logd);
err:
    sapi_list_deinit(logd.client_table_list, &logd, logd_free_table_data);
    

    return 0;
}

void exit_application(int signal)
{
    exiting = 1;
}

void set_default_opts(struct cmd_opts *opts)
{
    opts->local_path = DEFAULT_SOCK_PATH;
    opts->remote_path = NULL;
    opts->remote_port = -1;
    opts->maxconn = LOGD_DEF_CONN;
    opts->directory = LOGD_DFL_DIR;
}

int logd_create_server(struct logd *logd)
{
    FD_ZERO(&logd->rdfds);

    if (logd->opts.local_path) {
        logd->sock_type = LOCAL_SOCK;
        logd->sock = sapi_unix_tcp_server_create(logd->opts.local_path,
                                                 logd->opts.maxconn);
        if (logd->sock < 0)
            return -1;

        FD_SET(logd->sock, &logd->rdfds);
    } else if (logd->opts.remote_path) {
        logd->sock_type = REMOTE_SOCK;
        logd->sock = sapi_inet_tcp_server_create(logd->opts.remote_path,
                                                 logd->opts.remote_port,
                                                 logd->opts.maxconn);
        if (logd->sock < 0)
            return -1;

        FD_SET(logd->sock, &logd->rdfds);
    }

    return 0;
}

void logd_destroy_server(struct logd *logd)
{
    if (logd->opts.local_path) {
        sapi_unix_tcp_server_destroy(logd->sock);
        sysapi_unlink_file(logd->opts.local_path);
        FD_CLR(logd->sock, &logd->rdfds);

    } else if (logd->opts.remote_path) {
        sapi_inet_tcp_server_destroy(logd->sock);
        FD_CLR(logd->sock, &logd->rdfds);
    }
}

static int max_fd(struct logd *logd)
{
    int mfd = logd->sock;
    struct sapi_list *list_item;

    sapi_list_foreach(logd->client_table_list, list_item) {
        struct logd_client_table *table_data = sapi_list_item_data(list_item);
        if (!table_data)
            continue;
        else if (table_data->client_sock > mfd)
            mfd = table_data->client_sock;
    }
    return mfd;
}

int logd_accept_client_conn(int fd, struct logd *logd)
{
    int ret = -1;
    int cli_sock;
    struct logd_client_table *table_data;

    cli_sock = accept(fd, NULL, NULL);
    if (cli_sock < 0)
        return ret;

    table_data = calloc(1, sizeof(struct logd_client_table));
    if (!table_data) {
        close(cli_sock);
        return ret;
    }

    table_data->client_sock = cli_sock;
    LOGD_SET_PRIV(table_data, logd);
    sapi_list_add_tail(logd->client_table_list, table_data);
    FD_SET(table_data->client_sock, &logd->rdfds);

    return 0;
}

struct logd_client_table *logd_get_client_table_from_fd(int fd,
                                                        struct logd *logd)
{
    struct sapi_list *list_item;
    struct logd_client_table *table_data;

    sapi_list_foreach(logd->client_table_list, list_item) {
        table_data = sapi_list_item_data(list_item);
        if (table_data->client_sock == fd)
            return table_data;
    }
    return NULL;
}

int logd_print_tstamp(char *fdata, int size)
{
    char buf[200];
    int ret;

    // we do not have a valid timestamp representation from gmtime

    ret = sysapi_snprintf_cur_caltime(buf, sizeof(buf));
    if (ret == -1)
        return 0;

    return snprintf(fdata, size, "[%s]   ", buf);
}

int logd_free_table_data(void *ctx, void *data)
{
    struct logd *logd;
    struct logd_client_table *table_data = data;

    logd = LOGD_GET_PRIV(table_data);
    close(table_data->client_sock);
    FD_CLR(table_data->client_sock, &logd->rdfds);
    free(data);
    return 0;
}

int logd_debuglog_close_file(int fd, struct logd_msg *msg, struct logd *logd)
{
    struct logd_client_table *table_data;
    char *close_msg = "[Logd file closed]\n";

    table_data = logd_get_client_table_from_fd(fd, logd);
    if (!table_data)
        return -1;
    if (!table_data->filename)
        return -1;
    if (!table_data->fdata)
        return -1;
    if (!table_data->fdata_ptr)
        return -1;
    if ((table_data->file_offset + strlen(close_msg)) >= table_data->file_size)
        return -1;
    table_data->file_offset += logd_print_tstamp(table_data->fdata_ptr +
                                                  table_data->file_offset,
                                                  table_data->file_size -
                                                  table_data->file_offset);
    table_data->file_offset += snprintf(table_data->fdata_ptr +
                                       table_data->file_offset,
                                       table_data->file_size -
                                       table_data->file_offset,
                                       "%s", close_msg);
    sysapi_sync_unmap_file(table_data->fdata);
    sysapi_truncate_file(table_data->filename, table_data->file_offset);
    free(table_data->filename);
    sapi_list_delete(logd->client_table_list, logd_free_table_data, table_data);
    return 0;
}

int logd_debuglog_sync_file(int fd, struct logd_msg *msg, struct logd *logd)
{
    struct logd_client_table *table_data;

    table_data = logd_get_client_table_from_fd(fd, logd);
    if (!table_data)
        return -1;
    if (!table_data->filename)
        return -1;
    if (!table_data->fdata)
        return -1;
    if (!table_data->fdata_ptr)
        return -1;
    sysapi_sync_file(table_data->fdata, table_data->file_offset -
                                        table_data->written);
    table_data->written = table_data->file_offset;
    gettimeofday(&table_data->last_synced, NULL);

    return 0;
}

int logd_debuglog_write(int fd, struct logd_msg *msg, struct logd *logd)
{
    int ret;
    struct logd_client_table *table_data;

    table_data = logd_get_client_table_from_fd(fd, logd);
    if (!table_data)
        return -1;
    if (!table_data->filename)
        return -1;
    if (!table_data->fdata)
        return -1;
    if (!table_data->fdata_ptr)
        return -1;
    if ((table_data->file_offset + msg->len) >= table_data->file_size)
        return -1;
    table_data->file_offset += logd_print_tstamp(table_data->fdata_ptr +
                                              table_data->file_offset,
                                              table_data->file_size -
                                              table_data->file_offset);
    memcpy(table_data->fdata_ptr + table_data->file_offset,
           msg->data,
           msg->len);
    table_data->file_offset += msg->len;

    return 0;
}

int logd_debuglog_create(int fd, struct logd_msg *msg, struct logd *logd)
{
    char *create_msg = "[Logd file created]\n";
    int ret = -1;
    struct logd_client_table *table_data;

    ret = sysapi_new_truncate_file(msg->data, LOGD_DEBUG_SIZE_MB);
    if (ret < 0)
        return ret;

    ///XXX: on error, needs to remove the created file
    table_data = logd_get_client_table_from_fd(fd, logd);
    if (!table_data)
        return ret;

    table_data->filename = strdup(msg->data);
    /// XXX: on error, needs to remove the crated file
    table_data->fdata = sysapi_map_file_rdwr(msg->data);
    if (!table_data->fdata)
        return ret;
    /// XXX: on error, needs to remove the created file
    table_data->fdata_ptr = sysapi_get_maped_fdata_ptr(table_data->fdata);
    if (!table_data->fdata_ptr)
        return ret;
    table_data->file_size = LOGD_DEBUG_SIZE_MB;
    table_data->file_offset = logd_print_tstamp(table_data->fdata_ptr,
                                               table_data->file_size);
    table_data->file_offset += snprintf(table_data->fdata_ptr +
                                       table_data->file_offset,
                                       table_data->file_size -
                                       table_data->file_offset,
                                       "%s", create_msg);
    return 0;
}

int logd_process_client_req(int fd, struct logd *logd)
{
    int ret= -1;
    struct logd_msg *msg;
    char recv_buf[BUFSIZ];

    msg = (struct logd_msg *)(recv_buf);
    ret = recv(fd, msg, sizeof(struct logd_msg), 0);
    if (ret <= 0)
        return -EPIPE;
    else if (ret == sizeof(struct logd_msg)) {
        if (msg->len != 0) {
            ret = recv(fd, msg->data, msg->len, 0);
            if (ret <= 0)
                return -EPIPE;
            else {
                switch (msg->file_type) {
                    case LOGD_FILE_TYPE_DEBUGLOG: {
                        switch (msg->msg_type) {
                            case LOGD_MSG_TYPE_OPEN_FILE: {
                                ret = logd_debuglog_create(fd, msg, logd);
                            }
                            break;
                            case LOGD_MSG_TYPE_FILE_DATA: {
                                ret = logd_debuglog_write(fd, msg, logd);
                            }
                            break;
                            case LOGD_MSG_TYPE_SYNC_TO_DISK: {
                                ret = logd_debuglog_sync_file(fd, msg, logd);
                            }
                            break;
                            case LOGD_MSG_TYPE_CLOSE_FILE: {
                                ret = logd_debuglog_close_file(fd, msg, logd);
                            }
                            break;
                        }
                    }
                    break;
                    default:
                        return ret;
                }
            }
        }
    }

    return ret;
}

int logd_check_fdset(fd_set *setfd, struct logd *logd)
{
    struct sapi_list *list_item;
    int fd;

    if (FD_ISSET(logd->sock, setfd))
        return logd->sock;

    sapi_list_foreach(logd->client_table_list, list_item) {
        struct logd_client_table *table_data = sapi_list_item_data(list_item);
        if (table_data && table_data->client_sock > 0) {
            if (FD_ISSET(table_data->client_sock, setfd))
                return table_data->client_sock;
        }
    }

    return -1;
}

void logd_loop(struct logd *logd)
{
    int ret;
    fd_set allfd;
    int mfd;
    int fd;

    while (!exiting) {
        mfd = max_fd(logd);
        allfd = logd->rdfds;

        ret = select(mfd + 1, &allfd, NULL, NULL, NULL);
        if (ret < 0)
            return;
        else if (ret > 0) {
            fd = logd_check_fdset(&allfd, logd);
            if (fd == logd->sock) {
                logd_accept_client_conn(fd, logd);
            } else if (fd > 0) {
                ret = logd_process_client_req(fd, logd);
                if (ret == -EPIPE) {
                    logd_debuglog_close_file(fd, NULL, logd);
                }
            }
        }
    }
}
