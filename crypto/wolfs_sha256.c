#include <wolfssl/wolfcrypt/wc_port.h>
#include <wolfssl/wolfcrypt/sha256.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, char **argv)
{
    int ret;
    Sha256 sha256_priv;
    uint8_t hash[64];

    ret = wolfCrypt_Init();
    if (ret != 0) {
        fprintf(stderr, "failed to wolfCrypt_Init()\n");
        return ret;
    }

    ret = wc_InitSha256(&sha256_priv);
    if (ret != 0) {
        fprintf(stderr, "failed to init Sha256\n");
        return ret;
    }

    FILE *fp;

    fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "failed to open %s\n", argv[1]);
        return -1;
    }

    char data[2048];
    while (fgets(data, sizeof(data), fp)) {
        int length;

        length = strlen(data);

        wc_Sha256Update(&sha256_priv, (uint8_t *)data, length);
    }

    memset(hash, 0, sizeof(hash));
    wc_Sha256Final(&sha256_priv, hash);

    int i;

    fprintf(stderr, "Sha256   ");
    for (i = 0; i < 32; i ++) {
        uint8_t val;

        fprintf(stderr, "%02x", hash[i]);
    }
    fprintf(stderr, "\n");

    fclose(fp);

    return 0;
}
