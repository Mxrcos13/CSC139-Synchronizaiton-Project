#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// shared variables
int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

//synchronization primitives
pthread_mutex_t mutex;
pthread_cond_t cond_full;
pthread_cond_t cond_empty;
sem_t sem_full;
sem_t sem_empty;

void insert_request(int request, int sync_type) {

    if (sync_type == 1) { // mutex only

        pthread_mutex_lock(&mutex);
        buffer[in] = request;
        printf("Mutex request");
        in++;
        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 2){ // condition variables

        pthread_mutex_lock(&mutex);
        while ((in + 1) % BUFFER_SIZE == out) { // Buffer full
            pthread_cond_wait(&cond_empty, &mutex);
        }
        buffer[in] = request;
        printf("Mutex request");
        in++;
        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 3){ // semaphores

    }
    else{
        printf("Invalud Request");
        exit(1);
    }

}

int remove_request(int sync_type) {
    
    if (sync_type == 1) { // mutex only

    }else if(sync_type == 2){ // condition variables
        
    }else if(sync_type == 3){ // semaphores

    }
    else{
        printf("Invalud Request");
        exit(1);
    }
}