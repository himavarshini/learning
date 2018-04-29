/**
 * @copyright Dev Naga <devendra.aaru@gmail.com>
 *
 * MIT License
 *
 * import the keys priv and pub from a buf .. so that we could load form a key file
 * generate the signature from imported keys
 *
 */
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cstdint>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/signature.h>
#include <wolfssl/wolfcrypt/hash.h>

using namespace std;

void hexdump(byte *buf, int len)
{
    int i;

    for (i = 0; i < len; i ++) {
        cout << " " <<hex<<unsigned(buf[i]);
    }
    cout<<endl;
}

int main(int argc, char **argv)
{
    int ret;

    ecc_key eccKey;
    byte eccPubKey[] = {
        0x4, 0x61, 0xdd, 0x1e, 0xa9, 0x3f, 0xbe, 0xd6,
        0x5a, 0xfc, 0xff, 0x13, 0x7b, 0x7c, 0x65, 0xa9,
        0x2f, 0xfa, 0x37, 0x46, 0xa0, 0x21, 0xfb, 0x84,
        0x47, 0x55, 0x3a, 0x7f, 0x95, 0xba, 0x4e, 0x0,
        0x74, 0xa5, 0xf5, 0x4a, 0x9d, 0xd9, 0x52, 0xe3,
        0xf1, 0x1f, 0x68, 0x8, 0x91, 0x7, 0x8b, 0xd5,
        0xf9, 0x5e, 0x10, 0x48, 0x31, 0xde, 0xba, 0x32,
        0x50, 0x20, 0x31, 0x2f, 0xfa, 0x6d, 0x4e, 0x7a,
        0xfc
    };
    byte eccPrivKey[] = {
        0xbb, 0xc, 0x1a, 0x6, 0x34, 0xc, 0xa, 0x14,
        0x4d, 0x7b, 0xac, 0x8b, 0xf9, 0x70, 0x99, 0x96,
        0x2, 0x3e, 0x55, 0x5c, 0x33, 0x37, 0x2, 0xbd,
        0x9f, 0xf0, 0xcc, 0xca, 0x82, 0x4c, 0x71, 0x21
    };

    RNG rng;

    byte text[] = "Hello ECC";
    wc_InitRng(&rng);

    word32 signLen;
    byte *signBuf;

    byte eccPubKey_h[ECC_BUFSIZE], eccPrivKey_h[ECC_BUFSIZE];

    wc_ecc_init(&eccKey);

    ret = wc_ecc_import_private_key(eccPrivKey, sizeof(eccPrivKey), eccPubKey, sizeof(eccPubKey), &eccKey);
    if (ret != 0) {
        cout << "Import of ECC keys failed"<<endl;
        return -1;
    }

    word32 eccPubKey_h_len, eccPrivKey_h_len;

    // verify the keys pub
    eccPubKey_h_len = ECC_BUFSIZE;
    ret = wc_ecc_export_x963(&eccKey, eccPubKey_h, &eccPubKey_h_len);
    if (ret != 0) {
        cout << "ECC Pubkey export failed"<<endl;
        return -1;
    }

    hexdump(eccPubKey_h, eccPubKey_h_len);

    // verify the keys priv
    eccPrivKey_h_len = ECC_BUFSIZE;
    ret = wc_ecc_export_private_only(&eccKey, eccPrivKey_h, &eccPrivKey_h_len);
    if (ret != 0) {
        cout << "ECC Privkey export failed"<<endl;
        return -1;
    }

    hexdump(eccPrivKey_h, eccPrivKey_h_len);

    signLen = wc_SignatureGetSize((wc_SignatureType)1, &eccKey, sizeof(eccKey));
    if (signLen <= 0) {
        cout << "ECC Signature type " << 1 << "not supported "<<endl;
        return -1;
    }

    cout << "Signature length good " << signLen<<endl;

    signBuf = new uint8_t[signLen];
    if (!signBuf) {
        cout << "Failed to allocate signature with length " << signLen << endl;
        return -1;
    }

    ret= wc_SignatureGenerate(WC_HASH_TYPE_SHA256, (wc_SignatureType)1, text, sizeof(text), signBuf, &signLen, &eccKey, sizeof(eccKey), &rng);
    if (ret != 0) {
        cout << "Failed generating the ECC signature"<<endl;
        return -1;
    }
    hexdump(signBuf, signLen);

    return 0;
}
