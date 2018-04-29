/**
  * @copyright Dev Naga <devendra.aaru@gmail.com>
  *
  * MIT Licensed
  *
  * Sample program to generate sign and verify messages
  *
  * Taken from the Wolfssl examples here <https://github.com/wolfSSL/wolfssl-examples/blob/master/signature/signature.c>
  */
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdint>
#include <wolfssl/options.h>
#include <wolfssl/wolfcrypt/ecc.h>
#include <wolfssl/wolfcrypt/signature.h>
#include <wolfssl/wolfcrypt/hash.h>

using namespace std;

void hexdump(byte *data, int len)
{
    int i;

    for (i = 0; i < len; i ++) {
        cout << unsigned(data[i]);
    }

    cout << endl;
}

int main(int argc, char **argv)
{
    int ret;

    // ecc key context
    ecc_key eccKey;

    // rng context
    RNG rng;

    // signature buffer
    byte *signBuf = NULL;
    word32 signLen;

    // priv and pub key buffers
    byte eccPubKeyBuf[ECC_BUFSIZE], eccPrivKeyBuf[ECC_BUFSIZE];
    word32 eccPubKeyLen, eccPrivKeyLen;

    // text to sign
    byte text[] = "Hello ECC";

#if 0
    /* NIST Prime Curves */
    ECC_SECP192R1 = 1,
    ECC_PRIME192V2 = 2,
    ECC_PRIME192V3 = 3,
    ECC_PRIME239V1 = 4,
    ECC_PRIME239V2 = 5,
    ECC_PRIME239V3 = 6,
    ECC_SECP256R1 = 7,

    /* SECP Curves */
    ECC_SECP112R1 = 8,
    ECC_SECP112R2 = 9,
    ECC_SECP128R1 = 10,
    ECC_SECP128R2 = 11,
    ECC_SECP160R1 = 12,
    ECC_SECP160R2 = 13,
    ECC_SECP224R1 = 14,
    ECC_SECP384R1 = 15,
    ECC_SECP521R1 = 16,

    /* Koblitz */
    ECC_SECP160K1 = 17,
    ECC_SECP192K1 = 18,
    ECC_SECP224K1 = 19,
    ECC_SECP256K1 = 20,

    /* Brainpool Curves */
    ECC_BRAINPOOLP160R1 = 21,
    ECC_BRAINPOOLP192R1 = 22,
    ECC_BRAINPOOLP224R1 = 23,
    ECC_BRAINPOOLP256R1 = 24,
    ECC_BRAINPOOLP320R1 = 25,
    ECC_BRAINPOOLP384R1 = 26,
    ECC_BRAINPOOLP512R1 = 27,
#endif

    int key_type = ECC_SECP256R1;

    wc_InitRng(&rng);

    wc_ecc_init(&eccKey);
    ret = wc_ecc_make_key_ex(&rng, 32, &eccKey, key_type);
    if (ret != 0) {
        cout << "eccKeygen failure" << endl;
        return -1;
    }

    eccPubKeyLen = ECC_BUFSIZE;
    ret = wc_ecc_export_x963(&eccKey, eccPubKeyBuf, &eccPubKeyLen);
    if (ret != 0) {
        cout << "Ecc pubkey export failure" << endl;
        return -1;
    }

    cout << "Pubkey export good, Length: " << eccPubKeyLen << endl;
    hexdump(eccPubKeyBuf, eccPubKeyLen);

    eccPrivKeyLen = ECC_BUFSIZE;
    ret = wc_ecc_export_private_only(&eccKey, eccPrivKeyBuf, &eccPrivKeyLen);
    if (ret != 0) {
        cout << "Ecc privkey export failure" << endl;
        return -1;
    }

    cout << "Priv key export good, Length: " << eccPrivKeyLen << endl;
    hexdump(eccPrivKeyBuf, eccPrivKeyLen);

    signLen = wc_SignatureGetSize((wc_SignatureType)1, &eccKey, sizeof(eccKey));
    if (signLen <= 0) {
        cout << "ECC signature type " << 1 << "not supported "<< endl;
        return -1;
    }

    cout << "creating buffer for signature " << signLen <<endl;
    signBuf = new uint8_t[signLen];
    if (!signBuf) {
        cout << "Failed allocate sign buf with length " << signLen;
        return -1;
    }

#if 0
        WC_HASH_TYPE_NONE = 0,
        WC_HASH_TYPE_MD2 = 1,
        WC_HASH_TYPE_MD4 = 2,
        WC_HASH_TYPE_MD5 = 3,
        WC_HASH_TYPE_SHA = 4, /* SHA-1 (not old SHA-0) */
        WC_HASH_TYPE_SHA224 = 5,
        WC_HASH_TYPE_SHA256 = 6,
        WC_HASH_TYPE_SHA384 = 7,
        WC_HASH_TYPE_SHA512 = 8,
        WC_HASH_TYPE_MD5_SHA = 9,
        WC_HASH_TYPE_SHA3_224 = 10,
        WC_HASH_TYPE_SHA3_256 = 11,
        WC_HASH_TYPE_SHA3_384 = 12,
        WC_HASH_TYPE_SHA3_512 = 13,
        WC_HASH_TYPE_BLAKE2B = 14,
#endif

    ret = wc_SignatureGenerate(WC_HASH_TYPE_SHA256, (wc_SignatureType)1, text, sizeof(text), signBuf, &signLen, &eccKey, sizeof(eccKey), &rng);
    if (ret != 0) {
        cout << "Failed to generate ECC signature" << endl;
        return -1;
    }

    cout << "ECC Signature Good. Length: "<< signLen <<endl;
    hexdump(signBuf, signLen);

    ecc_key eccKey_verify;

    wc_ecc_init(&eccKey_verify);

    ret = wc_ecc_import_x963(eccPubKeyBuf, eccPubKeyLen, &eccKey_verify);
    if (ret != 0) {
        cout <<"Public key import failure" << endl;
        return -1;
    }

    ret = wc_SignatureVerify(WC_HASH_TYPE_SHA256, (wc_SignatureType)1, text, sizeof(text), signBuf, signLen, &eccKey, sizeof(eccKey));
    if (ret != 0) {
        cout <<"ECC Signature verify fail"<<endl;
        return -1;
    }

    cout << "ECC Signature verify Good"<<endl;
    return 0;
}
