//
// Created by Tengfei on 18-6-28.
//
#include"rehash.h"

#include <pthread.h>
#include <sys/time.h>


 long count=0;
 long cnt[2]={0,0};
 pthread_mutex_t mutex;
float Timeuse=0;
/*value中list初始化*/
list* listInit(int size,int nodeNum)
{
    list* linkList;
    listNode* head,*temp0,*node;
    linkList=(list*)malloc(sizeof(list));
    head=node=(listNode*)malloc(sizeof(listNode));
    node->value=(int*)malloc(sizeof(int));
    node->value=0;
//    printf("the dictEntry number is %d\n",nodeNum);
    for(int i=1;i<size;i++)
    {
        temp0=(listNode*)malloc(sizeof(listNode));
        temp0->value=(int*)malloc(sizeof(int));
        (temp0->value)=i;
//        printf(" the listnode is %d\n",temp0->value);
        (temp0->nodeNum)=nodeNum;
        temp0->pre=node;
        node->next=temp0;
        node=node->next;

    }
    node->next=NULL;
    linkList->head=head;
    linkList->tail=node;
    linkList->len=size;
    return linkList;
}


void htInit(struct dictht *ht,int type,int size,int threshold)
{
    /*初始化锁*/
    pthread_mutex_init(&mutex,NULL);

    if(size!=2)
        return;
    dictEntry ** ptr1=(dictEntry*)malloc(DATA_SIZE*sizeof(struct dictEntry*));
    dictEntry ** ptr2=(dictEntry*)malloc(DATA_SIZE*sizeof(struct dictEntry*));
    ht[0].table=ptr1;
    ht[1].table=ptr2;

    for(int i=0;i<DATA_SIZE;i++)
    {
        dictEntry* head;
        dictEntry* node;
        head=node=(dictEntry*)malloc(sizeof(dictEntry));
        head->key=(char*)malloc(CHAR_SIZE*sizeof(char));
        sprintf(head->key,"%d",i);
        head->dataTypeFlag=type;
        if(type==STRING)
        {
            head->value.val = (char *) malloc(CHAR_SIZE * sizeof(char));
            sprintf(head->value.val, "%d", i);
        }
            //初始化头节点的list
        else if(type==LIST)
        {
            head->value.linkList=listInit(LINK_LEN,i);
        }
        for(int j=1;j<LINK_LEN;j++)
        {
            dictEntry* temp0=(dictEntry*)malloc(sizeof(dictEntry));
            temp0->key=(char*)malloc(CHAR_SIZE*sizeof(char));
            temp0->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
            sprintf(temp0->key,"%d",i+j);
            if(type==STRING)
            sprintf(temp0->value.val,"%d",i+j);
            else if(type==LIST)
            {
               temp0->value.linkList=listInit(LINK_LEN,i);
            }
            node->next=temp0;
            node=node->next;
        }
        ht[0].table[i]=head;
    }
}

void moveLinkList(struct dictEntry **table,struct dictEntry* table0)
{
    dictEntry* head,*node1,*node2;

    dictEntry  *temp01=(dictEntry*)malloc (sizeof(dictEntry));
    temp01->key=(char*)malloc(CHAR_SIZE*sizeof(char));
    strcpy (temp01->key,table0->key);
    /*当value数据是list时*/
    /*为linklist头节点赋值*/
    temp01->value.linkList=(list*)malloc(sizeof(list));
    temp01->value.linkList->len=table0->value.linkList->len;
    temp01->value.linkList->head=(listNode*)malloc(sizeof(listNode));
    temp01->value.linkList->head->pre=NULL;
    temp01->value.linkList->head->value=table0->value.linkList->head->value;
    listNode *listNode1=temp01->value.linkList->head,*listNode0=table0->value.linkList->head->next;
    for(int k=1;k<table0->value.linkList->len;k++)
    {
        listNode* temp0List=(listNode*)malloc(sizeof(listNode));
        temp0List->value=(int*)malloc(sizeof(int));
        (temp0List->value)=listNode0->value;
        temp0List->nodeNum=listNode0->nodeNum;
        temp0List->pre=listNode1;
        listNode1->next=temp0List;
        listNode1=listNode1->next;
        listNode0=listNode0->next;
    }
    listNode1->next=NULL;
    *table = temp01;
    temp01->value.linkList->tail=listNode1;
    (*table)->value.linkList->head=temp01->value.linkList->head;
    (*table)->value.linkList->len=temp01->value.linkList->len;
    (*table)->value.linkList->tail=temp01->value.linkList->tail;
}

