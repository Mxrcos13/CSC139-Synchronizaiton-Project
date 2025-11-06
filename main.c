#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* producer(void* arg);
void* consumer(void* arg);
int num; // num of request


int main(int argc, char* argv[]) {
    pthread_t producer_thread, consumer_thread;

    int sync_type = 3; // choose which sync type 
    num = 5; // default num of requests

    if (argc > 1) {
        sync_type = atoi(argv[1]); // convert string arg to int
    }

    if (argc > 2) {
        num = atoi(argv[2]); // read number of requests, convert to int 
    }

    // error checking for invalid input 
    if (sync_type < 1 || sync_type > 3) {
        printf("Invalid sync type. Use:\n");
        printf("1 = Mutex only\n2 = Condition Variables\n3 = Semaphores\n");
        return 1;
    }

    // error checking num of requests 
    if (num <= 0) {
        printf("Invalid number of requests. Must be greater than 0.\n");
        return 1;
    }

    // display which method selected
    if (sync_type == 1){
        printf("Using Mutex Synchronization...\n");
    } 
    else if (sync_type == 2){
        printf("Using Condition Variables Synchronization...\n");
    } 
    else{
        printf("Using Semaphores Synchronization...\n");
    }

    // initialize synchronization primitives
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_full, NULL);
    pthread_cond_init(&cond_empty, NULL);
    sem_init(&sem_full, 0, 0);
    sem_init(&sem_empty, 0, BUFFER_SIZE);

    //create threads
    pthread_create(&producer_thread, NULL, producer, &sync_type);
    pthread_create(&consumer_thread, NULL, consumer, &sync_type);

    // wait for threads to finish
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("Finished successfully.\n");
    return 0;

}