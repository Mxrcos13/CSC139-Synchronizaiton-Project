#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* producer(void* arg);
void* consumer(void* arg);
int num = 5; // num of request USE ARGUEMTN VARS


int main() {
    pthread_t producer_thread, consumer_thread;

    int sync_type = 3; // change this to take arguments

    // Initialize synchronization primitives
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);
    sem_init(&sem_full, 0, 0);
    sem_init(&sem_empty, 0, BUFFER_SIZE);

    //create threads
    pthread_create(&producer_thread, NULL, producer, &sync_type);
    pthread_create(&consumer_thread, NULL, consumer, &sync_type);

    // wait fro threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Finished successfully.\n");
    return 0;

}