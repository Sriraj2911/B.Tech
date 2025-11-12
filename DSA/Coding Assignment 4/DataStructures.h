#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

//////////////////////// QUEUE ///////////////////////////
typedef struct{
    int *data;
    int front, rear, count;
}Queue;

void initQ(Queue *q, int n);
bool isEmptyQ(Queue *q);
bool isFullQ(Queue *q, int n);
void enqueue(Queue *q, int ele, int n);
int dequeue(Queue *q, int n);
void printQ(Queue q, int n);

////////////////////// VECTOR ///////////////////////////
typedef struct {
    void *data;         // pointer to the array
    size_t elementSize; // size of each element
    size_t size;        // number of elements used
    size_t capacity;    // allocated capacity
} Vector;

Vector* initVector(Vector* v, size_t elementSize);
void push_back(Vector* v, void* element);
void *get(Vector *v, size_t index);
void freeVector(Vector* v);

////////////////////// EDGE HEAP ///////////////////////////
typedef struct{
    int u, v; // Vertices at the two ends of the edge
    int w; // Weight of the edge
}Edge;

void swapEdge(Edge* a, Edge* b);
void heapifyEdge(Edge* arr, int n);
Edge deleteMinEdge(Edge* arr, int n);
void buildEdgeHeap(Edge* arr, int n);

#endif