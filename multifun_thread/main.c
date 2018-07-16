#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "subThreadFun.h"



int main(int argc ,char* argv[])
{
    pthread_t tid[NR_THREAD];
    char err_buf[1024];
    int i, ret;
    ret = pthread_mutex_init(&lock1,NULL);

    if(ret)
    {
        fprintf(stderr,"init rw lock failed (%s)\n",strerror_r(ret,err_buf, sizeof(err_buf)));
        exit(1);
    }
//    for(i = 0 ; i < NR_THREAD ; i++)
    {
        ret = pthread_create(&tid[0],NULL,thread_work1,NULL);
        if(ret != 0)
            printf("thread created failed!\n");

        ret = pthread_create(&tid[1],NULL,thread_work2,NULL);
        if(ret != 0)
            printf("thread created failed!\n");

        ret = pthread_create(&tid[2],NULL,thread_work3,NULL);

        if(ret != 0)
            printf("thread created failed!\n");
//
        ret = pthread_create(&tid[3],NULL,thread_work4,NULL);
        if(ret != 0)
            printf("thread created failed!\n");
//        ret = pthread_create(&tid[4],NULL,thread_work5,NULL);
//        if(ret != 0)
//            printf("thread created failed!\n");
    }
//    for(i = 0 ; i < NR_THREAD; i++)
    {
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
        pthread_join(tid[2],NULL);
        pthread_join(tid[3],NULL);
//        pthread_join(tid[4],NULL);
    }
    pthread_mutex_destroy(&lock1);
    exit(0);
}