//
// Created by sean on 18-6-28.
//

#ifndef REHASH_REHASH_H
#define REHASH_REHASH_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
# define DATA_SIZE 10000
#define LINK_LEN 1000
#define CHAR_SIZE 10
typedef struct dictEntry{
    char* key;
    union{
        char *val;
        int u64;
        double d;
    }value;
    struct dictEntry *next;
} dictEntry;

typedef struct dictht{
    dictEntry **table;
    unsigned long size;
    unsigned long sizemask;
    unsigned long used;
}dictht;


void htInit(struct dictht *ht,int size);

void moveFun(struct dictht *ht,int size);

void output(struct dictht* ht,int size);
void freeHt(struct dictht* ht,int len);

#endif //REHASH_REHASH_H
