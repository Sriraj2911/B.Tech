#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct{
    int *data;
    int front, rear, count;
}Queue;

void initQ(Queue *q, int n){
    q->data = malloc(sizeof(int)*n);
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
        return;
    }
    q->data[q->rear] = ele;
    q->rear = (q->rear+1)%n;
    q->count++;
}

int dequeue(Queue *q, int n){
    if(isEmptyQ(q)){
        return -1;
    }
    int val = q->data[q->front];
    
    q->front = (q->front + 1)%n;
    q->count--;
    return val;
}

void printQ(Queue q, int n){
    while(!isEmptyQ(&q)){
        printf("%d ", dequeue(&q, n));
    }
    printf("\n");
}

typedef struct{
    int u, v; // Vertices at the two ends of the edge
    int w; // Weight of the edge
}Edge;

typedef struct{
    Edge *data; // Pointer to elements
    size_t size; // Number of elements in vector
    size_t capacity; // Allocated capacity
}Vector;

// Create an empty vector
void initVector(Vector* vector, int capacity){
    vector->data = malloc(sizeof(Edge)*capacity);
    vector->size = 0;
    vector->capacity = capacity;
}

// Add an element at the end
void push_back(Vector* vector, Edge edge){
    if(vector->size == vector->capacity){
        vector->capacity = vector->capacity ? vector->capacity*2 : 1;
        vector->data = realloc(vector->data, vector->capacity * sizeof(Edge));
    }
    vector->data[vector->size++] = edge;
}

void freeVector(Vector* vector){
    free(vector->data);
}


void swapEdge(Edge* a, Edge* b){
    Edge temp = *a;
    *a = *b; 
    *b = temp;
}

void heapify(Edge* arr, int n){
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;

        if (left < n && arr[left].w < arr[smallest].w)
            smallest = left;
        if (right < n && arr[right].w < arr[smallest].w)
            smallest = right;

        if (smallest != i) {
            swapEdge(&arr[i], &arr[smallest]);
            i = smallest;
        } else break;
    }
}

Edge deleteMin(Edge* arr, int n){
    Edge min = arr[0];
    swapEdge(&arr[0], &arr[n-1]);
    heapify(arr, n-1); // Heapify only the valid part
    return min;
}

void buildHeap(Edge* arr, int n){
    for (int i = n/2 - 1; i >= 0; i--) {
        int idx = i;
        while (1) {
            int left = 2*idx + 1;
            int right = 2*idx + 2;
            int smallest = idx;

            if (left < n && arr[left].w < arr[smallest].w)
                smallest = left;
            if (right < n && arr[right].w < arr[smallest].w)
                smallest = right;

            if (smallest != idx) {
                swapEdge(&arr[idx], &arr[smallest]);
                idx = smallest;
            } else break;
        }
    }
}