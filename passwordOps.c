// C program to check password integrity from user side, and return a hashed password value to main function
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-constant-out-of-range-compare"
int check(const char pass[50], int len);
char* returnPasswordHash(const char passw[50], int max);
char* reversePasswordHash(const char passw_hash[75], int max);

int check(const char pass[50], int len){
    int i, a=0;
    for(i=0; i<len; i++){
        int ascii = pass[i];
        if(ascii>31 && ascii<65){
            a++;
        }
    }
    if(a>1){
        return 0;
    }
    else{
        return 1;
    }
}

char* returnPasswordHash(const char passw[50], int maxLen) {
    char* hashed = (char*)malloc(maxLen * sizeof(char));
    if (hashed == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Simple XOR-based hashing
    for (int i = 0; i < maxLen; i++) {
        hashed[i] = passw[i] ^ 10; // XOR with 10
    }

    return hashed;
}

char* reversePasswordHash(const char passw_hash[75], int maxLen){
    char* hashed = (char*)malloc(maxLen * sizeof(char));
    if (hashed == NULL) {
        // Handle memory allocation failure
        return NULL;
    }

    // Simple XOR-based hashing
    for (int i = 0; i < maxLen; i++) {
        hashed[i] = passw_hash[i] ^ 10; // XOR with 10
    }

    return hashed;
}

#pragma clang diagnostic pop