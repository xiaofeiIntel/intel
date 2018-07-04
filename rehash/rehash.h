//
// Created by sean on 18-6-28.
//

#ifndef REHASH_REHASH_H
#define REHASH_REHASH_H

#include <stdio.h>
#include<stdlib.h>
#include<string.h>
# define DATA_SIZE 10000
#define LINK_LEN 5
#define CHAR_SIZE 10
#define STRING 1
#define LIST 2

typedef struct listNode{
    struct listNode *pre;
    struct listNode *next;
    void *value;
    //第几个dictEntry节点的编号
    void *nodeNum;
  //  int listNodeNum;
}listNode;

typedef struct list{
    listNode * head;
    listNode * tail;
    //list的长度
    unsigned long len;
    /*节点复制函数*/
    void *(*dup)(void*ptr);
    /*节点释放函数*/
    void (*free)(void*ptr);
    /*节点值对比函数*/
    int (*match)(void *ptr,void *key);
}list;


typedef struct dictEntry{
    char* key;
    int dataTypeFlag;
    union{
        char *val;
        int u64;
        double d;
        struct list *linkList;
    }value;
    struct dictEntry *next;
} dictEntry;

typedef struct dictht{
    dictEntry **table;
    unsigned long size;
    unsigned long sizemask;
    unsigned long used;
}dictht;

/*nodeNum是当前dictentry的编号*/
list* listInit(int size,int nodeNum);
void htInit(struct dictht *ht,int type,int size,int threshold);

void moveFun(struct dictht *ht,int size);
void moveLinkList(struct dictEntry **table,struct dictEntry* table0);
void output(struct dictht* ht,int size,int type);
void freeHt(struct dictht* ht,int len);

#endif //REHASH_REHASH_H
