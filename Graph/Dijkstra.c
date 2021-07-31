#include<stdio.h>
#include<stdlib.h>

/*
    无向图的邻接矩阵 v0到其他顶点的最短路径
*/

#define MAXV 5
typedef char VertexType;  //顶点的类型
#define INF 1000

typedef struct Graph
{
    int edges[MAXV][MAXV]; //边
    VertexType vertex[MAXV];  //顶点
    int vertexnum;    //顶点的数量
    int edgenum;      //边的数量
} MatGraph;


//函数的定义
void CreatGraph2(MatGraph *g,int a[MAXV][MAXV])
{
    int i = 0;
    int j = 0;
    int nums = 0;
    g->vertexnum = MAXV;
    //生成节点的名称
    for (i = 0; i < MAXV; i++)
    {
        g->vertex[i] = i + 'A';
    }
    //边的信息
    for (i = 0; i < MAXV; i++)
    {
        
        for (j = 0; j < MAXV; j++)
        {

            g->edges[i][j] = a[i][j];
            if(g->edges[i][j] == 0)
            {
                nums++;
            }
            //printf("\n");
        }
    }
    g->edgenum = (MAXV * (MAXV - 1)) / 2 - nums;
}

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
            printf("请输入%c顶点到%c顶点的权重(不直接连接权重为%d):>",g->vertex[i],g->vertex[j],INF);
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
            printf("%-5d", g.edges[i][j]);
        }
        printf("\n");
    }
}


void Init(MatGraph g,int shortway[MAXV])
{
    int i = 0;
    for (i = 0; i < MAXV; i++)
    {
        shortway[i] = g.edges[0][i]; //v0到其他顶点的直接连线距离
    }
}

//输出V0到其他顶点的最短距离
void Dijkstra(MatGraph g,int shortway[MAXV],int p[MAXV])
{
    Init(g,shortway);      //初始化
    int finded[MAXV] = {0};  //标识是否求出到v0的最小的距离
    finded[0] = 1;  //v0到v0不用找最短距离
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < g.vertexnum; i++)
    {
        int min = INF;
        for (j = 0; j < g.vertexnum; j++)
        {
            if(!finded[j] && shortway[j] < min)
            {
                min = shortway[j];
                k = j;
            }
        }

        finded[k] = 1;   //求得了最小的距离

        for (j = 0; j < g.vertexnum; j++)
        {
            if(!finded[j] && min+g.edges[k][j] < shortway[j])
            {
                shortway[j] = min + g.edges[k][j];
                p[j] = k;
            }
        }

    }
}





int main()
{
    //图的邻接矩阵
    int a[MAXV][MAXV] = {{0,  1  ,  5  , 2  , 7  }, 
                         {1,  0  ,  INF, 3  , INF}, 
                         {5,  INF,  0  , 1  , 3  }, 
                         {2,  3  ,  1  , 0  , INF}, 
                         {7,  INF,  3  , INF, 0  }};

    MatGraph g;
    int shortway[MAXV] = {0};  //最短距离
    int p[MAXV] = {0};         //前驱
    CreatGraph2(&g,a);
    PrintGraph(g);

    Dijkstra(g,shortway,p);  //求每个顶点到v0的最短距离
    for (int i = 0; i < MAXV; i++)
    {
        printf("%c的前驱是%c\n", g.vertex[i],g.vertex[p[i]]);
    }
    printf("\n");
    for (int i = 0; i < MAXV; i++)
    {
        printf("%c到%c的最短路径为%d\n", g.vertex[0], g.vertex[i], shortway[i]);
    }
    return 0;
}