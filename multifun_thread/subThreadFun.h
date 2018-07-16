//
// Created by sean on 18-7-16.
//

#ifndef MULTIFUN_THREAD_SUBTHREADFUN_H
#define MULTIFUN_THREAD_SUBTHREADFUN_H
#ifndef UNTITLED5_SUBTHREADFUN_H
#define UNTITLED5_SUBTHREADFUN_H

#include <sys/param.h>
#define LOOP_TIMES 10000000
#define NR_THREAD 5
#define NO_COM
#define LOCK
pthread_mutex_t lock1;
struct timeval startTime,endTime;
extern float Timeuse;

typedef struct data{
    double cnt;
    char padding[120];

}data;

extern data array[5];

void* thread_work1();
void* thread_work2();
void* thread_work3();
void* thread_work4();
void* thread_work5();

#endif //UNTITLED5_SUBTHREADFUN_H
#endif //MULTIFUN_THREAD_SUBTHREADFUN_H
