//
// Created by sean on 18-6-28.
//

#include"rehash.h"


void htInit(struct dictht *ht,int size)
{
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
        head->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
        sprintf(head->key,"%d",i);
        sprintf(head->value.val,"%d",i);
        for(int j=1;j<LINK_LEN;j++)
        {
            dictEntry* temp=(dictEntry*)malloc(sizeof(dictEntry));
            temp->key=(char*)malloc(CHAR_SIZE*sizeof(char));
            temp->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
            sprintf(temp->key,"%d",i+j);
            sprintf(temp->value.val,"%d",i+j);
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
        dictEntry* head,*node1,*node2;

        dictEntry  *temp1=(dictEntry*)malloc (sizeof(dictEntry));
        temp1->key=(char*)malloc(CHAR_SIZE*sizeof(char));
        temp1->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
        strcpy (temp1->key,ht[0].table[i]->key);
        strcpy(temp1->value.val,ht[0].table[i]->value.val);
//        temp1->key=ht[0].table[i]->key;
//        temp1->value.val=ht[0].table[i]->value.val;
        ht[1].table[i]=temp1;
        head=node1=ht[1].table[i];
        node2=ht[0].table[i]->next;
        for(int j=1;j<LINK_LEN;j++)
        {
            dictEntry* temp2=(dictEntry*)malloc(sizeof(dictEntry));
            temp2->key=(char*)malloc(CHAR_SIZE*sizeof(char));
            temp2->value.val=(char*)malloc(CHAR_SIZE*sizeof(char));
            strcpy(temp2->key,node2->key);
            strcpy(temp2->value.val,node2->value.val);
            strcat(temp2->key,"ht2Link");
            node1->next=temp2;
            node1=node1->next;
            node2=node2->next;
        }
//
        // printf("ht[%d] is ",i);
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


void output(struct dictht* ht,int size)
{
    if(ht[0].table[0]==NULL)
    {
        printf("hash table has free!");
        return;
    }

    for(int i=0;i<DATA_SIZE;i++)
    {
        if(i%1000==0)
        { printf("\n");
            dictEntry* temp=ht[size].table[i];
            while(temp)
            {
                printf("key is %s,value is %s\n",temp->key,temp->value.val);
                temp=temp->next;
            }
        }
    }
}