#include "func.h"
#include <stdint.h>
#include <stdio.h>

int main(){

    uint32_t R = 0xdefabcd9;
    uint64_t key = 0x0000123456789abc;
    uint64_t out=functionF(R, key);
    printf("%llx", out);
    return 0;
}
