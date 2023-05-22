#include "func.h"
#include <stdio.h>
#include <stdint.h>

const uint8_t mapPC1[2][28]=
    {
        {
            57, 49, 41, 33, 25, 17, 9,
            1, 58, 50, 42, 34, 26, 18,
            10, 2, 59, 51, 43, 35, 27,
            19, 11, 3, 60, 52, 44, 36
        },
        {
            63, 55, 47, 39, 31, 23, 15,
            7, 62, 54, 46, 38, 30, 22,
            14, 6, 61, 53, 45, 37, 29,
            21, 13, 5, 28, 20, 12, 4
        }
    };

const uint8_t mapPC2[48]=
    {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32 
    };

const uint8_t leftShiftConst[16]={1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

uint32_t permuteChoice1(int mode, uint64_t key, int shiftNumber){
    uint32_t out = 0;
    for(int i=0; i<28; i++){
        uint32_t bit = (key >> mapPC1[mode][(28+i-shiftNumber)%28]) & 1;
        out = out | (bit << i);
    }
    return out;
}

uint64_t permuteChoice2(uint64_t cd){
    uint64_t out=0;
    for(int i=0; i<48; i++){
        uint64_t bit = (cd >> mapPC2[i]) &1;
        out = out | (bit<i);
    }
    return out;
}

uint64_t keySchedule(int n, uint64_t key){
    int shiftNumber = 0;
    for(int i=0; i<n; i++){
        shiftNumber += leftShiftConst[i];
    }
    uint64_t c =permuteChoice1(0, key, shiftNumber);
    uint32_t d =permuteChoice1(1, key, shiftNumber);
    uint64_t out = (c<<28) | d;
    out = permuteChoice2(out);
    return out;
}