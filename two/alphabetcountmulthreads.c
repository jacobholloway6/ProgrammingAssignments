#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "count.h"
#include <time.h>

typedef struct
{
    char **file_names, **file_paths;
    int start, end, num_threads, *thread_running_counter;
    long *alphabet_freq;
    pthread_mutex_t *writer_mutex;
} params;

int countTxtFiles(char *dir_path)
{

    DIR *dir = opendir(dir_path);
    struct dirent *file;
    int counter = 0;

    if (dir == NULL)
    {
        printf("Failed to open the directory %s\n", dir_path);
        return 0;
    }

    while ((file = readdir(dir)))
    {

        if (strlen(file->d_name) > 4 && strcmp(file->d_name + strlen(file->d_name) - 4, ".txt") == 0)
            counter++;
    }

    closedir(dir);
    return counter;
}

// Function to collect the names and paths of .txt files in a directory
void collectTxtFiles(char *dir_path, char **names, char **paths)
{
    struct dirent **dir_files;
    int num_files = scandir(dir_path, &dir_files, 0, alphasort);
    int counter = 0;

    for (int i = 0; i < num_files; i++)
    {
        // For each .txt file, store the name and path
        if (strlen(dir_files[i]->d_name) > 4 && strcmp(dir_files[i]->d_name + strlen(dir_files[i]->d_name) - 4, ".txt") == 0)
        {
            char full_path[512];
            sprintf(full_path, "%s/%s", dir_path, dir_files[i]->d_name);

            paths[counter] = strdup(full_path);
            names[counter] = strdup(dir_files[i]->d_name);
            counter++;
        }
        free(dir_files[i]);
    }
    free(dir_files);
}

// Function to be executed by each thread, calculating the frequency of alphabets in files
void *run_alphabet_counter(void *p)
{
    params *data = (params *)p;
    printf("Thread id = %lu started processing files with index from %d to %d!\n",
           pthread_self(), data->start, data->end - 1);

    pthread_mutex_lock(data->writer_mutex);
    // Increment the counter to indicate another thread has started
    (*(data->thread_running_counter))++;
    pthread_mutex_unlock(data->writer_mutex);

    // Initialize the local alphabet frequency array
    long local_alphabet_freq[ALPHABETSIZE] = {0};
    FILE *file;
    char c;

    // Iterate over the files assigned to this thread and count the frequency of alphabets
    for (int i = data->start; i < data->end; i++)
    {
        file = fopen(data->file_paths[i], "r");

        if (file)
        {
            printf("Thread id = %lu is processing file %s\n", pthread_self(), data->file_names[i]);

            // Read file character by character and update frequency if it's an alphabet
            while ((c = fgetc(file)) != EOF)
            {
                if (isalpha(c))
                    local_alphabet_freq[(tolower(c) - 'a')]++;
            }
            fclose(file);
        }
    }

    pthread_mutex_lock(data->writer_mutex);
    // Update the global alphabet frequency with the thread's local frequency
    for (int i = 0; i < ALPHABETSIZE; i++)
        data->alphabet_freq[i] += local_alphabet_freq[i];
    pthread_mutex_unlock(data->writer_mutex);
    pthread_exit(NULL);
}

// Function to spawn the threads and distribute the work among them
void spawn_threads(int num_files, char **names, char **paths, long freq[], int num_threads)
{
    pthread_t threads[num_threads];
    pthread_mutex_t lock;
    params thread_params[num_threads];
    int thread_counter = 0;

    pthread_mutex_init(&lock, NULL);
    int files_per_thread = num_files / num_threads + 1;
    int start = 0;

    // Create threads and assign them parameters
    for (int i = 0; i < num_threads; i++)
    {
        thread_params[i] = (params){.file_names = names, .file_paths = paths, .start = start, .end = start + files_per_thread, .alphabet_freq = freq, .num_threads = num_threads, .writer_mutex = &lock, .thread_running_counter = &thread_counter};

        // In the last thread, we handle the remaining files
        if (i == num_threads - 1)
            thread_params[i].end = num_files;

        pthread_create(&threads[i], NULL, run_alphabet_counter, &thread_params[i]);

        start += files_per_thread;
    }

    // Wait for all threads to finish and print their termination messages
    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);

        if (thread_counter == num_threads)
        {
            printf("\n");
            thread_counter--;
        }
        printf("Thread id = %lu is done!\n", threads[i]);
    }

    pthread_mutex_destroy(&lock);
    printf("\n");
}

// The main function to count the frequency of alphabets in .txt files in a directory using multiple threads
void alphabetcountmulthreads(char *dir_path, char *out_file, long alphabet_freq[], int num_threads)
{
    int num_files = countTxtFiles(dir_path);
    if (num_files <= 0)
        return;

    if (num_files < num_threads)
        num_threads = num_files;

    char **names = calloc(num_files, sizeof(char *));
    char **paths = calloc(num_files, sizeof(char *));

    collectTxtFiles(dir_path, names, paths);
    spawn_threads(num_files, names, paths, alphabet_freq, num_threads);

    // Free the memory allocated for file names and paths
    for (int i = 0; i < num_files; i++)
    {
        free(paths[i]);
        free(names[i]);
    }
    free(paths);
    free(names);

    // Write the final frequency of alphabets to the output file
    FILE *outputFile = fopen(out_file, "w");
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
        fprintf(outputFile, "%c -> %ld\n", 'a' + i, alphabet_freq[i]);
    }

    
    fclose(outputFile);

    printf("Task was completed on : %s \n", timeString);
    printf("File created successfully.\n\n");
	printf("The results are counted as follows : \n");
}
