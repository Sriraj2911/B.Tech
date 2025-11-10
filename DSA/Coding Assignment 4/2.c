#include <stdio.h>
#include <stdbool.h>
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

// bool to check if all the vertices were visited or not
bool allVisited(int* visited, int n){
    for(int i=0; i<n; i++){
        if(visited[i] == 0) return false;
    }
    return true;
}

Edge* Prims(int n, Vector adj[n], int m, Edge edges[m]){
    buildHeap(edges, m);
    int visited[n];
    for(int i=0; i<n; i++){
        visited[i] = 0;
    }
    int src = edges[0].u; // Vertex of the edge with minimum weight
    visited[src-1] = 1;

    Edge MST[n-1]; // Array of edges in the MST

    while(!allVisited(visited, n)){
        int curr = src;
        Vector temp = adj[curr-1]; // Vector with adjacent vertices of 'curr'
        
    }

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