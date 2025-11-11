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

// Return the array of edges in the MST
Edge* prims(int n, Vector adj[n], int m, Edge edges[m]){
    int *visited = calloc(n, sizeof(int));

    int src = 1;
    visited[src-1] = 1;
    
    Edge *MST = malloc(sizeof(Edge)*(n-1)); // Array of edges in the MST
    int MSTcount = 0;

    Edge *heap = malloc(sizeof(Edge)*m);
    int heapSize = 0;
    // Copy all the edges from src into heap
    for(int i=0; i<adj[src-1].size; i++){
        heap[heapSize++] = ((Edge *)adj[src-1].data)[i];
    }
    buildHeap(heap, heapSize);


    while(heapSize>0 && MSTcount<n-1){
        Edge minE = deleteMin(heap, heapSize--);
        int u = minE.u;
        int v = minE.v;
        // Skip edges with both vertices already visited
        if(visited[u-1]==1 && visited[v-1]==1){
            continue;
        }
        // Pick the next vertex, which should be unvisited
        int next = visited[u-1] ? v : u;
        visited[next-1] = 1;

        MST[MSTcount++] = minE; // Push the valid edge

        for(int i=0; i<adj[next-1].size; i++){
            Edge e = ((Edge *)adj[next-1].data)[i];
            if(!visited[e.v-1] || !visited[e.u-1]){
                heap[heapSize++] = e; // Push the edge onto the heap if the other end is unvisited
            }
        }
        buildHeap(heap, heapSize);
    }
    free(heap);
    return MST;
}

int main(){
    int n, m;
    scanf("%d\n%d", &n, &m);

    Vector adj[n];
    for(int i=0; i<n; i++){
        initVector(&adj[i], sizeof(Edge));
    }

    Edge edges[m];
    for(int i=0; i<m; i++){
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        addEdge(n, adj, edges[i].u, edges[i].v, edges[i].w);
    }

    Edge *MST = malloc(sizeof(Edge)*(n-1));
    MST = prims(n, adj, m, edges);

    int totalWeight = 0;
    
    printf("Edges in MST:\n");
    for(int i=0; i<n-1; i++){
        printf("(%d, %d) weight = %d\n", MST[i].u, MST[i].v, MST[i].w);
        totalWeight += MST[i].w;
    }
    printf("Total Weight = %d\n", totalWeight);
}