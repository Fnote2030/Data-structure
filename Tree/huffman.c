#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>
#include<string.h>

/*
    哈夫曼编码
    
    编码生成：哈夫曼树 + 编码
    反编码需要：哈夫曼树 + 编码
*/
#define MAX_SIZE 256


//哈夫曼树的节点
typedef struct htNode   
{
    char symbol;
    struct htNode *left;
    struct htNode *right;
} HTNode,*PHTNode;

//哈夫曼树的根节点
typedef struct HTree
{
    HTNode *root;
} HTree,*PHTree;

//队列节点
typedef struct QueueNode
{
    HTNode *val;        //节点的数据
    unsigned int priorty;   //优先级
    struct QueueNode *next; //指向队列的下一个节点
} *PQueueNode,QueueNode;
//哈夫曼树的队列
typedef struct PQueue
{
    unsigned int size;  //队列的长度
    QueueNode *first;  //指向队列的头节点
}*PQueue,Queue;


//
typedef struct TableNode
{
    char symbol;   //字符
    char *code;    //字符的编码
    struct TableNode *next;
} TableNode;

//haffuman编码表
typedef struct HTable
{
    TableNode *first;//   
    TableNode *last;
} *PHTable,HTable;


//函数的声明
PHTNode BuildTree(char *inputString);
void InitPQueue(PQueue *huffmanqueue);
void AddPQueue(PQueue huffmanqueue, PHTNode newnode, int weight);
PHTNode GetHTNode(PQueue huffmanqueue);//从队列中获取第一个节点的数据（树的节点指针）
PHTable BuildTable(PHTNode codeTree);  //返回根节点指针
void encode(PHTable table, char *str); //编码
void decode(PHTNode Tree, char *code);  //反编码




//主函数
int main()
{


    char *str = "afsdfafdsa";
    PHTNode codeTree = BuildTree(str);  //创建str字符串的haffman树
    
    PHTable codeTable = BuildTable(codeTree); //codeTree树对应的编码表
    encode(codeTable, str);


    FILE *file = fopen("text.txt", "r");
    assert(file);
    char scode[256];
    char code;
    int i = 0;
    while(fread(&code,1,1,file) >= 1) //返回实际读取的元素
    {
        scode[i] = code;
        i++;
    }
    //fgets(scode, 256, file);
    fclose(file);
    decode(codeTree, scode);
    return 0;
}




//函数的定义
PHTNode BuildTree(char *inputString)
{
    int nums[256] = {0}; //存放权重
    int i = 0;
    //统计字符串中每个字符出现的次数，权重，nums下标为字符的ascii
    for (i = 0; inputString[i] != '\0'; i++)
    {
        nums[(int)inputString[i]]++;
    }

    //创建一个队列存储出现过的字符
    PQueue huffmanqueue;
    InitPQueue(&huffmanqueue);//初始化
    //填充队列
    for (i = 0; i < 256; i++)
    {
        //出现过的字符压进队列
        if(nums[i] != 0) 
        {
            //创建一个树的节点
            PHTNode newnode = (PHTNode)malloc(sizeof(HTNode));
            assert(newnode);
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->symbol = i;   //字符
            //按照权重升序在队列中排序
            AddPQueue(huffmanqueue, newnode, nums[i]);  //字符（树的节点）和字符的权重（出现的次数）
        }
    }
    //生成huffman树
    while(huffmanqueue->size > 1)
    {   
        //两个最小权重的相加
        int priority = huffmanqueue->first->priorty;
        priority += huffmanqueue->first->next->priorty;
        PHTNode newnode = (PHTNode)malloc(sizeof(HTNode));
        newnode->left = GetHTNode(huffmanqueue);  //权重最小
        newnode->right = GetHTNode(huffmanqueue); //权重次小
        AddPQueue(huffmanqueue, newnode, priority); //重新进队，按照权重升序存储
    }
    //队列还剩一个根节点
    PHTNode root = (PHTNode)malloc(sizeof(HTNode));
    root = GetHTNode(huffmanqueue); //最后一个为根节点
    return root;
}

//初始化队列   0节点
void InitPQueue(PQueue *huffmanqueue)
{
    (*huffmanqueue) = (PQueue)malloc(sizeof(Queue));
    (*huffmanqueue)->first = NULL;
    (*huffmanqueue)->size = 0;
    return;
}


