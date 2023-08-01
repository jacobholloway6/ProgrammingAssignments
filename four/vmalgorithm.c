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
   accessPattern = (int *)malloc(sizeof(int) * AccessPatternLength);
   printf("The randomized Access Pattern: ");
   for (i = 0; i < AccessPatternLength; i++)
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

   // TODO: fill the code to impelement FIFO replacement algorithm
   int i;
   int pageFault = 0;
   int pageIndex;
   int page;
   int j;
   int frameNum;

   // bee sure that we never go beyond the number of virtual page
   if (FrameNR > ReferenceSZ)
   {
      frameNum = ReferenceSZ;
   }
   else
   {
      frameNum = FrameNR;
   }

   // iterate over the pattern
   for (i = 0; i < AccessPatternLength; i++)
   {
      // get page number
      page = accessPattern[i];

      // try to find a physical page which this page is in at the moment
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

   return pageFault;
}

/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{

   // TODO: fill the code to impelement LRU replacement algorithm

   int i;
   int pageFault = 0;
   int pageIndex;
   int page;
   int j;
   int framaNum;
   int *registers;
   int logicalClock;
   int maxVal;

   if (FrameNR > ReferenceSZ)
   {
      framaNum = ReferenceSZ;
   }
   else
   {
      framaNum = FrameNR;
   }

   /**
    * Add a register to every page frame - contain the last time that
    * the page in that frame was accessed
    */
   registers = (int *)calloc(framaNum, sizeof(int));
   for (i = 0; i < framaNum; i++)
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
      // get page number
      page = accessPattern[i];

      // try to find a physical page which this page is in at the moment
      pageIndex = -1;
      for (j = 0; j < framaNum; j++)
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

         // find the least recent used slot
         memory.nextToReplaced = 0;

         // the life of page cannot be longer than AccessPatternLength
         maxVal = AccessPatternLength;
         for (j = 0; j < framaNum; j++)
         {
            if (registers[j] < maxVal)
            {
               memory.nextToReplaced = j;
               maxVal = registers[j];
            }
         }
         // update the slot
         memory.PageFrameList[memory.nextToReplaced] = page;
         // update its logical clock
         registers[memory.nextToReplaced] = logicalClock;
      }
      else
      {
         // update the logical time of this slot
         registers[pageIndex] = logicalClock;
      }
      // print the physical memory out
      for (j = 0; j < framaNum; j++)
      {
         printf("%3d", memory.PageFrameList[j]);
      }
      printf("\n");
   }

   // deallocate memory on heap
   free(registers);
   return pageFault;
}
