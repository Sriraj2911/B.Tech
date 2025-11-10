#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>


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

#endif