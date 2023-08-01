/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */

#include "count.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void specialcharcount(char *path, char *filetowrite, long charfreq[])
{
    // Create a pointer to a directory
    DIR* d;

    // Create a pointer to read the directory entry
    struct dirent * dir;

    // Open the directory using opendir()
    d = opendir(path);
    if (d != NULL)
    {
        // Read the directory entry
        while ((dir = readdir(d)) != NULL)
        {
            // Check if the file has .txt extension
            if(strstr(dir->d_name, ".txt"))
            {
                char filePath[1024];
                sprintf(filePath, "%s/%s", path, dir->d_name);

                FILE *file = fopen(filePath, "r");
                if (file != NULL)
                {
                    char ch;
                    // Read the file character by character
                    while((ch = fgetc(file)) != EOF)
                    {
                        // Check if the character is a special character
                        switch(ch)
                        {
                            case ',':
                                charfreq[0]++;
                                break;
                            case '.':
                                charfreq[1]++;
                                break;
                            case ':':
                                charfreq[2]++;
                                break;
                            case ';':
                                charfreq[3]++;
                                break;
                            case '!':
                                charfreq[4]++;
                                break;
                            default:
                                break;
                        }
                    }
                    fclose(file);
                }
            }
        }
        closedir(d);
    }

    FILE *outputFile = fopen(filetowrite, "w");
    time_t currentTime;
    time(&currentTime);
    char *timeString = ctime(&currentTime);
    if (outputFile != NULL)
    {

        char specialChars[] = {',', '.', ':', ';', '!'};
        fprintf(outputFile, "File created on: %s\n", timeString);
        for (int i = 0; i < 5; ++i)
        {
            fprintf(outputFile, "%c -> %ld\n", specialChars[i], charfreq[i]);
        }
        fclose(outputFile);

        printf("Special result file created successfully.\n");
        
        
    }
}

/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12    
*/

