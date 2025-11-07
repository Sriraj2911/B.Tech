#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    int *data;
    int front, rear, count;
}Queue;

void initQ(Queue *q){
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

bool isEmptyQ(Queue *q){
    return (q->count == 0);
}

bool isFullQ(Queue *q, int n){
    return (q->count == n);
}

void enqueue(Queue *q, int ele, int n){
    if(isFullQ(q, n)){
        // printf("Queue overflow!\n");
        return;
    }
    q->data[q->rear] = ele;
    q->rear = (q->rear+1)%n;
    q->count++;
}

int dequeue(Queue *q, int n){
    if(isEmptyQ(q)){
        // printf("Queue underflow!\n");
        return -1;
    }
    int val = q->data[q->front];
    
    q->front = (q->front + 1)%n;
    q->count--;
    return val;
}

void addEdge(int n, int adj[n][n], int a, int b){
    // adj[][] is a nxn matrix
    // a and b are assumed to be <=n
    adj[a-1][b-1] = 1;
    adj[b-1][a-1] = 1;
}

typedef struct{
    int value, length;
}Vertex;

Vertex* bfs(int n, int adj[n][n], int src) {
    int *visited = calloc(n, sizeof(int));
    Queue *q = malloc(sizeof(Queue));
    initQ(q);

    enqueue(q, src, n);
    Vertex *vertices = malloc(sizeof(Vertex)*n);
    vertices[src-1].value = src;
    vertices[src-1].length = 0;
    visited[src-1] = 1;

    while (q->front < q->rear) {
        int curr = dequeue(q, n);
        for (int i = 0; i < n; i++) {
            if (adj[curr-1][i] && !visited[i]) {
                vertices[i].value = i + 1;
                vertices[i].length = vertices[curr-1].length + 1;
                visited[i] = 1;
                enqueue(q, i, n);
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
    for(int i=0; i<m; i++){
        scanf("%d %d", arr, arr+1);
        addEdge(n, adj, arr[0], arr[1]);
    }
    int src;
    scanf("%d", &src);
    Vertex *vertices = bfs(n, adj, src);

    for(int i=0; i<n; i++){
        printf("Vertex %d: Length = %d", vertices[i].value, vertices[i].length);
    }
}
