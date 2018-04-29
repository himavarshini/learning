// compile with the -lssl -lcrypto
// install libssl-dev on linux

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main()
{
    int i;
    char data[] = "Hello";
    uint8_t md[32];
    
    SHA1(data, strlen(data), md);
    
    for (i = 0; i < 20; i ++) { //sha1 is 160 bits / 8 bits per byte in length
        printf("%02x", md[i]);
    }
    printf("\n");
    
    return 0;
}