void moveString(struct dictEntry **dest,struct dictEntry*src) {


    dictEntry *head, *node1, *node2;
    dictEntry *temp01 = (dictEntry *) malloc(sizeof(dictEntry));
    temp01->key = (char *) malloc(CHAR_SIZE * sizeof(char));
    /*加锁*/
#ifdef USEMUTEX
     pthread_mutex_lock(&mutex);
#endif
    dumpRdb(src,PATH);
    strcpy(temp01->key, src->key);
    temp01->value.val = (char *) malloc(CHAR_SIZE * sizeof(char));
    strcpy(temp01->value.val, src->value.val);
    ++count;
    /*开锁*/

#ifdef USEMUTEX
    pthread_mutex_unlock(&mutex);
#endif

#ifdef NOCOMP
    pthread_mutex_lock(&mutex);
    cnt[0]++;
    pthread_mutex_unlock(&mutex);
#endif
    *dest = temp01;
    head = node1 = *dest;
    node2 = src->next;
    for (int j = 1; j < LINK_LEN; j++) {
        dictEntry *temp02 = (dictEntry *) malloc(sizeof(dictEntry));
        temp02->key = (char *) malloc(CHAR_SIZE * sizeof(char));
        temp02->value.val = (char *) malloc(CHAR_SIZE * sizeof(char));
        /*加锁并dump*/
#ifdef USEMUTEX
        pthread_mutex_lock(&mutex);
#endif
        dumpRdb(node2,PATH);
        strcpy(temp02->key, node2->key);
        strcpy(temp02->value.val, node2->value.val);
        ++count;

#ifdef USEMUTEX
        pthread_mutex_unlock(&mutex);
#endif
#ifdef NOCOMP
        pthread_mutex_lock(&mutex);
        cnt[0]++;
        pthread_mutex_unlock(&mutex);
#endif
        strcat(temp02->key, "ht2Link");
        node1->next = temp02;
        node1 = node1->next;
        node2 = node2->next;
    }
}


/*这里的迁移函数里是先进行dump到二进制文件后再进行复制到ht[1]中*/
void moveFun(struct dictht *ht,int size)
{
    /*打开文件，进行数据添加*/
    fid=fopen(PATH,"ab");
    DataWrite("redisDump",PATH);
    gettimeofday(&startTime,NULL);
    for(int i=0;i<DATA_SIZE;i++)
    {

        /*当value数据为string时*/
        if(ht[0].table[i]->dataTypeFlag==STRING)
        {
            moveString(&(ht[1].table[i]),ht[0].table[i]);

        }

        /*当value数据是list时*/
       else if(ht[0].table[i]->dataTypeFlag==LIST)
        {
           moveLinkList(&(ht[1].table[i]),ht[0].table[i]);
            listNode* printtemp0=ht[1].table[i]->value.linkList->head;
            for(int j=0;j<ht[1].table[i]->value.linkList->len;j++)
            {
                printf("ht[1].table[i].value.linklist is %d\n",printtemp0->value);
                printtemp0=printtemp0->next;
            }

            dictEntry* head,*node1,*node2;
            head = node1 = ht[1].table[i];
            node1=node1->next;
            node2 = ht[0].table[i]->next;
            for (int j = 1; j < LINK_LEN; j++) {
                dictEntry *temp02 = (dictEntry *) malloc(sizeof(dictEntry));
                temp02->key = (char *) malloc(CHAR_SIZE * sizeof(char));
                strcpy(temp02->key, node2->key);
                strcat(temp02->key, "ht2Link");
                moveLinkList(&node1,node2);

                node1 = node1->next;
                node2 = node2->next;
            }
        }
        strcat(ht[1].table[i]->key,"ht2");
    }
    gettimeofday(&endTime,NULL);

    Timeuse = 1000000*(endTime.tv_sec - startTime.tv_sec) + (endTime.tv_usec - startTime.tv_usec);

    Timeuse /= 1000000;
    printf("lock count is %d and used time is %f \n",count,Timeuse);
    fclose(fid);
}

