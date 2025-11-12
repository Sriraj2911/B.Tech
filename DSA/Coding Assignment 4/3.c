#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "DataStructures.h"

typedef struct{
    int value;
    int len;
    int prev;
}Vertex;

// Build the directed graph by repeated addEdge() calls
void addEdge(int n, Vector adj[n], int u, int v, int w){
    Edge e1 = {u, v, w};
    push_back(&adj[u-1], &e1);
}

bool allVisited(int visited[], int n){
    for(int i=0; i<n; i++){
        if(visited[i] == 0) return false;
    }
    return true;
}

// Print the path from src to v
void printPath(Vertex* vertices, int v, int n){
    if(vertices[v-1].prev == 0){
        printf("%d ", v);
        return;
    } 
    printPath(vertices, vertices[v-1].prev, n);
    printf("%d ", v);
}

void dijkstra(int n, Vector adj[n], int src){
    Vertex vertices[n];
    int visited[n];
    for(int i=0; i<n; i++){
        vertices[i].value = i+1;
        vertices[i].prev = 0;
        vertices[i].len = INT_MAX;
        visited[i] = 0;
    }
    vertices[src-1].len = 0;

    for(int i=0; i<n-1; i++){
        int u = -1, minLen = INT_MAX;
        // Pick the minimum vertex
        for(int j=0; j<n; j++){
            if(!visited[j] && vertices[j].len < minLen){
                minLen = vertices[j].len;
                u = j;
            }
        }

        if(u == -1) break; // Unreachable vertex

        visited[u] = 1;

        for(int j=0; j<adj[u].size; j++){
            Edge* e = (Edge *)get(&adj[u], j);
            int v = e->v;
            int w = e->w;
            if(!visited[v-1] && vertices[u].len != INT_MAX && vertices[u].len + w < vertices[v-1].len){
                vertices[v-1].len = vertices[u].len + w;
                vertices[v-1].prev = vertices[u].value;
            }
        }
    }
    for(int i=0; i<n; i++){
        printf("Vertex %d: Length = %d, Path = ", vertices[i].value, vertices[i].len);
        printPath(vertices, vertices[i].value, n);
        printf("\n");
    }
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

    int src; 
    scanf("%d", &src);

    dijkstra(n, adj, src);
    
    
}