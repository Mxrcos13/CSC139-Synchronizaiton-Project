/*
 * Name: Marcos Pantoja & Daniela Perez 
 * Date: 11-06-2025
 * Purpose of Code: Simulates server processing client request.
 */

#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* consumer(void* arg) {

    int sync_type = *((int*)arg); // cast void to int

    for(int i = 0; i < num; i++){
        remove_request(sync_type); //sync type

        sleep(rand() % 3 + 1); // sleep 1–3 seconds
    }
    pthread_exit(NULL); // close thread

}