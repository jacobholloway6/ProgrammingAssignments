/* This file is to test your program#2.
 * 
 */

#include <stdio.h> 
#include <dirent.h> 
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h> 
#include <stdbool.h> 
#include <time.h>
#include "count.h"



/*
 * Print the frequencies of alphabetical characters stored in array: charfreq[] to output screen in the format as:
 * letter -> frequency (one letter a line)
 * Input: charfreq - array having the frequency of each alphabet letter
          size     - the total number of alphabet letters 
 * example:
 * a -> 20 
 * b -> 30 
 */
 
void displayalphabetfreq(long charfreq[], int size)
{	
	 
	for(int i = 0; i < size; i++)
	  {
	  	printf("%c -> %d\n", (char)(i+97), charfreq[i]);
	  }
}

int main(int argc, char *argv[]) {

	
	time_t currentTime;
	time(&currentTime);
    char *timeString = ctime(&currentTime);


    if (argc < 2) {
        printf("Please enter 2 arguments only eg.\"./testmulthreads #_of__threads!!\"\n");
        return 1;
    }

    int num_threads = atoi(argv[1]);
	  
	  char *path = "/Users/jacobholloway/Developer/CS480Assignments/ProgrammingAssignments/Pzero/data";           // the data *.txt files are under this folder
	  char *filetowrite = "/Users/jacobholloway/Developer/CS480Assignments/ProgrammingAssignments/two/result/filetowrite.txt";    // the frequency of all alphabetical letters will be written in this file
	  
	  long alphabetfreq[ALPHABETSIZE] = {0}; // array to store the frequency of each alphablet letter, which should be alway up-to-date;
	  
	  
	  alphabetcountmulthreads(path, filetowrite, alphabetfreq, num_threads);  // process the data files using mutiple threads
	  
	  printf("\nTask was completed on : %s \n", timeString);
	  printf("The results are counted as follows : \n\n");
	  
	  
	  displayalphabetfreq(alphabetfreq, ALPHABETSIZE);  // print the frequency stored in the array to output screen
}
