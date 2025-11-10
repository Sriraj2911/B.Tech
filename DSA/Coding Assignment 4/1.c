#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "DataStructures.h"

void addEdge(int n, int adj[n][n], int a, int b){
    // a and b are assumed to be <=n
    adj[a-1][b-1] = 1;
    adj[b-1][a-1] = 1;
}

// A new struct for the vertices
typedef struct{
    int value; 
    int length; // Distance from the source vertex
    Queue q; // Queue of vertices present in the path from source
}Vertex;

Vertex* bfs(int n, int adj[n][n], int src) {
    int *discovered = calloc(n, sizeof(int)); // An array to maintain the discovered vertices
    Queue *q = malloc(sizeof(Queue));
    initQ(q, n);
    // Initialise the queue with the source vertex
    enqueue(q, src, n);
    discovered[src-1] = 1;
    // An array of Vertex data type
    Vertex *vertices = malloc(sizeof(Vertex)*n);
    for(int i=0; i<n; i++){
        vertices[i].value = i+1;
        vertices[i].length = -1;
        initQ(&(vertices[i].q), n);
    }
    // Initialize for the source vertex
    vertices[src-1].length = 0;
    enqueue(&(vertices[src-1].q), src, n);

    while (!isEmptyQ(q)) {
        int curr = dequeue(q, n); // Dequeuing the vertex means it has been visited

        for (int i = 0; i < n; i++) {
            if (adj[curr-1][i] && !discovered[i]) {
                discovered[i] = 1;

                // Copy the path from curr to i
                Queue temp = vertices[curr-1].q;
                initQ(&(vertices[i].q), n);
                for(int j=0; j<temp.count; j++){
                    int idx = (temp.front+j)%n;
                    enqueue(&(vertices[i].q), temp.data[idx], n);
                }
                // Add this vertex to the path
                enqueue(&(vertices[i].q), i+1, n);
                // Update the length of this vertex from the source
                vertices[i].length = vertices[curr-1].length + 1;
                // Enqueue this vertex to the queue
                enqueue(q, i+1, n);
            }
        }
    }

    free(q);
    return vertices;
}

int main(){
    int n, m;
    scanf("%d\n%d", &n, &m);
    int arr[2];
    int adj[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            adj[i][j] = 0;
        }
    }
    // Build the graph
    for(int i=0; i<m; i++){
        scanf("%d %d", arr, arr+1);
        addEdge(n, adj, arr[0], arr[1]);
    }
    int src;
    scanf("%d", &src);

    Vertex *vertices = bfs(n, adj, src);

    for(int i=0; i<n; i++){
        printf("Vertex %d: Length = %d, Path: ", vertices[i].value, vertices[i].length);
        printQ(vertices[i].q, n);
    }
}
