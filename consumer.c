#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* consumer(void* arg) {

    int sync_type = *((int*)arg); // cast void to int

    for(int i = 0; i < num; i++){
        remove_request(sync_type); //sync type
    }
    pthread_exit(NULL); // close thread

}