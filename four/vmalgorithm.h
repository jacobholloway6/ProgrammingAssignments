/********************************************
 * Page Replacement Simulation: header file
 *******************************************/

#include <stdio.h>
#include <stdlib.h>


/**************************************
 * The parameters of memory and disk pages 
 *
 * PageFrameList: The dynamically-allocated array representing memory pages
 * FrameNR: the number of page frames in memory
 * nextToReplaced: Point to the next page to be replaced
 *
 * accessPattern: The sequence of the demanding pages
 * AccessPatternLength: The length of the randomized access pattern
 * ReferenceSZ: the page number range of the access pattern
 *
 */

#define AccessPatternLength 20  // total number of memory access 

typedef struct
{
    int *PageFrameList;     // The dynamically-allocated array representing memory pages
    int nextToReplaced;	      // point to the next frame to be replaced
}PageFrame;



/*
 * The following global variables will be used in the program, please understand each of them before starting your coding ... 
 */


extern int *accessPattern;        // memory access pattern, for example: 4 2 2 0 1   means will access the page 4, 2, 2, 0 and 1 one by one in order


extern int ReferenceSZ;           // range of pages to be accssed
extern int FrameNR;               // the number of page frames in memory

extern PageFrame memory;          // representing the memory


/* Algorithm Functions */

extern int FIFO();

extern int LRU();