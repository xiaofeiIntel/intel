//
// Created by Tengfei on 18-6-28.
//
#include"rehash.h"

/*value中list初始化*/
list* listInit(int size,int nodeNum)
{
    list* linkList;
    listNode* head,*temp,*node;
    linkList=(list*)malloc(sizeof(list));
    head=node=(listNode*)malloc(sizeof(listNode));
    node->value=(int*)malloc(sizeof(int));
    node->value=0;
//    printf("the dictEntry number is %d\n",nodeNum);
    for(int i=1;i<size;i++)
    {
        temp=(listNode*)malloc(sizeof(listNode));
        temp->value=(int*)malloc(sizeof(int));
        (temp->value)=i;
//        printf(" the listnode is %d\n",temp->value);
        (temp->nodeNum)=nodeNum;
        temp->pre=node;
        node->next=temp;
        node=node->next;

    }
    node->next=NULL;
    linkList->head=head;
    linkList->tail=node;
    linkList->len=size;
    return linkList;
}
void moveLinkList(struct dictEntry **table,struct dictEntry* table0)
{
    dictEntry* head,*node1,*node2;

    dictEntry  *temp1=(dictEntry*)malloc (sizeof(dictEntry));
    temp1->key=(char*)malloc(CHAR_SIZE*sizeof(char));
    strcpy (temp1->key,table0->key);
    /*当value数据是list时*/
        /*为linklist头节点赋值*/
    temp1->value.linkList=(list*)malloc(sizeof(list));
    temp1->value.linkList->len=table0->value.linkList->len;
        temp1->value.linkList->head=(listNode*)malloc(sizeof(listNode));
        temp1->value.linkList->head->pre=NULL;
        temp1->value.linkList->head->value=table0->value.linkList->head->value;
        listNode *listNode1=temp1->value.linkList->head,*listNode0=table0->value.linkList->head->next;
        for(int k=1;k<table0->value.linkList->len;k++)
        {
            listNode* tempList=(listNode*)malloc(sizeof(listNode));
            tempList->value=(int*)malloc(sizeof(int));
            (tempList->value)=listNode0->value;
            tempList->nodeNum=listNode0->nodeNum;
            tempList->pre=listNode1;
            listNode1->next=tempList;
            listNode1=listNode1->next;
            listNode0=listNode0->next;
        }
        listNode1->next=NULL;
    *table = temp1;
    temp1->value.linkList->tail=listNode1;
    (*table)->value.linkList->head=temp1->value.linkList->head;
    (*table)->value.linkList->len=temp1->value.linkList->len;
    (*table)->value.linkList->tail=temp1->value.linkList->tail;
}

void htInit(struct dictht *ht,int type,int size,int threshold)
{
    if(size!=2)
        return;
    dictEntry ** ptr1=(dictEntry*)malloc(DATA_SIZE*sizeof(struct dictEntry*));
    dictEntry ** ptr2=(dictEntry*)malloc(DATA_SIZE*sizeof(struct dictEntry*));
//    dictEntry ** ptr1=(dictEntry**)malloc(DATA_SIZE*sizeof(struct dictEntry*));
//    dictEntry ** ptr2=(dictEntry**)malloc(DATA_SIZE*sizeof(struct dictEntry*));
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
            dictEntry* temp=(dictEntry*)malloc(sizeof(dictEntry));
            temp->key=(char*)malloc(CHAR_SIZE*sizeof(char));
            temp->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
            sprintf(temp->key,"%d",i+j);
            if(type==STRING)
            sprintf(temp->value.val,"%d",i+j);
            else if(type==LIST)
            {
               temp->value.linkList=listInit(LINK_LEN,i);
            }
            node->next=temp;
            node=node->next;
        }
        ht[0].table[i]=head;
    }
}