void freeHt(struct dictht* ht)
{
    dictEntry* temp01, *head1,*temp02,*head2;

    for(int i=0;i<DATA_SIZE;i++)
    {
        free(ht[0].table[i]->key);
        free(ht[1].table[i]->key);
        ht[0].table[i]->key=NULL;
        head1=ht[0].table[i];
        head2=ht[1].table[i];
        while(head1!=NULL&&head2!=NULL)
        {
            temp01=head1;
            temp02=head2;
            head1=head1->next;
            head2=head2->next;
            free(temp01->value.val);
            temp01->value.val=NULL;
            free(temp01);
            free(temp02->value.val);
            temp02->value.val=NULL;
            free(temp02);
        }
//        free(ht[0].table[i]->value.val);
//        ht[0].table[i]->value.val=NULL;
//        free(ht[0].table[i]);
//        ht[0].table[i]=NULL;
    }
    printf("free success!\n");
}


void output(struct dictht* ht,int size,int type)
{
    if(ht[0].table[0]==NULL)
    {
        printf("hash table has free!");
        return;
    }

    for(int i=0;i<DATA_SIZE;i++)
    {
        if(i%10==0)
        { printf("\n");
            dictEntry* temp0=ht[size].table[i];
            while(temp0)
            {
                if(type==STRING)
                printf("key is %s,value is %s\n",temp0->key,temp0->value.val);
                else if(type==LIST)
                {
                    listNode* node=temp0->value.linkList->head;
                    for(int j=0;j<temp0->value.linkList->len;j++)
                    {
                        printf("the number of list node is %d\n",(int)(node->value));
                        node=node->next;
                    }
                }
                temp0=temp0->next;
            }
        }
    }
}
void printMultiThread(struct dictht* ht,int type)
{
    if(ht[0].table[0]==NULL)
    {
        printf("hash table has free!");
        return;
    }

    for(int i=0;i<DATA_SIZE;i+=10)
    {
            printf("\n");
            dictEntry* temp0=ht[0].table[i];
            dictEntry* temp1=ht[1].table[i];
        printf("table[%d] ht[0] value %s and ht[1] value %s\n",i,temp0->value.val,temp1->value.val);
            temp0=temp0->next;
            temp1=temp1->next;
        printf("table[%d] ht[0] value %s and ht[1] value %s\n",i,temp0->value.val,temp1->value.val);
    }
}

void DataWrite(const char* data,const char* path)
{

    if(fid==NULL)
    {
        printf("write error!");
        return;
    }
    int len=0;
    while(*(data+len)!='\0')
        len++;
    fwrite(data,sizeof(char),CHAR_SIZE,fid);
}


void DataRead(const char* path)
{
    printf("begining read!\n");
    FILE *fid;
//    fid = fopen("/home/sean/San/project/RWBinary/test_write.rdb","rb");
    fid = fopen(path,"rb");
    if(fid == NULL)
    {
        printf("读取文件出错");
        return;
    }
    //获取文件大小
    fseek (fid , 0 , SEEK_END);
    long lSize = ftell (fid);
    rewind (fid);
    //开辟存储空间
    int num = lSize/sizeof(char);
    char *pos = (char*) malloc (sizeof(char)*num);
    if (pos == NULL)
    {
        printf("开辟空间出错");
        return;
    }
    fread(pos,sizeof(char),num,fid);
    for(int i = 0; i < num; i++)
        printf("%c", pos[i]);
    printf("\n");
    free(pos);     //释放内存
    fclose(fid);
}


void dumpRdb(const dictEntry* src,const char* path)
{
    DataWrite(src->key,path);
    DataWrite(src->value.val,path);
}

void changeData()
{

}