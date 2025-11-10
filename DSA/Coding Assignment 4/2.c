#include <stdio.h>
#include "DataStructures.h"

void addEdge(int n, Vector adj[n], int a, int b){
    // a and b are assumed to be <=n
    push_back(&adj[a-1], b);
    push_back(&adj[b-1], a);
}

typedef struct{
    int u, v; // Vertices at the two ends of the edge
    int w; // Weight of the edge
}Edge;

Edge* Prims(int n, Vector adj[n], int m, int arr[m]){
    
}

int main(){
    int n, m;
    scanf("%d\n%d", &n, &m);
    int adj[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            adj[i][j] = 0;
        }
    }
    Edge edges[m];
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        addEdge(n, adj, edges[i].u, edges[i].v);
    }

}