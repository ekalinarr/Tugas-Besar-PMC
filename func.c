#include "func.h"
#include "key.h"
#include <stdio.h>
#include <stdint.h>

const uint8_t permutePosition[64]=
    {
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7,
        56, 48, 40, 32, 24, 16, 8, 0,
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6
    };

const uint8_t inversePermutePosition[64]=
    {
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57, 25,
        32, 0, 40, 8, 48, 16, 56, 24
    };

const uint8_t mapE[48]=
    {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9, 10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32, 1
    };

const uint8_t mapP[32]=
    {
        16, 7, 20, 21,
        29, 12, 28, 17,
        1, 15, 23, 26,
        5, 18, 31, 10,
        2, 8, 24, 14,
        32, 27, 3, 9,
        19, 13, 30, 6,
        22, 11, 4, 25
    };

const uint8_t mapS[8][4][16]=
{
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14} 
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12} 
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1 ,15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

uint64_t initialPermutation(uint64_t input){
    uint64_t output=0;    
    for(int i=0; i<64; i++){
        uint64_t bit=(input >> permutePosition[i]) & 1;
        output = output | (bit << i);
    }
    return output;
}

uint64_t inversePermutation(uint64_t input){
    uint64_t output=0;
    for(int i=0; i<64; i++){
        uint64_t bit=(input >> inversePermutePosition[i]) & 1;
        output= output | (bit << i);
    }
    return output;
}

uint32_t funcP(uint32_t in){
    uint32_t out=0;
    for(int i=0; i<32; i++){
        uint32_t bit=(in >> mapP[i]) & 1;
        out = out | (bit<<i);
    }
    return out;
}

uint32_t funcS(uint64_t in){
    uint32_t out = 0;
    uint8_t s;
    uint8_t partition;
    for(int i=0; i<8; i++){
        s= (in >> (6*(7-i)))& 0xFF;
        partition = mapS[i][(((0x20&s)>>4 )| (s&1))][(s>>1)&0xF];
        out = out | partition<<(4*(7-i));
    }
    return out;
}

uint64_t funcE(uint32_t R){
    uint64_t out=0;
    uint64_t bit = 0;
    for(int i=0; i<48; i++){
        bit = (R >> mapE[i]) & 1;
        out = out | bit<<i;
    }
    return out;
}

uint32_t functionF(uint32_t R, uint64_t key){
    uint64_t out=funcE(R);
    out = out ^ key;
    out = funcS(out);
    out = funcP(out);
    return out;
}

uint64_t encrypt(uint64_t plain_text, uint64_t key){
    uint32_t left = initialPermutation(plain_text)>>32;
    uint32_t right = initialPermutation(plain_text);
    for(int i=1; i<17; i++){
        uint32_t temp = right;
        right = functionF(right, keySchedule(i, key))^left;
        left = temp;
    }
    uint64_t out= right;
    out= (out<<32) | left;
    out = inversePermutation(out);
    return out;
}

// PASTIIN LAGI XIXIXIXIXIXIXI
// Generate key
uint64_t generate_key_uint64(uint64_t input) {
    uint64_t key = input % (uint64_t)(pow(26, 8));
    return key;
}

uint64_t generate_key_int(int input1, int input2, int input3, int input4, int input5, int input6, int input7, int input8) {
    int inputs[] = {input1, input2, input3, input4, input5, input6, input7, input8};
    uint64_t key = 0;
    for (int i = 0; i < 8; i++) {
        if (inputs[i] < 1 || inputs[i] > 26) {
            printf("Input integers must be in the range 1 to 26.\n");
            return 0;
        }
        key = key * 26 + (inputs[i] - 1);
    }
    return key;
}

// Ubah string ke unsigned
uint64_t stringToUnsigned64BitInteger(const char* str) {
    return strtoull(str, NULL, 0);
}

// convert uint64_t
char* uint64ToString(uint64_t value) {
    uint64_t temp = value;
    int length = 0;
    do {
        length++;
        temp /= 10;
    } while (temp > 0);

    char* str = (char*)malloc((length + 1) * sizeof(char));

    str[length] = '\0';
    do {
        length--;
        str[length] = '0' + (value % 10);
        value /= 10;
    } while (value > 0);

    return str;
}
