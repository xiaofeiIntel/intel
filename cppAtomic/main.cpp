#include <iostream>
#include <atomic>
#include <sys/time.h>
//#include <threads.h>
#include <pthread.h>
using namespace std;

#define THREAD_NUM 4
#define NUM 10000000
#define SPIN
atomic_int acnt(0);
int cnt;
struct timeval startTime,endTime;
float Timeuse=0.0;
pthread_spinlock_t spinlock;
void* f(void* thr_data)
{
    gettimeofday(&startTime,NULL);
    for(int n = 0; n < NUM; ++n) {
#ifdef SPIN
        pthread_spin_lock(&spinlock);
        ++cnt;
        pthread_spin_unlock(&spinlock);
#endif
#ifndef SPIN
        ++acnt;
#endif
        // for this example, relaxed memory order is sufficient, e.g.
        // atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed);
    }
    gettimeofday(&endTime,NULL);
    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);
    Timeuse /= 1000000;
    int count=acnt;
    printf("time used is %f and acnt is %d \n",Timeuse,count);
}

int main(void)
{
//    thrd_t thr[10];
    pthread_t threadarr[10];
    int ret=pthread_spin_init(&spinlock,NULL);
    for(int n = 0; n < THREAD_NUM; ++n)
//        thrd_create(&thr[n], f, NULL);
        pthread_create(&threadarr[n],NULL,f,NULL);
    for(int n = 0; n < THREAD_NUM; ++n)
//        thrd_join(thr[n], NULL);
        pthread_join(threadarr[n],NULL);
    pthread_spin_destroy(&spinlock);
//    printf("The atomic counter is %u\n", acnt);
    printf("The non-atomic counter is %u\n", cnt);
}