//
// Created by sean on 18-7-16.
//

//
// Created by sean on 18-7-12.
//

#include <sys/time.h>
#include "subThreadFun.h"
#include <stdio.h>
#include <pthread.h>

int global_cnt = 0;
int cnt[NR_THREAD+1]={0};
float Timeuse=0;
data array[5];
void* thread_work1()
{
    array[0].cnt=0;
    gettimeofday(&startTime,NULL);
    for(int i = 0 ; i < LOOP_TIMES;i++)
    {
#ifdef LOCK
        pthread_mutex_lock(&lock1);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        array[0].cnt++;
#endif
#ifdef LOCK
        pthread_mutex_unlock(&lock1);
#endif
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    printf("time used in thread1  cnt[1] is %f global_cnt is %d, Timeuse is %f s\n",array[0].cnt,global_cnt,Timeuse);
    return NULL;
}

void* thread_work2()
{
    int i;
    array[1].cnt=0;
    gettimeofday(&startTime,NULL);
    for(i = 0 ; i < LOOP_TIMES; i++ )
    {
#ifdef LOCK
        pthread_mutex_lock(&lock1);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        ++(array[1].cnt);
#endif
#ifdef LOCK
        pthread_mutex_unlock(&lock1);
#endif
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    printf("time used in thread2  cnt[2] is %f global_cnt is %d, Timeuse is %f s\n",array[1].cnt,global_cnt,Timeuse);
    return NULL;
}

void* thread_work3()
{
    gettimeofday(&startTime,NULL);
    for(int i = 0 ; i < LOOP_TIMES; i++ )
    {
#ifdef LOCK
        pthread_mutex_lock(&lock1);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        cnt[3]++;
#endif
#ifdef LOCK
        pthread_mutex_unlock(&lock1);
#endif
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    printf("time used in thread3  cnt[3] is %f global_cnt is %d, Timeuse is %f s\n",array[2].cnt,global_cnt,Timeuse);
    return NULL;
}


void* thread_work4()
{
    gettimeofday(&startTime,NULL);
    for(int i = 0 ; i < LOOP_TIMES; i++ )
    {
#ifdef LOCK
        pthread_mutex_lock(&lock1);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        cnt[4]++;
#endif
#ifdef LOCK
        pthread_mutex_unlock(&lock1);
#endif
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    printf("time used in thread4  cnt[4] is %d global_cnt is %d, Timeuse is %f s\n",cnt[4],global_cnt,Timeuse);
    return NULL;
}

void* thread_work5()
{
    gettimeofday(&startTime,NULL);
    for(int i = 0 ; i < LOOP_TIMES; i++ )
    {
#ifdef LOCK
        pthread_mutex_lock(&lock1);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        cnt[5]++;
#endif
#ifdef LOCK
        pthread_mutex_unlock(&lock1);
#endif
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    printf("time used in thread4  cnt[5] is %d global_cnt is %d, Timeuse is %f s\n",cnt[5],global_cnt,Timeuse);
    return NULL;
}