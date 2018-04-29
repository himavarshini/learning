/**
 * @copyright Dev Naga <devendra.aaru@gmail.com>
 *
 * A memory to disk sync API implemenetation in CPP
 * MIT Licensed
 */
 
#include <iostream>
#include <cstdint>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#define MEMBUF_SIZE_DEFL 1024 * 1024
class linuxMembufIO {
    private:
        uint8_t *memBuffer;
        int memBufWrOffset;
    public:
        linuxMembufIO()
        {
            memBuffer = new uint8_t[MEMBUF_SIZE_DEFL];
            if (!memBuffer) {
                std::cout<<"Failed to allocate memBuffer"<<std::endl;
                return;
            }

            memBufWrOffset = 0;
        }
        int writeMembuf(char *data, int len, char *filename, int *flen);
};

int linuxMembufIO::writeMembuf(char *data, int len, char *filename, int *flen)
{
    int ret;
    int fd;

    if ((memBufWrOffset + len) >= MEMBUF_SIZE_DEFL) {
        time_t now;
        struct tm *t;

        now = time(0);
        t = gmtime(&now);
        sprintf(filename, "%04d-%02d-%02d-%02d:%02d:%02d.txt",
                          t->tm_year + 1900,
                          t->tm_mon + 1,
                          t->tm_mday,
                          t->tm_hour,
                          t->tm_min,
                          t->tm_sec);
        fd = open(filename, O_CREAT | O_WRONLY, S_IRWXU);
        if (fd < 0) {
            std::cout<<"Failed to open file"<<filename<<std::endl;
            return -1;
        }

        write(fd, memBuffer, memBufWrOffset);
        close(fd);
        memset(memBuffer, 0, MEMBUF_SIZE_DEFL);
        memBufWrOffset = 0;
    }

    memcpy(memBuffer + memBufWrOffset, data, len);
    memBufWrOffset += len;

    return 0;
}

/// TESTING
int main(int argc, char **argv)
{
    linuxMembufIO memBuf;
    char *msg = "Hello this is membuf";
    char filename[20];
    int filename_len = 0;

    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    memBuf.writeMembuf(msg, strlen(msg), filename, &filename_len);
    return 0;
}