void moveFun(struct dictht *ht,int size)
{
    for(int i=0;i<DATA_SIZE;i++)
    {


        /*当value数据为string时*/
        if(ht[0].table[i]->dataTypeFlag==STRING)
        {
            dictEntry* head,*node1,*node2;

            dictEntry  *temp1=(dictEntry*)malloc (sizeof(dictEntry));
            temp1->key=(char*)malloc(CHAR_SIZE*sizeof(char));
            strcpy (temp1->key,ht[0].table[i]->key);
            temp1->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
            strcpy(temp1->value.val, ht[0].table[i]->value.val);
//        temp1->key=ht[0].table[i]->key;
//        temp1->value.val=ht[0].table[i]->value.val;
            ht[1].table[i] = temp1;
            head = node1 = ht[1].table[i];
            node2 = ht[0].table[i]->next;
            for (int j = 1; j < LINK_LEN; j++) {
                dictEntry *temp2 = (dictEntry *) malloc(sizeof(dictEntry));
                temp2->key = (char *) malloc(CHAR_SIZE * sizeof(char));
                temp2->value.val = (char *) malloc(CHAR_SIZE * sizeof(char));
                strcpy(temp2->key, node2->key);
                strcpy(temp2->value.val, node2->value.val);
                strcat(temp2->key, "ht2Link");
                node1->next = temp2;
                node1 = node1->next;
                node2 = node2->next;
            }
        }

        /*当value数据是list时*/
        if(ht[0].table[i]->dataTypeFlag==LIST)
        {
           moveLinkList(&(ht[1].table[i]),ht[0].table[i]);
            listNode* printTemp=ht[1].table[i]->value.linkList->head;
            for(int j=0;j<ht[1].table[i]->value.linkList->len;j++)
            {
                printf("ht[1].table[i].value.linklist is %d\n",printTemp->value);
                printTemp=printTemp->next;
            }
            /*为linklist头节点赋值*/
//            temp1->value.linkList=(list*)malloc(sizeof(list));
//            temp1->value.linkList->len=ht[0].table[i]->value.linkList->len;
//            temp1->value.linkList->head=(listNode*)malloc(sizeof(listNode));
//            temp1->value.linkList->head->pre=NULL;
//            temp1->value.linkList->head->value=ht[0].table[0]->value.linkList->head->value;
////            temp1->value.linkList->head=ht[0].table[i]->value.linkList->head;
//            listNode *listNode1=temp1->value.linkList->head,*listNode0=ht[0].table[i]->value.linkList->head->next;
//            for(int k=1;k<ht[0].table[i]->value.linkList->len;k++)
////            while(listNode0!=ht[0].table[i]->value.linkList->tail)
//            {
//                listNode* tempList=(listNode*)malloc(sizeof(listNode));
//                tempList->value=(int*)malloc(sizeof(int));
//                (tempList->value)=listNode0->value;
//                tempList->nodeNum=listNode0->nodeNum;
//                tempList->pre=listNode1;
//                listNode1->next=tempList;
//                listNode1=listNode1->next;
//                listNode0=listNode0->next;
//            }
//            listNode1->next=NULL;

//            /*这里将temp的list的部分*/
//            ht[1].table[i] = temp1;
//            ht[1].table[i]->value.linkList->head=temp1->value.linkList->head;
//            ht[1].table[i]->value.linkList->len=temp1->value.linkList->len;
//            ht[1].table[i]->value.linkList->tail=temp1->value.linkList->tail;

            dictEntry* head,*node1,*node2;
            head = node1 = ht[1].table[i];
            node1=node1->next;
            node2 = ht[0].table[i]->next;
            for (int j = 1; j < LINK_LEN; j++) {
                dictEntry *temp2 = (dictEntry *) malloc(sizeof(dictEntry));
                temp2->key = (char *) malloc(CHAR_SIZE * sizeof(char));
               // temp2->value.val = (char *) malloc(CHAR_SIZE * sizeof(char));
                strcpy(temp2->key, node2->key);
                strcat(temp2->key, "ht2Link");
                moveLinkList(&node1,node2);
//                node1->next = temp2;
//                node1->value.linkList->head=temp2->value.linkList->head;
//                node1->value.linkList->len=temp2->value.linkList->len;
//                node1->value.linkList->tail=temp2->value.linkList->tail;
                node1 = node1->next;
                node2 = node2->next;
            }
        }
        strcat(ht[1].table[i]->key,"ht2");
    }
}

void freeHt(struct dictht* ht,int len)
{
    for(int i=0;i<len;i++)
    {
        free(ht[0].table[i]->key);
        ht[0].table[i]->key=NULL;
        free(ht[0].table[i]->value.val);
        ht[0].table[i]->value.val=NULL;
        free(ht[0].table[i]);
        ht[0].table[i]=NULL;
    }

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
        if(i%100==0)
        { printf("\n");
            dictEntry* temp=ht[size].table[i];
            while(temp)
            {
                if(type==STRING)
                printf("key is %s,value is %s\n",temp->key,temp->value.val);
                else if(type==LIST)
                {
                    listNode* node=temp->value.linkList->head;
                    for(int j=0;j<temp->value.linkList->len;j++)
                    {
                        printf("the number of list node is %d\n",(int)(node->value));
                        node=node->next;
                    }
                }
                temp=temp->next;
            }
        }
    }
}