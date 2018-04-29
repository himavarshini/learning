/**
 * @Copyright Dev Naga <devendra.aaru@gmail.com>
 * All rights reserved .. MIT Licensed
 *
 * This program does only AES Encrypt in the CBC mode with key size of 256.. this an example
 */
#include <wolfssl/wolfcrypt/aes.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    Aes aes, aes_d;
    int ret;
    int aes_key_fd, aes_iv_fd;
    int in_fd, out_fd;
    uint8_t key_val[32];
    uint8_t iv_val[16];

    aes_key_fd = open(argv[1], O_RDONLY);
    if (aes_key_fd < 0) {
        fprintf(stderr, "failed to open keyfd\n");
        return -1;
    }

    memset(key_val, 0, sizeof(key_val));
    read(aes_key_fd, key_val, sizeof(key_val));
    close(aes_key_fd);

    aes_iv_fd = open(argv[2], O_RDONLY);
    if (aes_iv_fd < 0) {
        fprintf(stderr, "failed to open ivfd\n");
        return -1;
    }

    memset(iv_val, 0, sizeof(iv_val));
    read(aes_iv_fd, iv_val, sizeof(iv_val));
    close(aes_iv_fd);

    // setup key and iv values for encrypt
    ret = wc_AesSetKey(&aes, key_val, sizeof(key_val), iv_val, AES_ENCRYPTION);
    if (ret != 0) {
        fprintf(stderr, "failed to set aes keyiv\n");
        return -1;
    }

    // setup key and iv values for decrypt
    ret = wc_AesSetKey(&aes_d, key_val, sizeof(key_val), iv_val, AES_DECRYPTION);
    if (ret != 0) {
        fprintf(stderr, "failed to set aes keyiv\n");
        return -1;
    }

    // open input file in read only
    in_fd = open(argv[3], O_RDONLY);
    if (in_fd < 0) {
        fprintf(stderr, "failed to open input file %s\n", argv[3]);
        return -1;
    }

    // create output file and write only
    out_fd = open(argv[4], O_CREAT | O_WRONLY, S_IRWXU);
    if (out_fd < 0) {
        return -1;
    }

    while (1) {
        uint8_t in_data[AES_BLOCK_SIZE * 16];
        uint8_t out_data[AES_BLOCK_SIZE * 16];

        memset(in_data, 0, sizeof(in_data));
        ret = read(in_fd, in_data, sizeof(in_data));
        if (ret <= 0) {
            break;
        }

        memset(out_data, 0, sizeof(out_data));

        // FIXME: padding must be added in pkcs7 format but right now we are not doing that
        // openssl usually takes care of that if you using that .. we using wolfssl so
        // we need to tkae care of the padding
        ret = wc_AesCbcEncrypt(&aes, out_data, in_data, sizeof(in_data));
        if (ret != 0) {
            fprintf(stderr, "failed to encrypt\n");
            break;
        }

        // write to the output the encrypted content
        write(out_fd, out_data, sizeof(out_data));
    }

    close(in_fd);
    close(out_fd);

    printf("encrypted\n");

/// test the input encrypted content

    int in_fd_d, out_fd_d;

    in_fd_d = open(argv[4], O_RDONLY);
    if (in_fd_d < 0) {
        return -1;
    }

    out_fd_d = open("decrypted.c", O_CREAT | O_WRONLY, S_IRWXU);
    if (out_fd_d < 0) {
        return -1;
    }

    while (1) {
        uint8_t in_data[AES_BLOCK_SIZE];
        uint8_t out_data[AES_BLOCK_SIZE];

        memset(in_data, 0, sizeof(in_data));
        ret = read(in_fd_d, in_data, sizeof(in_data));
        if (ret <= 0) {
            break;
        }

        memset(out_data, 0, sizeof(out_data));

        ret = wc_AesCbcDecrypt(&aes_d, out_data, in_data, sizeof(in_data));
        if (ret != 0) {
            break;
        }

        write(out_fd_d, out_data, sizeof(out_data));
    }

    close(in_fd_d);
    close(out_fd_d);

    printf("decrypted\n");

    return 0;
}
