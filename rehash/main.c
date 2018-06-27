
#include "rehash.h"



int main() {

    dictht ht[2];
    htInit(ht,2);
//    output(ht,0);
    moveFun(ht,2);
//    freeHt(ht,DATA_SIZE);
    //
    output(ht,1);


    return 0;
}