//将树的节点的信息，以权重升序在队列中存储
void AddPQueue(PQueue huffmanqueue, PHTNode newnode, int weight)
{
    if(huffmanqueue->size == MAX_SIZE)
    {
        printf("哈夫曼列表已经满了！\n");
        return;
    }
    PQueueNode queuenode = (PQueueNode)malloc(sizeof(QueueNode));
    queuenode->priorty = weight; //节点的权重
    queuenode->val = newnode;   //指向树的节点信息
    queuenode->next = NULL;

    //队列没有节点
    if(huffmanqueue->size == 0 || huffmanqueue->first == NULL)
    {
        //成为队列的第一个节点
        huffmanqueue->first = queuenode;
        huffmanqueue->size = 1; //队列节点数量为1
        return;
    }
    else//有多个节点
    {
        //比第一个节点的权重小，成为第一个节点
        if (weight <= huffmanqueue->first->priorty)
        {
            queuenode->next = huffmanqueue->first;
            huffmanqueue->first = queuenode;
            huffmanqueue->size++;
            return;
        }
        else  //迭代找到权重大于等于新节点权重的某个节点，插入到它的前面
        {
            PQueueNode iterator = huffmanqueue->first;  //找到的某个节点的上一个节点
            while(iterator->next != NULL )
            {
                if(weight <= iterator->next->priorty) //为某个节点 插入到它前面
                {
                    queuenode->next = iterator->next;
                    iterator->next = queuenode;
                    huffmanqueue->size++;
                    return;
                }
                iterator = iterator->next;  //比较下一个权重更大的节点
            }
            //没有比新节点权重大的节点，新节点成为最后的节点
            if(iterator->next == NULL)
            {
                iterator->next = queuenode;
                huffmanqueue->size++;
                return;
            }
        }
    }
}


//从队列中获取第一个节点的数据（树的节点的指针）
PHTNode GetHTNode(PQueue huffmanqueue)
{
    PHTNode popnode = NULL;
    if(huffmanqueue->size > 0)
    {
        PQueueNode pnode = huffmanqueue->first; //队列的第一个节点
        popnode = pnode->val;  // 树的节点指针
        huffmanqueue->first = pnode->next;
        huffmanqueue->size--;
        free(pnode);
        pnode = NULL;
    }
    else
    {
        printf("队列是空的!\n");
    }
    return popnode;
}


//后序遍历
void TraverseTree(PHTNode treenode,PHTable *table,int k,char code[256])
{
    if(treenode->left == NULL && treenode->right == NULL)
    {
        code[k] = '\0';  //字符串结束符
        TableNode *newtabnode = (TableNode *)malloc(sizeof(TableNode));
        newtabnode->code = (char *)malloc(sizeof(char) * (strlen(code) + 1)); //包括'\0'
        strcpy(newtabnode->code, code); //字符对应的编码
        newtabnode->symbol = treenode->symbol;  //字符
        newtabnode->next = NULL;
        //连接到表上
        if((*table)->first == NULL)
        {
            (*table)->first = newtabnode;
            (*table)->last = newtabnode;
        }
        else
        {
            (*table)->last->next = newtabnode;
            (*table)->last = newtabnode;
        }
    }
    if(treenode->left != NULL)
    {
        code[k] = '0';
        TraverseTree(treenode->left, table, k + 1, code);
    }
    if(treenode->right != NULL)
    {
        code[k] = '1';
        TraverseTree(treenode->right, table, k + 1, code);
    }
}
//
PHTable BuildTable(PHTNode codeTree)
{
    PHTable table = (PHTable)malloc(sizeof(HTable));  //创建一张codetree对应的编码表
    table->first = NULL;
    table->last = NULL;
    char code[256] = {0};
    int k = 0;   //层数
    TraverseTree(codeTree, &table, k, code);  //填充table
    return table;
}


void encode(PHTable table, char *str)
{
    FILE *file = fopen("text.txt", "w");
    assert(file);

    TableNode *node;
    int i = 0;
    printf("%s >> ", str);
    for (i = 0; str[i] != '\0'; i++)//打印每一个字符的编码
    {
        node = table->first;
        while(node->symbol != str[i]) //找到字符对应的编码
        {
            node = node->next; 
        }
        //fseek(file, 0, SEEK_END); //调整指针到末尾
        fwrite(node->code, strlen(node->code), 1, file);
        printf("%s ", node->code);  //打印
    }
    fwrite("\0", 1, 1, file);  //结束符
    fclose(file);
    printf("\n");
}

void decode(PHTNode Tree, char *code)
{
    PHTNode pnode = Tree;
    int i = 0;
    for (i = 0; code[i] != '\0'; i++)//遍历所有编码
    {
        if(pnode->left == NULL && pnode->right == NULL)
        {
            //当前节点为叶子节点
            printf("%c", pnode->symbol);
            pnode = Tree; //回到根节点
        }
        if(code[i] == '0')
        {
            pnode = pnode->left;
        }
        if(code[i] == '1')
        {
            pnode = pnode->right;
        }
        if (code[i] != '0' && code[i] != '1')
        {
            printf("编码格式是错误的！\n");
            return;
        }
    }

    if(pnode->left == NULL && pnode->right == NULL)
        {
            printf("%c", pnode->symbol);
        }
}