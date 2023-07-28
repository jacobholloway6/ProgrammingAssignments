/*
 *  This header file is for programming #3.  
 *  You may need to add more comments to explain your code ... 
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <semaphore.h>

#define BUFFER_SIZE 5   // rounded buffer size

#define PRODUCERS 3  // number of producers
#define CONSUMERS 5  // number of consumers

#define ITERATIONS 30   // number of actions producers/consumers perform 
#define PRODUCER_ITERATIONS (ITERATIONS / PRODUCERS)  //number of actions each producer performs
#define CONSUMER_ITERATIONS (ITERATIONS / CONSUMERS) //number of actions each consumer performs

typedef struct {
    int value[BUFFER_SIZE];
    int next_in, next_out, size;
} buffer_t;    // struct of bounded buffer


extern buffer_t buffer;   //global variable: rounded buffer


extern pthread_t consumer_tid[CONSUMERS]; // producer threads
extern pthread_t producer_tid[PRODUCERS]; // consumer threads

extern pthread_mutex_t mutex;
extern sem_t full, empty;


void * producer(void *param);
void * consumer(void *param);
void initilization();





