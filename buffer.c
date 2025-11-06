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
        
        if((in + 1) % BUFFER_SIZE == out){
            printf("Buffer full! Producer skipping request #%d\n", request);
        }
        else{
            buffer[in] = request;
            printf("Mutex produce request #%d\n", request);
            in = (in + 1) % BUFFER_SIZE;
        }

        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 2){ // condition variables

        pthread_mutex_lock(&mutex);
        while ((in + 1) % BUFFER_SIZE == out) { // Buffer full
            pthread_cond_wait(&cond_empty, &mutex);
        }
        buffer[in] = request;
        printf("Conditional Variable produce request #%d\n", request);
        in = (in + 1) % BUFFER_SIZE;
        pthread_cond_signal(&cond_full); 
        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 3){ // semaphoreproduce s
        sem_wait(&sem_empty);
        buffer[in] = request;
        printf("Semphore produce request #%d\n", request);
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&sem_full);
    }

    else{
        printf("Invalid produce Request\n");
        exit(1);
    }

}

int remove_request(int sync_type) {
    int request;
    if(sync_type == 1){
        pthread_mutex_lock(&mutex);

        if ((in == out)){
            printf("Buffer empty! Consumer waiting (Mutex-only mode)\n");
            request = -1; // return dummy value
        }
        else{
            request = buffer[out];
            printf("Mutex consume request #%d\n", request);
            out = (out + 1) % BUFFER_SIZE;
        }

        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 2){ // condition variables

        pthread_mutex_lock(&mutex);
        while (in == out) { // Buffer empty
            pthread_cond_wait(&cond_full, &mutex);
        }
        request = buffer[out];
        printf("Conditional Variable consume request #%d\n", request);
        out = (out + 1) % BUFFER_SIZE;
        pthread_cond_signal(&cond_empty);
        pthread_mutex_unlock(&mutex);

    }else if(sync_type == 3){ // semaphores
        sem_wait(&sem_full);
        request = buffer[out];
        printf("Semphore consume request #%d\n", request);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&sem_empty);
    }
    else{
        printf("Invalid consume Request\n");
        exit(1);
    }
    return request;
}