#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num = 5;

void* producer(void* arg) {

    int sync_type = *((int*)arg); // cast void to int

    for(int i; i < num; i++){
        insert_request(i + 1, sync_type); // request number and sync type
    }
    
    pthread_exit(NULL); // close thread

}