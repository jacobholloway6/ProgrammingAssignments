/* This program is to test specialcharcount function.
 * 
 */

#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<unistd.h> 
#include <stdbool.h> 
#include "count.h"


/*
 * This function prints the frequency stored in array charfreq[] to output screen.
 * Input: charfreq - array having the frequency of special characters
          size     - the total number of special characters
 * example:
 * a -> 20
 * b -> 30          
 */
void displayspecialcharfreq(long charfreq[], int size)
{	
	for(int i = 0; i < size; i++)
	  {
	  	switch(i)
	  	{
	  		case 0:
	  			printf(", -> %d\n", charfreq[i]);
	  			break;
	  		case 1:
	  			printf(". -> %d\n", charfreq[i]);
	  			break;
	  		case 2:
	  			printf(": -> %d\n", charfreq[i]);
	  			break;
	  		case 3:
	  			printf("; -> %d\n", charfreq[i]);
	  			break;
	  		case 4:
	  			printf("! -> %d\n", charfreq[i]);
	  			break;
	  	}	  	
	  }
}

int main()
{
	  char *path = "/home/cs/zhengli/cssc1729/programmingAssignments/projectzero/data";           // the path of the directory including the *.txt files to be processed
	  char *filetowrite = "/home/cs/zhengli/cssc1729/programmingAssignments/projectzero/result/specialresult.txt";    // the frequency of all alphabetical letters will be written in this file
	  
	  long charfreq[SPECIALCHARSIZE] = {0}; // array to store the frequency of 5 special characters
	  
	  specialcharcount(path, filetowrite, charfreq); // count the frequency of special characters and write into file
	  
	  displayspecialcharfreq(charfreq, SPECIALCHARSIZE); // print the array to output screen	  
}
