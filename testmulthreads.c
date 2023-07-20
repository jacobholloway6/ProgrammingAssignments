/* This file is to test your program#2.
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

int main(int argc, char *argv[])
{
	
	  printf("Please enter 2 arguments only eg.\"./testmulthreads #_of__threads!!\"\n");
	  
	  int num_threads = atoi(argv[1]);  
	  
	  char *path = "../data";           // the data *.txt files are under this folder
	  char *filetowrite = "../result/result.txt";    // the frequency of all alphabetical letters will be written in this file
	  
	  long alphabetfreq[ALPHABETSIZE] = {0}; // array to store the frequency of each alphablet letter, which should be alway up-to-date;
	  
	  
	  alphabetcountmulthreads(path, filetowrite, alphabetfreq, num_threads);  // process the data files using mutiple threads
	  
	  printf("The results are counted as follows : \n");
	  
	  displayalphabetfreq(alphabetfreq, ALPHABETSIZE);  // print the frequency stored in the array to output screen
}
