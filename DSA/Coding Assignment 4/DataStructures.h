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
typedef struct{
    int u, v; // Vertices at the two ends of the edge
    int w; // Weight of the edge
}Edge;

typedef struct{
    Edge *data; // Pointer to elements
    size_t size; // Number of elements in vector
    size_t capacity; // Allocated capacity
}Vector;

Vector* initVector(Vector* vector, int capacity);
void push_back(Vector* vector, Edge edge);
void freeVector(Vector* vector);

////////////////////// HEAP ///////////////////////////
void swapEdge(Edge* a, Edge* b);
void heapify(Edge* arr, int n);
Edge deleteMin(Edge* arr, int n);
void buildHeap(Edge* arr, int n);

#endif