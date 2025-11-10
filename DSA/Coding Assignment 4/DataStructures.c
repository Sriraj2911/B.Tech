#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//////////////////////////// QUEUE ////////////////////////////////////
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

////////////////////////// VECTOR /////////////////////////////////////////
typedef struct{
    int *data; // Pointer to elements
    size_t size; // Number of elements in vector
    size_t capacity; // Allocated capacity
}Vector;

// Create an empty vector
Vector* create_vector(){
    Vector* vector = malloc(sizeof(Vector));
    vector->data = NULL;
    vector->size = 0;
    vector->capacity = 0;
    return vector;
}

// Add an element at the end
void push_back(Vector* vector, int value){
    if(vector->size == vector->capacity){
        vector->capacity = vector->capacity ? vector->capacity*2 : 1;
        vector->data = realloc(vector->data, vector->capacity * sizeof(int));
    }
    vector->data[vector->size++] = value;
}

// Get element at index
int vector_at(Vector* vector, size_t index){
    if(index >= vector->size){
        return -1;
    }
    return vector->data[index];
}