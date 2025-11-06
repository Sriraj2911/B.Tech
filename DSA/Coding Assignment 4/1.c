#include <stdio.h>
#include <stdbool.h>

// #define n 10

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

void addQ(Queue *q, int ele, int n){
    if(isFullQ(q, n)){
        printf("Queue overflow!\n");
        return;
    }
    q->data[q->rear] = ele;
    q->rear = (q->rear+1)%n;
    q->count++;
}

int deleteQ(Queue *q, int n){
    if(isEmptyQ(q)){
        printf("Queue underflow!\n");
        return -1;
    }
    int val = q->data[q->front];
    
    q->front = (q->front + 1)%n;
    q->count--;
    return val;
}

