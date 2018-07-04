
#include "rehash.h"


int main() {

    dictht ht[2];
    htInit(ht,LIST,2,1000);
//    output(ht,0);
    moveFun(ht,2);
//    freeHt(ht,DATA_SIZE);
        output(ht,0,LIST);


    return 0;
}
