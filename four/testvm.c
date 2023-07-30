#include "vmalgorithm.h"

int main(int argc, char* argv[])
{
	  int testmode = 0;
 
    if( argc != 3 )
    {
        printf("Please type the command again, following the format as: ./testvm  <reference page range> <number of memory frames>\n");
        return -1;
    }

   
    ReferenceSZ = atoi(argv[1]);
    FrameNR = atoi(argv[2]);
    
    
    /**** If you need more self-testing, please:
    
      1) uncomment generateAccessPattern() - line 24
      2) comment out line 29 - line 33
     ****/
    
    //generateAccessPattern();   // Please uncomment the following line for more self-testing
        
    /*
     * Please comment out the following five lines for more self-testing
     */
    testmode = 1;
    int pattern[20] = {5,2,2,0,4,6,4,4,1,3,4,5,0,4,5,6,2,0,0,1};
    accessPattern = pattern;
    /********************************************************************************************/
   

   initializePageFrame();
   printf("Running program using FIFO algorithm ... ...\n");
   printf("page fault of FIFO: %d\n",FIFO());
   free(memory.PageFrameList);

   printf("\n");
   printf("\n");

   
   printAccessPattern();   // print the access pattern again ...

   initializePageFrame();
   printf("Running program using LRU algorithm ... ...\n");
   printf("page fault of LRU: %d\n",LRU());
   free(memory.PageFrameList);


   if (testmode == 0)
        free(accessPattern);	

   return 0;

}
