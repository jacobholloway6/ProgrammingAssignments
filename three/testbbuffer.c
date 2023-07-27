
/*
*  This file is to test the bounded buffer program.  
*  
*/

#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<unistd.h> 
#include <stdbool.h> 
#include <pthread.h>
#include "bbuffer.h"

int main()
{
    long int i;

    srand(time(NULL));
   
    /*
     * Initialize global varabiles
     */
    initilization();

    /* Create the consumer threads */
    for (i = 0; i < CONSUMERS; i++)
    {
			if (pthread_create(&consumer_tid[i], NULL, consumer, (void *)i) != 0) {
	    	perror("pthread_create");
	    	abort();
			}				
		}
    
    /* Create the producer threads */
    for (i = 0; i < PRODUCERS; i++)
			if (pthread_create(&producer_tid[i], NULL, producer, (void *)i) != 0) {
	    		perror("pthread_create");
	    abort();
		}

    /* Wait for them to complete */
    for (i = 0; i < CONSUMERS; i++)
			if (pthread_join(consumer_tid[i], NULL) != 0) {
	    	perror("pthread_join");
	    	abort();
		}
		
    for (i = 0; i < PRODUCERS; i++)
			if (pthread_join(producer_tid[i], NULL) != 0) {
	    	perror("pthread_join");
	    	abort();
		}

    return 0;
}
