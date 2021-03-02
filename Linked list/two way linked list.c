#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>
#include<assert.h>

typedef int DataType;


typedef struct ListNode
{
    struct ListNode *next;
    struct ListNode *prior;
    DataType data;
}ListNode,*PListNode;



//函数的声明
void ListInit(PListNode *phead);
void ListDestory(PListNode *phead);   //销毁
void ListClear(PListNode phead);   //清除其他节点，留下头节点

void Listpushback(PListNode phead, DataType val);
void Listpopback(PListNode phead, DataType *val);
void Listpushfront(PListNode phead, DataType val);
void Listpopfront(PListNode phead, DataType *val);

void ListPrint(PListNode phead);
PListNode BuyListNode(DataType val);  //创建一个新的节点，赋值为val
PListNode ListFind(PListNode phead, DataType val); //找到val的地址
void ListInsert(PListNode pos, DataType val); //在Pos的前面插入val
void ListErase(PListNode pos, DataType *val); //删除pos位置上的节点，并记录删除节点的数据





void test1()
{
    PListNode phead = NULL;
    ListInit(&phead);  //初始化
    int i = 0;

    for (i = 0; i < 10; i++)
    {
        Listpushback(phead,i);
    }
    ListPrint(phead);

    for (i = 0; i < 10; i++)
    {
        Listpushfront(phead,i);
    }
    ListPrint(phead);  
}


void test2()
{
    PListNode phead = NULL;
    int val = 0;
    ListInit(&phead);  //初始化
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        Listpushback(phead,i);
    }
    ListPrint(phead);

    PListNode pos = ListFind(phead, 5);
    if(pos)
    {
        ListInsert(pos, 66);
    }
    ListPrint(phead);

    ListErase(pos, &val);
    ListPrint(phead);
    printf("%d\n", val);
}
void test3()
{
    PListNode phead = NULL;
    ListInit(&phead);  //初始化
    int i = 0;
    for (i = 0; i < 10; i++)
    {
        Listpushback(phead,i);
    }
    ListPrint(phead);

    ListDestory(&phead);  //头节点也删除
    //ListClear(phead);
    for (i = 0; i < 10; i++)
    {
        Listpushback(phead,i);
    }
    ListPrint(phead);
}

int main()
{
    test1();
    return 0;
}



//函数的定义

//尾插节点
void Listpushback(PListNode phead,DataType val)
{
    assert(phead);
    PListNode tail = phead->prior;
    PListNode newnode = BuyListNode(val); //创建的新的节点，赋值val
    //连接
    tail->next = newnode;
    newnode->prior = tail;
    newnode->next = phead;
    phead->prior = newnode;
}


//创建一个新的节点
PListNode BuyListNode(DataType val)
{
    PListNode newnode = (PListNode)malloc(sizeof(ListNode));
    newnode->data = val;
    newnode->prior = newnode->next = NULL;
    return newnode;
}


//链表打印
void ListPrint(PListNode phead)
{
    assert(phead);
    PListNode cur = phead->next;
    while(cur != phead)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}


//创建头节点，不放有效值
void ListInit(PListNode *phead)
{
    *phead = BuyListNode(0); //创建一个新的节点
    (*phead)->prior = *phead;
    (*phead)->next = *phead;
}


//从尾部删除节点
void Listpopback(PListNode phead, DataType *val)
{
    assert(phead);
    assert(phead->next != phead);
    PListNode tail = phead->prior; //要删除的节点
    PListNode tailprior = tail->prior; //要删除的节点的前一个节点
    *val = tail->data;

    tailprior->next = phead;
    phead->prior = tailprior;
    free(tail);
    tail = NULL;
}



void Listpushfront(PListNode phead, DataType val)
{
    assert(phead);
    //assert(phead->next != phead);
    PListNode first = phead->next;
    PListNode newnode = BuyListNode(val);

    phead->next = newnode;
    newnode->prior = phead;
    newnode->next = first;
    first->prior = newnode;
}



void Listpopfront(PListNode phead, DataType *val)
{
    assert(phead);
    assert(phead->next != phead);
    PListNode first = phead->next;
    PListNode second = first->next;

    phead->next = second;
    second->prior = phead;
    *val = first->data;
    free(first);
    first = NULL;
}


PListNode ListFind(PListNode phead, DataType val)
{
    assert(phead);
    PListNode cur = (PListNode)malloc(sizeof(ListNode));
    cur = phead->next;
    while(cur)
    {
        if(cur->data == val)
        {
            return cur; //返回val的地址
        }
        cur = cur->next;
    }
    return NULL;  //没有找到，返回NULL
}


void ListInsert(PListNode pos, DataType val)
{
    assert(pos);
    PListNode prior = pos->prior;
    PListNode newnode = BuyListNode(val);
    prior->next = newnode;
    newnode->prior = prior;
    newnode->next = pos;
    pos->prior = newnode;
}

//删除pos位置上的节点，并记录删除节点的数据
void ListErase(PListNode pos, DataType *val)
{
    assert(pos);
    assert(pos->next != pos);
    PListNode prior = pos->prior;
    PListNode next = pos->next;
    *val = pos->data;
    free(pos);
    pos->next = NULL;
    pos->prior = NULL;
    prior->next = next;
    next->prior = prior;
}


void ListDestory(PListNode *phead)
{
    assert(*phead);
    ListClear(*phead);
    free(*phead);
    *phead = NULL;
}

//清除其他节点，留下头节点
void ListClear(PListNode phead)
{
    assert(phead);
    PListNode cur = phead->next;
    while(cur != phead)
    {
        PListNode next = cur->next;
        free(cur);
        cur = next;
    }
    phead->next = phead;
    phead->prior = phead;
}   
