//
// Created by sean on 18-7-16.
//

#include <stdio.h>
#include<sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#define LOOP_TIMES 10000000
#define NR_THREAD 4
//#define NO_LOCK
//#define NO_COM
pthread_mutex_t lock;
struct timeval startTime,endTime;
float Timeuse;
double timecount=0;
int global_cnt = 0;
int cnt[NR_THREAD]={0};

void* thread_work2(void* param)
{
    int *num=(int*)param;
    printf("param is %d\n",*num);
    int i;
    gettimeofday(&startTime,NULL);
    for(i = 0 ; i < LOOP_TIMES; i++ )
    {
#ifndef NO_LOCK
        pthread_mutex_lock(&lock);
#endif
#ifndef NO_COM
        global_cnt++;
#endif
#ifdef NO_COM
        cnt[*num]++;
#endif
#ifndef NO_LOCK
        pthread_mutex_unlock(&lock);
#endif
    }
    gettimeofday(&endTime,NULL);

    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);

    Timeuse /= 1000000;
    printf("time used in thread[%d] is %f s\n",cnt[*num],Timeuse);
    return NULL;
}
int main(int argc ,char* argv[])
{
    pthread_t tid[NR_THREAD];
    char err_buf[1024];
    int i, ret;
    int num[NR_THREAD];
    ret = pthread_mutex_init(&lock,NULL);
    if(ret)
    {
        fprintf(stderr,"init rw lock failed (%s)\n",strerror_r(ret,err_buf, sizeof(err_buf)));
        exit(1);
    }
    for(i = 0 ; i < NR_THREAD ; i++)
    {
        num[i]=i;
        printf("i is %d\n",i);
        ret = pthread_create(&tid[i],NULL,thread_work2,(void*)&num[i]);
        if(ret != 0)
        {
            fprintf(stderr,"create thread failed ,return %d (%s)\n",
                    ret,strerror_r(ret,err_buf,sizeof(err_buf)));
        }
    }
    for(i = 0 ; i < NR_THREAD; i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    printf("the global_cnt is %d\n",global_cnt);
//    printf("thread num: %d\n",NR_THREAD);
//    printf("loops per thread : %d\n",LOOP_TIMES);
//    printf("expect result: %d\n",LOOP_TIMES*NR_THREAD);
//    printf("actual result:cnt1 is %d,  cnt2 is %d global_cnt is %d\n",cnt[1],cnt[2],global_cnt);
    exit(0);
}