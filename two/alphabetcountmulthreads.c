/*
 * alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

#include <stdio.h> 
#include "count.h"

/**
  The alphabetcountmulthreads function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite. Different with programming assignment#0, you need to implement 
  the program using mutithreading.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z, which should be already up-to-date;
      num_threads - number of the threads running in parallel to process the files
      
       
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Requirements:
1)	Multiple threads are expected to run in parallel to share the workload, i.e. suppose 3 threads to process 30 files, then each thread should process 10 files;
2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
Thread id = 274237184 starts processing files with index from 0 to 10!
3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
Thread id = 265844480 is processing file input_11.txt
4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
      Thread id = 274237184 is done !
5)	The array: long alphabetfreq[ ] should always be up-to-date, i.e. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]


You should have the screen printing should be similar as follows:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 a -> 2973036
 b -> 556908
 c -> 765864
 ... ...
*/


#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>

#define MAX_NUM_FILES 1024
#define MAX_FILE_NAME_LENGTH 1024

void alphabetcountmulthreads(char* path, char* filetowrite, long alphabetfreq[], int num_threads);



typedef struct ThreadData {
    char** fileNames;
    int start;
    int end;
    long* alphabetfreq;
    pthread_mutex_t* mutex;
} ThreadData;

void count_alphabets_in_file(char* filename, long* alphabetfreq, pthread_mutex_t* mutex);

void* process_files(void* arg);

void alphabetcountmulthreads(char* path, char* filetowrite, long alphabetfreq[], int num_threads) {
    DIR* dirp;
    struct dirent* entry;
    char* fileNames[MAX_NUM_FILES];
    int fileCount = 0;

    time_t currentTime;
    time(&currentTime);
    char *timeString = ctime(&currentTime);

    pthread_t threads[num_threads];
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    ThreadData data[num_threads];

    if ((dirp = opendir(path)) == NULL) {
        printf("Error opening directory: %s\n", path);
        return;
    }

    while ((entry = readdir(dirp)) != NULL) {
        if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
            fileNames[fileCount] = malloc(MAX_FILE_NAME_LENGTH);
            sprintf(fileNames[fileCount], "%s/%s", path, entry->d_name);
            fileCount++;
        }
    }
    closedir(dirp);

    int filesPerThread = fileCount / num_threads;

    for (int i = 0; i < num_threads; i++) {
        data[i].fileNames = fileNames;
        data[i].start = i * filesPerThread;
        data[i].end = (i == num_threads - 1) ? fileCount - 1 : (i + 1) * filesPerThread - 1;
        data[i].alphabetfreq = alphabetfreq;
        data[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, process_files, &data[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    for (int i = 0; i < fileCount; i++) {
        free(fileNames[i]);
    }

    // Save results to file
    FILE* fp;
    if ((fp = fopen(filetowrite, "w")) == NULL) {
        printf("Error opening file: %s\n", filetowrite);
        return;
    }
    
    for (int i = 0; i < 26; i++) {
        fprintf(fp, "%c -> %ld\n", 'a' + i, alphabetfreq[i]);
        
    }
    fclose(fp);
}

void* process_files(void* arg) {
    ThreadData* data = (ThreadData*)arg;

    printf("Thread id = %lu (thread: %lu) is processing files with index from %d to %d!\n", getpid(), pthread_self(), data->start, data->end);

    for (int i = data->start; i <= data->end; i++) {
        char* baseName = basename(data->fileNames[i]);  // Extract filename from path
        printf("Thread id = %lu is processing file %s\n", pthread_self(), baseName);
        count_alphabets_in_file(data->fileNames[i], data->alphabetfreq, data->mutex);
    }

    printf("Thread id = %lu is done!\n", pthread_self());


    return NULL;
}

void count_alphabets_in_file(char* filename, long* alphabetfreq, pthread_mutex_t* mutex) {
    FILE* file;
    int ch;

    if ((file = fopen(filename, "r")) == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    while ((ch = fgetc(file)) != EOF) {
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') {
            pthread_mutex_lock(mutex);
            alphabetfreq[ch - 'a']++;
            pthread_mutex_unlock(mutex);
        }
    }

    fclose(file);
}
