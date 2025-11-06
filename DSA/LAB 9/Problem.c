#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int literal_to_index(int x, int n) {
    return (x > 0) ? (x - 1) : (-x - 1 + n);
}

int negate_index(int i, int n) {
    return (i + n) % (2*n);
}

void addEdge(int n, int adj[2*n][2*n], int a, int b) {
    int a_idx = literal_to_index(a, n);
    int b_idx = literal_to_index(b, n);
    int not_a = negate_index(a_idx, n);
    int not_b = negate_index(b_idx, n);

    adj[not_a][b_idx] = 1;
    adj[not_b][a_idx] = 1;
}

int* bfs(int n, int adj[2*n][2*n], int src) {
    int *visited = calloc(2*n, sizeof(int));
    int *q = malloc(sizeof(int)*2*n);
    int front = 0, rear = 0;

    q[rear++] = src;
    visited[src] = 1;

    while (front < rear) {
        int curr = q[front++];
        for (int i = 0; i < 2*n; i++) {
            if (adj[curr][i] && !visited[i]) {
                visited[i] = 1;
                q[rear++] = i;
            }
        }
    }

    free(q);
    return visited;
}

bool unsatisfied(int n, int adj[2*n][2*n], int literal) {
    int src = literal_to_index(literal, n);
    int not_src = negate_index(src, n);
    int *visited = bfs(n, adj, src);
    bool result = visited[not_src];
    free(visited);
    return result;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t > 0){
        t--;
        int n, m;
        scanf("%d %d", &n, &m);
        int adj[2*n][2*n];
        for (int i = 0; i < 2*n; i++)
            for (int j = 0; j < 2*n; j++)
                adj[i][j] = 0;
    
        for (int i = 0; i < m; i++) {
            int a, b;
            scanf("%d %d", &a, &b);
            addEdge(n, adj, a, b);
        }
    
        for (int i = 1; i <= n; i++) {
            if (unsatisfied(n, adj, i)) {
                printf("Unsatisfiable\n");
                return 0;
            }
        }
        printf("Satisfiable\n");
    }
}


