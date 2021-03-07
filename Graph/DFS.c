#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

#define MAXV 4
int visited[MAXV] = {0};  //标记某顶点已经访问  深度优先递归
int visited2[MAXV] = {0};   //深度优先非递归
int visited3[MAXV] = {0};  //广度优先

//边
typedef struct ANode
{
    int adjvex;  //该边的邻接点编号
    struct ANode *nextedge;  //指向下一条边
    int weight;   //权重
} EdgeNode;
//顶点
typedef struct VNode
{
    int count;        //数量
    char name;
    EdgeNode *firstedge;  //指向第一条边
} VNode;
//邻接表,多个节点
typedef struct 
{
    VNode adjlist[MAXV];  //头节点
    int vertexnum;   //顶点个数
    int edgenum;     //边的数量
} AdjGraph;



void CreatAdj(AdjGraph **g, int A[MAXV][MAXV], int v, int e)
{
    int i = 0;
    int j = 0;
    *g = (AdjGraph *)malloc(sizeof(AdjGraph));
    for (i = 0; i < v; i++)
    {
        (*g)->adjlist[i].firstedge = NULL;
        (*g)->adjlist[i].name = 'A' + i;  //顶点名字
    }
    for (i = 0; i < v; i++)
    {
        (*g)->adjlist[i].count = 0;  //出度
        for (j = v-1; j >= 0; j--)   //采用头插法，让编号小的作为第一条弧的弧头节点
        {
            if(A[i][j] != 0)//存在边
            {
                EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));//新的边
                (*g)->adjlist[i].count += 1;  //出度
                p->adjvex = j;
                p->weight = A[i][j];
                p->nextedge = (*g)->adjlist[i].firstedge;  //头插
                (*g)->adjlist[i].firstedge = p;
            }
        }
    }
    (*g)->edgenum = e;
    (*g)->vertexnum = v;
}
void DispAdj(AdjGraph g)
{
    int i = 0;
    EdgeNode *p;
    for (i = 0; i < g.vertexnum; i++)
    {
        p = g.adjlist[i].firstedge; //某个顶点
        printf("%3d:%c:", i,g.adjlist[i].name);
        while(p != NULL)
        {
            printf("%3d:%c[%d]->", p->adjvex, g.adjlist[p->adjvex].name, p->weight);
            p = p->nextedge;
        }
        printf("^\n");
    }
}



/*
    深度优先算法(递归算法)
*/
void DFS(AdjGraph *g,int v)
{
    assert(g);
    EdgeNode *p;  //边
    printf("%c", g->adjlist[v].name);  //访问的顶点 v为顶点的编号
    visited[v] = 1;   //标记为访问过
    p = g->adjlist[v].firstedge;  //p指向第一条弧的弧头节点
    while(p != NULL)  //遍历所有弧头节点
    {
        if(visited[p->adjvex] == 0)  //该节点未访问
        {
            DFS(g, p->adjvex);
        }
        p = p->nextedge;  //下一条弧的弧头节点
    }
}


/*
    深度优先算法（非递归算法）
*/
void DFS1(AdjGraph *g,int v)
{
    assert(g);
    EdgeNode *p;
    int ST[MAXV] = {0};
    int top = 0;
    int node = 0;
    int x = 0;
    ST[top] = v;
    visited2[v] = 1; //标记为访问
    printf("%c", g->adjlist[v].name); 

    while(top >= 0)  //栈非空
    {
        x = ST[top];
        p = g->adjlist[x].firstedge;  //第一个弧头节点
        while(p != NULL)
        {
            node = p->adjvex;   //弧头节点的编号
            if(visited2[node] == 0)  
            {
                printf("%c", g->adjlist[node].name);
                visited2[node] = 1;  //标记为访问
                ST[++top] = node; //节点编号进栈
                break;
            }
            p = p->nextedge;  //下一条弧
        }
        if(p == NULL)//所以邻接顶点都访问过了
        {
            top--;  //回到上一个节点
        }
    }
    printf("\n");
}

/*
    广度优先算法
*/

void BFS(AdjGraph *g,int v)
{
    EdgeNode *p;
    int queue[MAXV] = {0};
    int rear = 0;
    int front = 0;
    visited3[v] = 1; //标记为访问
    printf("%c", g->adjlist[v].name);
    queue[rear] = v; //当前节点进队
    rear = (rear + 1) % MAXV;
    while(front != rear) //队列非空
    {
        int node = queue[front];//出队
        front = (front + 1) % MAXV;
        p = g->adjlist[node].firstedge; //弧头节点
        while(p != NULL)
        {
            int x = p->adjvex;  //弧头节点的编号
            if(visited3[x] == 0)
            {
                printf("%c", g->adjlist[x].name);
                queue[rear] = x; //当前节点进队
                rear = (rear + 1) % MAXV;
                visited3[x] = 1; //标记为访问过了
            }
            p = p->nextedge;
        }
    }
    printf("\n");
}



int main()
{
    AdjGraph *g;
    int A[MAXV][MAXV] = {{0, 12, 34, 56}, {12, 0, 0, 50}, {34, 0, 0, 60}, {56, 50, 60, 0}};
    CreatAdj(&g, A, MAXV, 10);
    DispAdj(*g);
    //递归深度优先遍历  从编号为0的顶点开始遍历
    DFS(g, 0);
    printf("\n");

    //非递归深度优先遍历
    DFS1(g, 0);

    //广度优先算法
    BFS(g, 1);

    return 0;
}