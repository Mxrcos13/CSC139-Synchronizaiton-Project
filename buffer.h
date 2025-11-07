/*
 * Name: Marcos Pantoja & Daniela Perez 
 * Date: 11-06-2025
 * Purpose of Code: Defines global variables and prototypes.
 */

#include <pthread.h>
#include <semaphore.h>

// synchronization primitives
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_full;
extern pthread_cond_t cond_empty;
extern sem_t sem_full;
extern sem_t sem_empty;

#define BUFFER_SIZE 5

// num of requests CHANGE LATTER
extern int num;

// function prototypes
void insert_request(int request, int sync_type);
int remove_request(int sync_type);
