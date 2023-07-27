/*
 * The code is not part of the real application, and just used to 
 * illustrate the bounded-buffer problem using Semaphore and/or mutexes. 
 * Detailed requirements please refer to the assignment documentation.
 * 
 */
#include "bbuffer.h"


    buffer_t buffer;
	pthread_t consumer_tid[CONSUMERS];
	pthread_t producer_tid[PRODUCERS];
	pthread_mutex_t mutex;
	sem_t full, empty;

void initilization() {
    /* TODO: intialize golbal variables if you need, such as semaphore, mutex and etc. Leave it empyty if you
     * do not need it.
     */

    pthread_mutex_t mutex;
    sem_t full, empty;
    // set up mutex lock
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, // the flag
            0, // share the flag among thread
            BUFFER_SIZE // the flag is 0 when the buffer is empty
            // we reduces the value of full when adding new item to buffer
            );
    sem_init(&empty, // the flag
            0, // share the flag among thread
            0 // the flag is 0 when the buffer is empty
            );
    buffer.next_in = 0;
    buffer.next_out = 0;
    buffer.size = 0;

}

/* *
 * insert_item - thread safe(?) function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */

int insert_item(int item, long int id) {
    /* TODO: Check and wait if the buffer is full. Ensure exclusive
     * access to the buffer and may use the existing code to insert an item.
     */
    pthread_mutex_lock(&mutex);
    do{
        pthread_mutex_unlock(&mutex);
        
        /*
         * block the thread until the value of full is greater than 0
         * aka until the buffer is not full
         * or
         * until a consumer removes an item from the buffer 
         */
        sem_wait(&full);
        
        /**
         * lock to check the condition of th buffer
         */
        pthread_mutex_lock(&mutex);
        
        /*
         *  continue to the next loop if 
         *  another producer has just inserted an item to buffer 
         *  and made it full again
         */
    }while(buffer.size >= BUFFER_SIZE);
    
    /**
     * insert new item to the buffer 
     */
    buffer.value[buffer.next_in] = item;
    buffer.size++;

    printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
    buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE;

    // release the lock
    pthread_mutex_unlock(&mutex);
    
    /**
     * increase value of empty
     * to tell consumers that there is an item to be removed
     */
    sem_post(&empty);
    return 0;
}

/**
 * remove_item - thread safe(?) function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id) {
    /* TODO: Check and wait if the buffer is empty. Ensure exclusive
     * access to the buffer and use the existing code to remove an item.
     */
    pthread_mutex_lock(&mutex);

    do {
        pthread_mutex_unlock(&mutex);
        /**
         * block the thread until the value of empty is greater than 0
         * aka until the buffer is not empty
         * or
         * until a producer inserts an item to the buffer 
         */
        sem_wait(&empty);
        
        /**
         * lock to check the condition of th buffer
         */
        pthread_mutex_lock(&mutex);
        
        /*
         *  continue to the next loop if 
         *  another consumer has just remove the last item from buffer 
         *  and made it empty again
         */
    } while (buffer.size <= 0);

    /*
     * remove item from buffer
     */
    *item = buffer.value[buffer.next_out];
    buffer.value[buffer.next_out] = -1;
    buffer.size--;

    printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out);

    buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE;

    // release the lock
    pthread_mutex_unlock(&mutex);
    
    /**
     * increase value of full
     * to tell producers that there is another empty slot to be filled
     */
    sem_post(&full);

    return 0;
}

/**
 * producer - will iterate PRODUCER_ITERATION times and call the corresponding
 * function to insert an integer to the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple producer threads
 * @return nothing
 */
void * producer(void *param) {
    int item, i;
    long int id = (long int) param;

    printf("producer %ld started!\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) {
        sleep(rand() % 3);

        item = rand() % 10000;
        if (insert_item(item, id))
            printf("Error while inserting to buffer\n");
    }

    pthread_exit(0);
}

/**
 * consumer - will iterate CONSUMER_ITERATION times and call the corresponding
 * function to remove an integer from the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple consumer threads
 * @return nothing
 */
void * consumer(void *param) {
    int item, i;
    long int id = (long int) param;

    printf("consumer %ld started!\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--) {
        sleep(rand() % 3);

        if (remove_item(&item, id))
            printf("Error while removing from buffer\n");
    }

    pthread_exit(0);
}