#include <iostream>
#include <vector>
#include <queue>
#include <map>
#define INFTY 168168168

using namespace std;

typedef struct ArcNode *PtrToArcNode;
struct ArcNode {
    int adjvertex;
    int load; //capacity
    PtrToArcNode next;
};
typedef struct VertexNode AdjList[1000];
struct VertexNode {
    PtrToArcNode first;
};
typedef struct {
    AdjList L;
    int Nv;
    int Ne;
}Graph;

void EdmondsKarp(Graph &G, int src, int dst);

int main() {
    Graph G;
    string src, dst;
    G.Nv = 0;
    cin >> src >> dst >> G.Ne;

    for(int i=0; i<1000; i++) {
        G.L[i].first = nullptr;
    }

    //input the graph
    map<string, int> station;
    for(int i=0; i<G.Ne; i++) {
        string v1, v2;
        int w;
        cin >> v1 >> v2 >> w;

        if(station.find(v1) == station.end()) {
            station[v1] = ++G.Nv;
        }
        if(station.find(v2) == station.end()) {
            station[v2] = ++G.Nv;
        }

        PtrToArcNode ptr = (PtrToArcNode)malloc(sizeof(struct ArcNode));
        ptr->adjvertex = station[v2];
        ptr->load = w;
        ptr->next = G.L[station[v1]].first;
        G.L[station[v1]].first = ptr;
    }

    //EK algorithm
    EdmondsKarp(G, station[src], station[dst]);
    return 0;
}

void EdmondsKarp(Graph &G, int src, int dst) {
    //int flow[G.Nv + 1][G.Nv + 1]
    vector<vector<int>> flow(G.Nv + 1, vector<int>(G.Nv + 1));
    vector<int> path(G.Nv + 1);
    vector<int> curflow(G.Nv + 1);
    queue<int> q;
    int maxflow = 0;
    
    while(1) {
        fill(curflow.begin(), curflow.end(), 0);
        curflow[src] = INFTY;
        q.push(src);

        //BFS, find the path to dst
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            for(PtrToArcNode ptr = G.L[v].first; ptr != nullptr; ptr = ptr->next) {
                int w = ptr->adjvertex;
                if(curflow[w] == 0 && flow[v][w] < ptr->load) { //vertex w has not been visited, and the pipe v->w has remaining space
                    path[w] = v;
                    curflow[w] = min(curflow[v], ptr->load - flow[v][w]); //if "pipe" has enough space, carry all flow, if not, use all the remaining space 
                    q.push(w);
                }
            }
        }

        if(curflow[dst] == 0) { //no augmented path found, flow got max
            break;
        }

        for(int i=dst; i!=src; i=path[i]) {
            flow[path[i]][i] += curflow[dst]; //update forward arc
            flow[i][path[i]] -= curflow[dst]; //update backward arc
        }
        
        maxflow += curflow[dst];
    }

    cout << maxflow << endl;
}