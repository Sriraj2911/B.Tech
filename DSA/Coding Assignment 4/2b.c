#include <stdio.h>
#include <stdlib.h>
#include "DataStructures.h"

typedef struct{
    int *parent; // Array of parents of elements of the set
    int *rank; // Array of ranks of the trees
    int size;
}DisjointSet;

DisjointSet* createSet(int n){
    DisjointSet *set = malloc(sizeof(DisjointSet));
    set->parent = malloc(sizeof(int)*n);
    set->rank = calloc(n, sizeof(int));
    set->size = n;

    for(int i=0; i<n; i++){
        set->parent[i] = i+1; // Initially, each element is its own parent
    }
    return set;
}

int findSet(DisjointSet *set, int x){
    if(set->parent[x-1] != x){
        set->parent[x-1] = findSet(set, set->parent[x-1]);
    }
    return set->parent[x-1];
}

void unionSet(DisjointSet *set, int x, int y){
    int rootX = findSet(set, x);
    int rootY = findSet(set, y);

    if(rootX == rootY){
        return; // Already in the same set
    }
    // Attach smaller rank tree under larger rank tree
    if(set->rank[rootX-1] < set->rank[rootY-1]){
        set->parent[rootX-1] = rootY;
    }
    else if(set->rank[rootX-1] > set->rank[rootY-1]){
        set->parent[rootY-1] = rootX;
    }
    else{
        set->parent[rootY-1] = rootX;
        set->rank[rootX]++;
    }
}

void freeSet(DisjointSet *set){
    free(set->parent);
    free(set->rank);
    free(set);
}

// Build the graph by repeated addEdge() calls
void addEdge(int n, Vector adj[n], int a, int b, int w){
    Edge e1 = {a, b, w};
    Edge e2 = {b, a, w};
    push_back(&adj[a-1], &e1);
    push_back(&adj[b-1], &e2);
}

Edge* kruskals(int n, Vector adj[n], int m, Edge edges[m]){
    buildHeap(edges, m); // Heapify the edges according to weight

    Edge* MST = malloc(sizeof(Edge)*(n-1));
    int MSTcount = 0;
    // Create and initialise the disjoint-set
    DisjointSet *set = malloc(sizeof(DisjointSet));
    set = createSet(n);

    while(MSTcount < n && m > 0){
        Edge minE = deleteMin(edges, m--);
        int u = minE.u;
        int v = minE.v;
        int w = minE.w;

        if(findSet(set, u) == findSet(set, v)) continue; // Don't add the edge if u and v are in the same set
        
        unionSet(set, u, v);
        MST[MSTcount++] = minE;
    }
    freeSet(set);
    return MST;
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

    Edge *MST = malloc(sizeof(Edge)*(n-1));
    MST = kruskals(n, adj, m, edges);

    int totalWeight = 0;
    
    printf("Edges in MST:\n");
    for(int i=0; i<n-1; i++){
        printf("(%d, %d) weight = %d\n", MST[i].u, MST[i].v, MST[i].w);
        totalWeight += MST[i].w;
    }
    printf("Total Weight = %d\n", totalWeight);
}


