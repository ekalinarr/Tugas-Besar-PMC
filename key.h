#ifndef key_h
#define key_h

#include <stdint.h>

uint32_t permuteChoice1(int mode, uint64_t key, int shiftNumber);
uint64_t permuteChoice2(uint64_t cd);
uint64_t keySchedule(int n, uint64_t key);

#endif