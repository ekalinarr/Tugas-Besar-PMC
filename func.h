#ifndef func_h
#define func_h

#include <stdint.h>

uint64_t initialPermutation(uint64_t inputKey);
uint64_t inversePermutation(uint64_t inputKey);
uint32_t funcP(uint32_t in);
uint32_t funcS(uint64_t in);
uint64_t funcE(uint32_t R);
uint32_t functionF(uint32_t R, uint64_t key);
uint64_t encrypt(uint64_t plain_text, uint64_t key);
#endif