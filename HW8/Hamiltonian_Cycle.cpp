#include <cstdio>
#include <stdlib.h>
#include <string.h>

#define MaxVertexNum 200

typedef struct {
    int Nv;
    int Ne;
    int AdjMatrix[MaxVertexNum][MaxVertexNum]; //start from AdjMatrix[1][1] 
}Graph;

void Judge(Graph &G, int *path, int len);

int main() {
    Graph G;
    scanf("%d%d", &G.Nv, &G.Ne);
    memset(G.AdjMatrix, 0, sizeof(G.AdjMatrix));

    int v1, v2;
    for(int i=0; i<G.Ne; i++) {
        scanf("%d%d", &v1, &v2);
        G.AdjMatrix[v1][v2] = 1;
        G.AdjMatrix[v2][v1] = 1;
    }

    int k, n, *path;
    scanf("%d", &k);
    while(k--) {
        scanf("%d", &n);
        path = (int*)malloc(n * sizeof(int));

        for(int i=0; i<n; i++) {
            scanf("%d", &path[i]);
        }
        
        Judge(G, path, n);
    }

    return 0;
}

void Judge(Graph &G, int *path, int len) {
    if((G.Nv + 1 != len) || (path[0] != path[len-1])) {
        printf("NO\n");
        return;
    }
    
    int v1, v2;
    for(int i=0; i<len-1; i++) {
        //no edge from path[i] to path[i+1]
        if(G.AdjMatrix[path[i]][path[i+1]] != 1) {
            printf("NO\n");
            return;
        }

        //pass a same vertex 2 times
        for(int j=0; j<i; j++) {
            if(path[i] == path[j]) {
                printf("NO\n");
                return;
            }
        }
    }

    printf("YES\n");
}