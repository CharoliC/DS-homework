#include <cstdio>
#include <stdlib.h>
#include <string.h>

typedef struct EdgeNode {
    int v1, v2, w;
    bool status; //if the edge has the same weight as othor edges, and can connect 2 components, status = true
}Edge;
typedef struct HeapStruct {
    Edge *edges;
    int size;
}*MinHeap;
typedef int *UFset;

//min-heap
void Insert(MinHeap H, Edge e);
Edge DeleteMin(MinHeap H);

//disjoint set
void Union(UFset &S, int rt1, int rt2);
int Find(UFset &S, int x);

void JudgeMST(MinHeap H, UFset &S);

int components, isUnique = 1, weight = 0;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    components = n; //every single vertex is a component

    MinHeap H = (MinHeap)malloc(sizeof(struct HeapStruct));
    H->edges = (Edge*)malloc((m + 1) * sizeof(struct EdgeNode));
    H->edges[0].w = -1;
    H->size = 0;

    UFset S = (int*)malloc((n + 1) * sizeof(int));
    memset(S, -1, (n + 1) * sizeof(int));

    while(m--) {
        Edge e;
        scanf("%d%d%d", &e.v1, &e.v2, &e.w);
        e.status = false;
        Insert(H, e);
    }

    JudgeMST(H, S);

    return 0;
}

void Insert(MinHeap H, Edge e) {
    H->edges[++H->size] = e;

    int i;
    for(i=H->size; H->edges[i/2].w > e.w; i/=2) {
        H->edges[i] = H->edges[i/2];
    }
    H->edges[i] = e;
}

Edge DeleteMin(MinHeap H) {
    Edge e = H->edges[1];
    H->edges[1] = H->edges[H->size--];

    Edge temp = H->edges[1];
    int i, child;
    for(i=1; 2*i<H->size; i=child) {
        child = 2*i;
        if(child + 1 <= H->size && H->edges[child + 1].w < H->edges[child].w) {
            child++;
        }
        if(temp.w < H->edges[child].w) {
            break;
        }
        H->edges[i] = H->edges[child];
    }
    H->edges[i] = temp;
    return e;
}

void Union(UFset &S, int rt1, int rt2) {
    if(rt1 != rt2) {
        S[rt2] = rt1;
        components--;
    }
}

int Find(UFset &S, int x) {
    if(S[x] < 0) {
        return x;
    }
    else {
        return S[x] = Find(S, S[x]);
    }
}

void JudgeMST(MinHeap H, UFset &S) {
    Edge e, next_e;
    while(H->size != 0) {
        //select an edge with the least weight
        e = DeleteMin(H);

        //if edge e can connect 2 components
        if(Find(S, e.v1) != Find(S, e.v2)) {
            for(int i=1; i<=H->size; i++) {
                next_e = H->edges[i];
                if(next_e.w == e.w && Find(S, next_e.v1) != Find(S, next_e.v2)) {
                    H->edges[i].status = true;
                }
            }
            Union(S, Find(S, e.v1), Find(S, e.v2));
            weight += e.w;
        }
        //e cannot connect 2 components, but e can connect 2 components before selecting another edge with the same weight as e, then MST is not unique
        else {
            if(e.status) {
                isUnique = 0;
            }
        }
    }

    if(components > 1) {
        printf("No MST\n%d", components);
    }
    else {
        printf("%d\n", weight);
        if(isUnique) {
            printf("Yes");
        }
        else {
            printf("No");
        }
    }
}