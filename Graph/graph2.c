#include<stdio.h>
#include<stdlib.h>

#define MAXV 4

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
    char name;        //节点名字
    int count;        //数量
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
        (*g)->adjlist[i].count = 0;
        for (j = v-1; j >= 0; j--)
        {
            if(A[i][j] != 0)//存在边
            {
                EdgeNode *p = (EdgeNode *)malloc(sizeof(EdgeNode));//新的边
                (*g)->adjlist[i].count += 1;
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
            printf("%3d[%d]->", p->adjvex, p->weight);
            p = p->nextedge;
        }
        printf("^\n");
    }
}

int main()
{
    AdjGraph *g;
    int A[MAXV][MAXV] = {{0, 12, 34, 56}, {12, 0, 0, 50}, {34, 0, 0, 60}, {56, 50, 60, 0}};
    CreatAdj(&g, A, MAXV, 10);
    DispAdj(*g);
    return 0;
}