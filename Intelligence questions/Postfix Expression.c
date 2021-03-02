/*
    中缀表达式转后缀表达式
*/

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<stdbool.h>



typedef struct Node
{
    int data;
    struct Node *pNext;
} NODE, *PNODE;


typedef struct Stack
{
    PNODE pTop;      //永远指向栈顶元素
    PNODE pBottom;  //栈底元素下一个没有实际含义的元素
} STACK, *PSTACK;


//函数的声明
void initStack(PSTACK ps);
bool pushStack(PSTACK ps, int val);  //压栈
void traverseStack(PSTACK ps);     //遍历输出
bool pop(PSTACK ps, int *val);              //出栈一次，成功返回true，失败返回false

bool is_empty(PSTACK ps);
void clear(PSTACK ps);



//主函数
int main()
{
    STACK s;
    char c;
    int val = 0;
    initStack(&s);
    printf("请输入中缀表达式：");
    scanf("%c", &c);
    //
    while(c != '#')
    {
        while(c>='0' && c<='9')
        {
            printf("%c", c);
            scanf("%c", &c);
            if(c<'0' || c>'9')
            {
                printf(" ");
            }
        }

        if(is_empty(&s)) //栈空的
        {
            pushStack(&s, c);
        }
        else if(')' == c ) 
        {
            //输出左右括弧里面的运算符，并把左括弧出栈
            pop(&s, &val);
            while ('(' != val && !is_empty(&s))
            {
                printf("%c ", val);
                pop(&s, &val);
            }
        }
        else if('+'==c || '-'==c)
        {
            //优先级不大于前面的运算符
            do
            {
                pop(&s, &val);
                if ('('==val)
                {
                    pushStack(&s, val);
                }
                else
                {
                    printf("%c ", val);
                }
            } while ('('!=val && !is_empty(&s));
            //输出前面优先级大于等于刚接收的运算符
            pushStack(&s, c);
        }
        else if('('==c || '/'==c || '*'==c)
        {
            pushStack(&s, c);

        }
        else if('#'==c)
        {
            break;
        }
        else
        {
            printf("\n输入格式错误！\n");
            break;
        }
        scanf("%c", &c);
    }
    while(pop(&s,&val))
    {
        printf("%c ", val);
    }

    // pop(&s, &val);
    // printf("%c ", val);
    // pop(&s, &val);
    // printf("%c ", val);

    return 0;
}




//函数的定义
void initStack(PSTACK ps)
{
    PNODE p = (PNODE)malloc(sizeof(NODE));
    if (NULL == p)
    {
        printf("分配空间失败！\n");
        exit(-1);
    }
    //printf("初始化成功！\n");
    p->pNext = NULL;
    ps->pBottom = p;
    ps->pTop = p; 

    
}

bool pushStack(PSTACK ps, int val)
{
    PNODE pNew = (PNODE)malloc(sizeof(NODE));
    if (NULL == pNew)
    {
        printf("分配空间失败！\n");
        return false;
    }
    pNew->data = val;
    pNew->pNext = ps->pTop;  //加在栈顶上面
    ps->pTop = pNew;        //栈顶为新节点
    //printf("压栈成功！\n");
    return true;
}


void traverseStack(PSTACK ps)
{
    if(is_empty(ps))
    {
        printf("栈为空！\n");
        return;
    }
    PNODE p = ps->pTop;   //从栈顶开始
    while(p!=ps->pBottom)    
    {
        printf("%d ", p->data);
        p = p->pNext;  //往下
    }
    printf("\n");
}

bool is_empty(PSTACK ps)
{
    if(ps->pBottom == ps->pTop)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool pop(PSTACK ps, int *val)
{
    if(is_empty(ps))
    {
        return false;
    }
    else
    {
        PNODE p = ps->pTop;  //栈顶
        *val =p->data;
        ps->pTop =p->pNext;  //新栈顶
        free(p);
        p = NULL;
        return true;
    }
}


void clear(PSTACK ps)
{
    if(is_empty(ps))
    {
        return;
    }
    else
    {
        PNODE p = ps->pTop;  //中转新的栈顶
        while(ps->pTop != ps->pBottom)
        { 
            p = p->pNext;  //暂存新的栈顶
            free(ps->pTop); //释放原栈顶
            ps->pTop = p;
        }
        //ps->pTop = ps->pBottom;
    }

}