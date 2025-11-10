#include <stdio.h>

void addEdge(int n, int adj[n][n], int a, int b){
    // a and b are assumed to be <=n
    adj[a-1][b-1] = 1;
    adj[b-1][a-1] = 1;
}

typedef struct{
    int u, v; // Vertices at the two ends of the edge
    int w; // Weight of the edge
}Edge;

// struct Vector{
//     int size;
//     int array[size];
// };

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