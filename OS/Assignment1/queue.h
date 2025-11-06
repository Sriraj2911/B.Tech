#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define n 10

typedef struct{
    int data[n];
    int front, rear, count;
}Queue;

void initQ(Queue *q);
bool isEmptyQ(Queue *q);
bool isFullQ(Queue *q);
void addQ(Queue *q, int ele);
int deleteQ(Queue *q);
int frontQ(Queue *q);

#endif