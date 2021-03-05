/*
        图的邻接矩阵
*/

#include<stdio.h>
#include<stdlib.h>

#define MAXV 4
typedef char VertexType;  //顶点的类型

typedef struct Graph
{
    int edges[MAXV][MAXV]; //边
    VertexType vertex[MAXV];  //顶点
    int vertexnum;    //顶点的数量
    int edgenum;      //边的数量
} MatGraph;


//函数的定义
void CreatGraph(MatGraph *g)
{
    int i = 0;
    int j = 0;
    int nums = 0;
    g->vertexnum = MAXV;
    //输入顶点的信息
    printf("请输入%d个顶点的名字：\n", MAXV);
    for (i = 0; i < MAXV; i++)
    {
        scanf("%c", &(g->vertex[i]));
        getchar();
    }
    //输入边的信息
    for (i = 0; i < MAXV; i++)
    {
        
        for (j = 0; j < MAXV; j++)
        {
            printf("请输入%c顶点到%c顶点的权重(无连接权重为0):>",g->vertex[i],g->vertex[j]);
            scanf("%d", &(g->edges[i][j]));
            getchar();
            if(g->edges[i][j] == 0)
            {
                nums++;
            }
            //printf("\n");
        }
    }
    g->edgenum = (MAXV * (MAXV - 1)) / 2 - nums;
}

void PrintGraph(MatGraph g)
{
    int i = 0;
    int j = 0;
    printf("图的邻接矩阵:\n");
    for (i = 0; i < g.vertexnum; i++)
    {
        for (j = 0; j < g.vertexnum; j++)
        {
            printf("%-4d", g.edges[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    MatGraph g;
    CreatGraph(&g);
    PrintGraph(g);
    return 0;
}