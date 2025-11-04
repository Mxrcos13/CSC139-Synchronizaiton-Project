#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// shared variables
int buffer[5];
int in = 0;
int out = 0;

//synchronization primitives
pthread_mutex_t mutex;
pthread_cond_t cond_full;
pthread_cond_t cond_empty;
sem_t sem_full;
sem_t sem_empty;

void insert_request(int request, int sync_type) {
    if (sync_type == 1) { // Mutex only

    }else if(sync_type == 2){ // Condition Variables
        
    }else if(sync_type == 3){ // Semaphores

    }
    else{
        printf("Invalud Request");
        exit(1);
    }

}

int remove_request(int sync_type) {

}