/**
 * @copyright Dev Naga <devendra.aaru@gmail.com>
 *
 * signing the sha 20 byte hash with ECC random keys
 *
 * MIT Licnesed
 */

#include <iostream>
#include <cstdio>
#include <cstdint>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/sha.h>
#include <wolfssl/wolfcrypt/signature.h>
#include <wolfssl/wolfcrypt/hash.h>
#include <wolfssl/wolfcrypt/ecc.h>

using namespace std;

class ShaHashFile {
    private:
        Sha shaData;
    public:
        ShaHashFile();
        void getShaHash(char *filanem, uint8_t hash_out[64]);
};

class eccSign {
    private:
        ecc_key key;
        RNG rng;
    public:
        eccSign();
        int generateEccSignatureForHash(uint8_t *hash, int hash_len, uint8_t *signature, word32 *signature_len);
};

ShaHashFile::ShaHashFile()
{
    int ret;

    ret = wc_InitSha(&shaData);
    if (ret != 0) {
        cout << "failed to sha512 init"<<endl;
        return;
    }
}


eccSign::eccSign()
{
    wc_InitRng(&rng);
    wc_ecc_init(&key);
    wc_ecc_make_key(&rng, 32, &key);
}

void ShaHashFile::getShaHash(char *fname, uint8_t *hash)
{
    int fd;
    int ret;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        return;
    }

    while (1) {
        uint8_t msg[1024];

        ret = read(fd, msg, sizeof(msg));
        if (ret <= 0) {
            break;
        }

        wc_ShaUpdate(&shaData, msg, ret);
    }
    wc_ShaFinal(&shaData, hash);
    close(fd);
}

int eccSign::generateEccSignatureForHash(uint8_t *hash, int hash_len, uint8_t *sign, word32 *sign_len)
{
    int ret;

    ret = wc_ecc_sign_hash(hash, hash_len, sign, sign_len, &rng, &key);
    if (ret != 0) {
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int ret;
    ShaHashFile shaPriv;
    eccSign eccSign;

    uint8_t hash[64];

    memset(hash, 0, sizeof(hash));
    shaPriv.getShaHash(argv[1], hash);

    int i;

    cout << "sha ";
    for (i = 0; i < 20; i ++)
        cout << " " <<hex<<unsigned(hash[i]);
    cout <<endl;

    uint8_t sign[512];
    word32 sign_len = sizeof(sign);

    ret = eccSign.generateEccSignatureForHash(hash, 20, sign, &sign_len);
    if (ret != 0) {
        cout <<"failed generating signature hash"<<endl;
        return -1;
    }

    cout <<"Signature length : "<<sign_len<<endl;
    for (i = 0; i < sign_len; i ++) {
        cout <<hex<<unsigned(sign[i]);
    }
    cout<<endl;
    return 0;
}
 
