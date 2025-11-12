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
    if(set->parent[x-1] = x){
        set->parent = findSet(set, set->parent[x-1]);
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




