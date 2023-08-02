/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file
 */

#include "vmalgorithm.h"

int FrameNR;        // Frame Number
int ReferenceSZ;    // Reference Size
int *accessPattern; // Access Pattern
PageFrame memory;

/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc(sizeof(int) * AccessPatternLength); // Allocates memory dynamically for the array & each element is the size of an integer

   if(&malloc == NULL){
      printf("Memory was not allocated successfully. \n"); // Validates that memory allocation was successful
      exit -1;
   }

   printf("The randomized Access Pattern: "); // Provides terminal output of the random access pattern that was generated using the srand(time) function
   for (i = 0; i < AccessPatternLength; i++)
   {
      accessPattern[i] = rand() % ReferenceSZ; // For each index, generate a random number which represents a page to be accessed
      printf("%d ", accessPattern[i]); // Random number is stored at accessPattern
   }
   
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
   int i;

   // Allocates memory dynamically for the array 'PageFrameList' in 'memory' of size 'FrameNR'
   // This represents the memory frames to hold the pages
   memory.PageFrameList = (int *)malloc(sizeof(int) * FrameNR); // dynamic allocated FrameNR frames to be used in memory
   memory.nextToReplaced = 0;                                   // indicate the new frame to be replaced as 0
   for (i = 0; i < FrameNR; i++)
   {
      memory.PageFrameList[i] = -1; // initialization to -1 indicating all frames are unused
   }
}

// Print the pages loaded in memory

void printPageFrame()
{
   int i;
   for (i = 0; i < FrameNR; i++)
   {
      // Sets the value of each frame to -1, indicating that the frame is initially unused
      // This assumes that valid page numbers are non-negative
      printf("%2d ", memory.PageFrameList[i]);
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
   for (i = 0; i < AccessPatternLength; i++)
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

   
   int i;
   int pageFault = 0;
   int pageIndex;
   int page;
   int j;
   int frameNum;

   // Ensures that the number of frames does not exceed the number of virtual pages
   // be sure that we never go beyond the number of virtual page
   if (FrameNR > ReferenceSZ)
   {
      frameNum = ReferenceSZ;
   }
   else
   {
      frameNum = FrameNR;
   }

   // iterate over access pattern which is the sequence of page accesses
   for (i = 0; i < AccessPatternLength; i++)
   {
      // get page number
      page = accessPattern[i];

      // Attempt to find the page in memory (within page frame list)
      // If found, pageIndex will hold the index at which the page was found
      // If not found, pageIndex will remain as -1
      pageIndex = -1;
      for (j = 0; j < frameNum; j++)
      {
         if (page == memory.PageFrameList[j])
         {
            pageIndex = j;
            break;
         }
      }

      // the physical page is not found
      // there is a page fault
      if (pageIndex < 0)
      {
         pageFault++;
         // fill the page in the chosen slot
         memory.PageFrameList[memory.nextToReplaced] = page;
         // update the index of the next chosen slot
         memory.nextToReplaced = (memory.nextToReplaced + 1) % frameNum;
      }
      // print the physical memory out
      for (j = 0; j < frameNum; j++)
      {
         printf("%3d", memory.PageFrameList[j]);
      }
      printf("\n");
   }
   
   // Return the total number of page faults that have occurred. 
   return pageFault;
}

/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{

   int i;
   int pageFault = 0;
   int pageIndex;
   int page;
   int j;
   int frameNum = (FrameNR > ReferenceSZ) ? ReferenceSZ : FrameNR;
   int *registers = NULL;
   int logicalClock = 0;
   int maxVal;

   
// Ensures that the number of frames do not exceed the number of virtual pages
   if (FrameNR > ReferenceSZ)
   {
      frameNum = ReferenceSZ;
   }
   else
   {
      frameNum = FrameNR;
   }

   /**
    * Add a register to every page frame - contain the last time that
    * the page in that frame was accessed
    */
   
   // Allocate an array of registers, one for each frame
   // Each register keeps track of the "logical time" the page in the corresponding frame was last accessed
   registers = (int *)calloc(frameNum, sizeof(int));
   for (i = 0; i < frameNum; i++)
   {
      registers[i] = 0;
   }

   /**
    * Use a "logical clock" that advance by 1 tick each time
    * a memory reference is made
    */
   logicalClock = 0;

   for (i = 0; i < AccessPatternLength; i++)
   {
      // Each time a page is referenced, update its register
      logicalClock++;
      // get page number from the access pattern
      page = accessPattern[i];

      // Try to find a physical page in memory in the page list
      pageIndex = -1;
      for (j = 0; j < frameNum; j++)
      {
         if (page == memory.PageFrameList[j])
         {
            pageIndex = j;
            break;
         }
      }

      // the physical page is not found
      // there is a page fault
      if (pageIndex < 0)
      {
         pageFault++;

         // Find the frame with the oldest (smallest) logical time
         // This will be the least recently used frame
         memory.nextToReplaced = 0;

         // the life of page cannot be longer than AccessPatternLength
         maxVal = AccessPatternLength;
         for (j = 0; j < frameNum; j++)
         {
            if (registers[j] < maxVal)
            {
               memory.nextToReplaced = j;
               maxVal = registers[j];
            }
         }
         // Replaces the least recently used fram with the new page frame
         memory.PageFrameList[memory.nextToReplaced] = page;
         // update its logical clock
         registers[memory.nextToReplaced] = logicalClock;
      }
      else
      {
         // update the logical time of this slot if the page was found in memory 
         registers[pageIndex] = logicalClock;
      }
      // print the physical memory out
      for (j = 0; j < frameNum; j++)
      {
         printf("%3d", memory.PageFrameList[j]);
      }
      printf("\n");
   }

   // deallocates memory on heap
   free(registers);
   return pageFault;
}
