#include <pthread.h>
#include <semaphore.h>

// synchronization primitives
extern pthread_mutex_t mutex;
extern pthread_cond_t cond_full;
extern pthread_cond_t cond_empty;
extern sem_t sem_full;
extern sem_t sem_empty;

#define BUFFER_SIZE 5

// function proto types
void insert_request(int request, int sync_type);
int remove_request(int sync_type);
