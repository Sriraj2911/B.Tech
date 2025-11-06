#include <stdio.h>
#include <stdbool.h>

#define n 10

typedef struct{
    int data[n];
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

bool isFullQ(Queue *q){
    return (q->count == n);
}

void addQ(Queue *q, int ele){
    if(isFullQ(q)){
        printf("Queue overflow!\n");
        return;
    }
    q->data[q->rear] = ele;
    q->rear = (q->rear+1)%n;
    q->count++;
}

int deleteQ(Queue *q){
    if(isEmptyQ(q)){
        printf("Queue underflow!\n");
        return -1;
    }
    int val = q->data[q->front];
    
    q->front = (q->front + 1)%n;
    q->count--;
    return val;
}

// Returns the front element without deleting it
int frontQ(Queue *q){
    if(isEmptyQ(q)){
        printf("Queue is empty\n");
        return -1;
    }
    return q->data[q->front];
}