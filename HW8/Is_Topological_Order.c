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
}AdjList[MaxVertexNum];

typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;
    int Ne;
    AdjList G;
};
typedef PtrToGNode LGraph;

LGraph ReadG(); /* details omitted */

bool IsTopSeq(LGraph Graph, Vertex Seq[]);

int main()
{
    int i, j, N;
    Vertex Seq[MaxVertexNum];
    LGraph G = ReadG();
    scanf("%d", &N);
    for(i=0; i<N; i++) {
        for(j=0; j<G->Nv; j++) {
            scanf("%d", &Seq[j]);
        }
        
        if(IsTopSeq(G, Seq) == true) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }

    return 0;
}

/* Used for test */
LGraph ReadG() {
    LGraph G = (PtrToGNode)malloc(sizeof(struct GNode));
    PtrToAdjVNode ptr;
    int v1, v2;
    int i;

    scanf("%d%d", &G->Nv, &G->Ne);

    for(i=0; i<G->Nv; i++) {
        G->G[i].FirstEdge = NULL;
    }

    for(i=0; i<G->Ne; i++) {
        scanf("%d%d", &v1, &v2);
        
        ptr = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
        ptr->AdjV = v2;
        ptr->Next = G->G[v1 - 1].FirstEdge;
        G->G[v1-1].FirstEdge = ptr;
    }

    return G;
}

/* Your function will be put here */
bool IsTopSeq(LGraph Graph, Vertex Seq[]) {
    PtrToAdjVNode ptr;
    int indegree[10];
    int i;

    //count indegree
    for(i=0; i<Graph->Nv; i++) {
        indegree[i] = 0;
    }
    for(i=0; i<Graph->Nv; i++) {
        for(ptr = Graph->G[i].FirstEdge; ptr != NULL; ptr = ptr->Next) {
            indegree[ptr->AdjV - 1]++;
        }
    }

    //dequeue Seq[0], Seq[1], ...
    for(i=0; i<Graph->Nv; i++) {
        //if indegree of Seq[i] is not 0, not topological order
        if(indegree[Seq[i] - 1] != 0) {
            return false;
        }

        for(ptr = Graph->G[Seq[i] - 1].FirstEdge; ptr != NULL; ptr = ptr->Next) {
            indegree[ptr->AdjV - 1]--;
        }
    }

    return true;
}