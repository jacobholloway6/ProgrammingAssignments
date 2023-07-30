/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file 
 */

#include "vmalgorithm.h"

int *accessPattern;
int ReferenceSZ; 
int FrameNR;
PageFrame memory;

/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("The randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
   int i;
   memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    // dynamic allocated FrameNR frames to be used in memory
   memory.nextToReplaced =0;          // indicate the new frame to be replaced as 0
   for(i=0; i< FrameNR; i++)
   {
			memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused 
   }

}

// Print the pages loaded in memory
void printPageFrame()
{
   int i;
   for(i=0; i< FrameNR; i++)
   {
			printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}


/*
 *  Print the access pattern in order
 */
void printAccessPattern()
{
   int i;
   printf("The Same Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");

}


/*
 * Return: number of the page fault using FIFO page replacement algorithm
 */
int FIFO()
{
   
   //TODO: fill the code to impelement FIFO replacement algorithm 
   
   
}



/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{

    //TODO: fill the code to impelement LRU replacement algorithm 

}

