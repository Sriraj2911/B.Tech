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