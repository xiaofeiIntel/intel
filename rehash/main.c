
#include "rehash.h"
#include <pthread.h>
//#define TIME
#define MULTITHRED

long subCount=0;
// long count;
pthread_t subThread;
void subThreadFun(void *htable)
{
    dictht* ht=(dictht*)htable;
    for(int i=0;i<DATA_SIZE;i++)
    {
#ifdef USEMUTEX
        pthread_mutex_lock(&mutex);
#endif
        strcat(ht->table[i]->value.val,"sub");
        ++count;
#ifdef USEMUTEX
        pthread_mutex_unlock(&mutex);
#endif
#ifdef NOCOMP
        pthread_mutex_lock(&mutex);
        cnt[0]++;
        pthread_mutex_unlock(&mutex);
#endif
        dictEntry* ptr=ht->table[i]->next;
        for(int j=1;j<LINK_LEN;j++)
        {
#ifdef USEMUTEX
            pthread_mutex_lock(&mutex);
#endif
            strcat(ptr->value.val,"sub1");
            ++count;
#ifdef USEMUTEX
            pthread_mutex_unlock(&mutex);
#endif
#ifdef NOCOMP
            pthread_mutex_lock(&mutex);
            cnt[0]++;
            pthread_mutex_unlock(&mutex);
#endif
            ptr=ptr->next;
        }
//        printf("sub thread  changed  table[%d] value %s and next node's value %s\n",i,ht->table[i]->value.val,ptr->value.val);
    }
//    printf("count is %ld\n",count);
}
int main() {

    dictht ht[2];
    int res;
    htInit(ht,STRING,2,1000);
#ifdef TIME
    gettimeofday(&startTime,NULL);
#endif
#ifdef MULTITHRED
    res=pthread_create(&subThread,NULL,(void*)subThreadFun,(void*)&ht[0]);
    if(res!=0)
        printf("create sub thread failed");
#endif
    moveFun(ht,2);
#ifdef MULTITHRED
    pthread_join(subThread,NULL);
#endif
#ifdef TIME


//    freeHt(ht);
#endif
//    printMultiThread(ht,STRING);
#ifdef TIME
    printf("Timeuse = %f\n",Timeuse);
#endif
    return 0;
}
