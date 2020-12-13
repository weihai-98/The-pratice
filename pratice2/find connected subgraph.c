#include <stdio.h>
#include <stdlib.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}

/* Your function will be put here */
void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) ){
    int i,j,t,n=G->NumOfVertices,first;
    int isconnect[20][20]={0},stack[20];/*stack is to Store updated vertices*/
    PtrToVNode b;
    int *a;
    for(i=0;i<n;i++){
        int isread[20]={0};
        isconnect[i][i]=1;
        t=0;
        stack[++t]=i;
        while(t!=0){ /*Find connected parts from each vertex*/
            j=stack[t];
            t--;
            b=G->Array[j];
            while(b!=NULL){
            isconnect[i][b->Vert]=1;
            if(isread[b->Vert]==0){
                isread[b->Vert]=1;
                stack[++t]=b->Vert;
                }
            b=b->Next; 
            }
        }
    }
    a=malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        a[i]=0;
    }
    i=0;
    /*Print out the vertices in the connected subgraph*/
    while(i<n){
        first=1;
        for(j=i;j<n;j++){
            if(isconnect[i][j]==1&&isconnect[j][i]==1){
                a[j]=1;
                if(first==0){
                printf(" ");
                }
                else if(first==1){
                first=0;
                }
            (*visit)(j);
            }
        }
        printf("\n");
        while(a[i]!=0){
            i++;
            if(i>n)
                break;            
        }
    }
}