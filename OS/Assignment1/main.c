#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "queue.h"

Queue q;
pthread_mutex_t lock;

void* producer(void* arg){
    while(1){
        int num = rand() % 100; // Random integer between 0 and 99

        pthread_mutex_lock(&lock); // Lock the mutex, so that only producer touches the queue
        if(!isFullQ(&q)){
            addQ(&q, num);
            printf("Produced: %d\n", num);
        }
        else{
            printf("Queue full, producer waiting...\n");
        }
        pthread_mutex_unlock(&lock); // Unlock the mutex, so that now consumer can access the queue

        usleep(rand()%1000000);
    }
    return NULL;
}

void* consumer(void* arg){
    while(1){
        pthread_mutex_lock(&lock); // Lock the mutex, so that only consumer touches the queue
        if(!isEmptyQ(&q)){
            int num = deleteQ(&q);
            printf("Consumed: %d\n", num);
        }
        else{
            printf("Queue empty, consumer waiting...\n");
        }
        pthread_mutex_unlock(&lock); // Unlock the mutex, so that now producer can access the queue

        usleep(rand()%1000000);
    }
    return NULL;
}

int main(){
    pthread_t p, c;

    initQ(&q);
    pthread_mutex_init(&lock, NULL);
    // Create the producer and consumer threads
    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    // This part of the code is not accessed due to the infinite loop in producer() and consumer()
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&lock);

    return 0;
}