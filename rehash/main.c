
#include "rehash.h"
#include <time.h>
#include<sys/time.h>

int main() {
    struct timeval startTime,endTime;
    float Timeuse;
    dictht ht[2];
    htInit(ht,STRING,2,1000);
//    output(ht,0);
    gettimeofday(&startTime,NULL);
    moveFun(ht,2);
    gettimeofday(&endTime,NULL);

    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);

    Timeuse /= 1000000;

    printf("Timeuse = %f\n",Timeuse);
//    freeHt(ht,DATA_SIZE);
//        output(ht,1,STRING);


    return 0;
}
