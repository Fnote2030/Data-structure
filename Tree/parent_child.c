/*
    线索二叉树
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<malloc.h>

typedef char ElemType;

//Link 表示指向左右孩子
//Thread 表示指向前驱和后继节点的线索
typedef enum
{
    Link,
    Thread
} TagType;

typedef struct BTnode
{
    ElemType data;
    struct BTnode *lchild;  //指向右孩子/后继
    struct BTnode *rchild;  //指向左孩子/前驱
    TagType ltag;
    TagType rtag;
}BTNode,*PBTNode;

//全局变量指向刚刚访问过的节点
PBTNode pre = NULL;

//函数的声明
void CreateBTree(PBTNode *pt);    //创建二叉树
void InThreading(PBTNode pt);    //中序遍历线索化
void InOrderThreading(PBTNode *p, PBTNode pt);
void InOrderTraverse(PBTNode p);

int main()
{
    PBTNode pt = NULL;
    PBTNode p = NULL; //指向根节点的节点
    CreateBTree(&pt);
    InOrderThreading(&p, pt);
    InOrderTraverse(p);
    return 0;
}


//函数的定义
void CreateBTree(PBTNode *pt)
{
    ElemType c;
    scanf("%c", &c);
    if(' ' == c)
    {
        *pt = NULL;   //该节点不存在
    }
    else
    {
        *pt = (PBTNode)malloc(sizeof(BTNode));
        assert((*pt));
        (*pt)->data = c;
        (*pt)->ltag = Link;  
        (*pt)->rtag = Link;  //假设有左右子树

        CreateBTree(&(*pt)->lchild);
        CreateBTree(&(*pt)->rchild);
    }
}

//中序遍历线索化
void InThreading(PBTNode pt)
{
    if(pt)
    {
        InThreading(pt->lchild);
        //处理  上一个节点能否和当前节点互为前驱后继的关系
        if(!pt->lchild)
        {
            pt->ltag = Thread;  
            pt->lchild = pre;   //指向前驱
        }
        if(!pre->rchild)
        {
            pre->rtag = Thread;
            pre->rchild = pt;
        }
        pre = pt;  //记录刚才访问的节点

        InThreading(pt->rchild);
    }
}   


void InOrderThreading(PBTNode *p,PBTNode pt)
{
    *p = (PBTNode)malloc(sizeof(BTNode));
    assert((*p));
    (*p)->ltag = Link;  //左孩子
    (*p)->rtag = Thread; //后继
    (*p)->rchild = *p;
    if(!pt)
    {
        (*p)->lchild = pt;
        (*p)->ltag = Thread;
    }
    else
    {
        (*p)->lchild = pt;
        pre = *p;
        InThreading(pt);  //遍历线索

        pre->rchild = *p;  //指向前置节点
        pre->rtag = Thread; //后继
        (*p)->rchild = pre;  //前置节点的后继为最后一个节点
    }
}

void visit(ElemType c)
{
    printf("%c", c);
}

void InOrderTraverse(PBTNode p)
{
    PBTNode t = p->lchild;
    while(t != p)
    {
        //访问最底下的左子树
        while(t->ltag==Link)
        {
            t = t->lchild;
        }
        visit(t->data);  
        //往回访问左子树
        while (t->rtag == Thread && t->rchild!=p)
        {
            t = t->rchild;
            visit(t->data);
        }
        //去到右子树(作为双亲节点)
        t = t->rchild;  
    }
    printf("\n");
}