/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
    DIR* d;
    struct dirent * dir;
    d = opendir(path);
    if (d != NULL)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name, ".txt"))
            {
                char filePath[1024];
                sprintf(filePath, "%s/%s", path, dir->d_name);

                FILE *file = fopen(filePath, "r");
                if (file != NULL)
                {
                    char ch;
                    while((ch = fgetc(file)) != EOF)
                    {
                        ch = tolower(ch);
                        if(ch >= 'a' && ch <= 'z')
                        {
                            alphabetfreq[ch - 'a']++;
                        }
                    }
                    
                    fclose(file);
                }
                else
                {
                    printf("Failed to open the input file: %s\n", filePath);
                }
            }
        }
        closedir(d);
    }
   
    FILE *outputFile = fopen(filetowrite, "w");
    time_t currentTime;
    time(&currentTime);
    char *timeString = ctime(&currentTime);
    if (outputFile == NULL)
    {
        printf("Failed to create the output file.\n");
        return;
    }
    fprintf(outputFile, "File created on: %s\n", timeString);
    fprintf(outputFile, "Letter -> Frequency\n");
    for (int i = 0; i < 26; i++)
    {
        fprintf(outputFile, "%c -> %ld\n", 'a' + i, alphabetfreq[i]);
    }

    fclose(outputFile);

    printf("File created successfully.\n");
}



