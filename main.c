#include "func.h"
#include <stdint.h>
#include <stdio.h>

int main(){

    uint64_t  in= 0x0123456789abcdef;
    uint64_t out = initialPermutation(in);
    printf("%llx\n", out);
    out = inversePermutation(out);
    printf("%llx\n", out);

    return 0;
}
