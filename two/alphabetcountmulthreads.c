#include <stdio.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libgen.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "count.h"

#define MAX_NUM_FILES 1024
#define MAX_FILE_NAME_LENGTH 1024
#define DT_REG 8
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
	dirp = opendir(path);
    pthread_t threads[num_threads];
    pthread_mutex_t mutex;
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Error initializing mutex\n");
        return;
    }

    ThreadData data[num_threads];

    if ((dirp = opendir(path)) == NULL) {
        printf("Error opening directory: %s\n", path);
        return;
    }

    while ((entry = readdir(dirp)) != NULL) {

	char fullpath[MAX_FILE_NAME_LENGTH];
	sprintf(fullpath, "%s/%s",path, entry->d_name);
	struct stat entry_stat;
	if(stat(fullpath, &entry_stat) != 0){
	printf("Error getting file information: %s\n", fullpath);
	continue;	
}
        if (fileCount >= MAX_NUM_FILES) {
            printf("Too many files, can't process more than %d files\n", MAX_NUM_FILES);
            break;
        }

        if (S_ISREG(entry_stat.st_mode) && strstr(entry->d_name, ".txt") != NULL) {
            fileNames[fileCount] = malloc(MAX_FILE_NAME_LENGTH);
            if (fileNames[fileCount] == NULL) {
                printf("Failed to allocate memory\n");
                return;
            }
            strcpy(fileNames[fileCount], fullpath);
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
        if (pthread_create(&threads[i], NULL, process_files, &data[i]) != 0) {
            printf("Error creating thread\n");
            return;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            printf("Error joining thread\n");
            return;
        }
    }

    if (pthread_mutex_destroy(&mutex) != 0) {
        printf("Error destroying mutex\n");
        return;
    }

    for (int i = 0; i < fileCount; i++) {
        free(fileNames[i]);
    }

    FILE* fp;
    if ((fp = fopen(filetowrite, "w")) == NULL) {
        printf("Error opening file: %s\n", filetowrite);
        return;
    }

    for (int i = 0; i < 26; i++) {
        if (fprintf(fp, "%c -> %ld\n", 'a' + i, alphabetfreq[i]) < 0) {
            printf("Error writing to file\n");
            return;
        }
    }
	
    fclose(fp);
	printf("File created successfully!\n");
}

void* process_files(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread id = %lu (thread: %lu) is processing files with index from %d to %d!\n", getpid(), pthread_self(), data->start, data->end);

    for (int i = data->start; i <= data->end; i++) {
	char* baseName = basename(data->fileNames[i]);
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
        if (ch == EOF && ferror(file)) {
            printf("Error reading from file\n");
            return;
        }
        ch = tolower(ch);
        if (ch >= 'a' && ch <= 'z') {
            pthread_mutex_lock(mutex);
            alphabetfreq[ch - 'a']++;
            pthread_mutex_unlock(mutex);
        }
    }

    fclose(file);
}

