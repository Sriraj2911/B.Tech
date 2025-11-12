#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "DataStructures.h"

// Build the graph by repeated addEdge() calls
void addEdge(int n, Vector adj[n], int a, int b, int w){
    Edge e1 = {a, b, w};
    Edge e2 = {b, a, w};
    push_back(&adj[a-1], &e1);
    push_back(&adj[b-1], &e2);
}

int main(){
    int n, m;
    scanf("%d\n%d", &n, &m);

    Vector adj[n];
    for(int i=0; i<n; i++){
        initVector(&adj[i], sizeof(Edge)); // Initialise each vector as a vector of edges
    }

    Edge edges[m];
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        addEdge(n, adj, edges[i].u, edges[i].v, edges[i].w);
    }
}