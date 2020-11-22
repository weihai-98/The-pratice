#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} bool;
#define MaxVertexNum 10  /* maximum number of vertices */
typedef int Vertex;      /* vertices are numbered from 1 to MaxVertexNum */

typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;
    PtrToAdjVNode Next;
};

typedef struct Vnode{
    PtrToAdjVNode FirstEdge;
} AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq( LGraph Graph, Vertex Seq[] );

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for (i=0; i<N; i++) {
        for (j=0; j<G->Nv; j++)
            scanf("%d", &Seq[j]);
        if ( IsTopSeq(G, Seq)==true ) printf("yes\n");
        else printf("no\n");
    }

    return 0;
}

/* Your function will be put here */
bool IsTopSeq( LGraph Graph, Vertex Seq[] ){
    int deg[2000],queue[2000];
    int i,vertex,n=0;
    int front=-1,rear=-1;
    PtrToAdjVNode p;
    /*初始化存储degree的数表*/
    for(i=0;i<1000;i++)
        deg[i]=0;
    /*计算各个顶点的degree*/
    for(i=0;i<Graph->Nv;i++){
        p=Graph->G[i].FirstEdge;
        while(p!=NULL){
            deg[p->AdjV]++;
            p=p->Next;
        }
    }
    for(i=0;i<Graph->Nv;i++){
        /*因为顶点在图中的保存的值是从零开始,所以所有的seq值均减1*/
        vertex=Seq[i]-1;
        queue[++rear]=vertex;
        while(front!=rear){
            n++;
            vertex=queue[++front];
            if(deg[vertex]!=0){
                return false;
            }
        /*该顶点链接的下一个顶点的地址为p，因为该顶点已读，因此所有链接的下一个顶点的degree减1*/
            p=Graph->G[vertex].FirstEdge;
            while(p!=NULL){
                deg[p->AdjV]--;
                if(deg[p->AdjV]<0)
                    return false;
                p=p->Next;
            }
        }
    }
    if(n!=Graph->Nv)
        return false;
    else
    {
        return true;
    }
    
}