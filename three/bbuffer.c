/*
 * The code is not part of the real application, and just used to
 * illustrate the bounded-buffer problem using Semaphore and/or mutexes.
 * Detailed requirements please refer to the assignment documentation.
 *
 */
#include "bbuffer.h"

//Variables are all pulled from the Header file that uses the extern classification

buffer_t buffer; // Used as a holding place between consumers and prodcuers
pthread_t consumer_tid[CONSUMERS];
pthread_t producer_tid[PRODUCERS];
pthread_mutex_t mutex; // Establishes a lock on threads
sem_t full, empty;

void initilization()
{
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, BUFFER_SIZE);
    sem_init(&empty, 0, 0);
    buffer.next_in = 0;
    buffer.next_out = 0;
    buffer.size = 0;
}

/* *
 * insert_item - thread safe(?) function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */

int insert_item(int item, long int id) // Waits until there is a free slot in the buffer and then will add it if there is no lock or buffer is not full
{
    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    buffer.value[buffer.next_in] = item;
    buffer.size++;
    printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
    buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    return 0;
}

/**
 * remove_item - thread safe(?) function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id) // Pulls from the buffer and will decrement until it gets to zero. 
{
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);

    *item = buffer.value[buffer.next_out];
    buffer.value[buffer.next_out] = -1;
    buffer.size--;
    printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out);
    buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);
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
void *producer(void *param) // Creates an item and adds it to the buffer
{
    int item, i;
    long int id = (long int)param;

    printf("producer %ld started!\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) // decrements until there is nothing left in PRODUCER_ITERATIONS
    {
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
void *consumer(void *param) // Takes an item from the buffer and decrements until it is finished in the while loop.
{
    int item, i;
    long int id = (long int)param;

    printf("consumer %ld started!\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--)
    {
        sleep(rand() % 3);

        if (remove_item(&item, id))
            printf("Error while removing from buffer\n");
    }

    pthread_exit(0);
}