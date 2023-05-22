#include "func.h"
#include <stdint.h>
#include <stdio.h>

int main(){

    uint64_t plain = 0xabcdef1234567890;
    uint64_t key = 0xabcdabcdabcdabcd;
    uint64_t cipher=encrypt(plain, key);

    printf("Plain text: %llx\n", plain);
    printf("Cipher text: %llx\n", cipher);
    printf("\ndecrypt: %llx", encrypt(cipher, key));

    return 0;
}
