#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"
#include "scheduler.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <FIFO/SJF> <job_sizes_comma_separated> \n", argv[0]);
        return 1;
    }
    
    if (strcmp(argv[1], "FIFO") != 0 && strcmp(argv[1], "SJF") != 0) {
        fprintf(stderr, "Error: policy must be FIFO or SJF.\n");
        return 1;
    }    

    int *jobs = NULL;
    int size = 0;
    char *token = strtok(argv[2], ",");

    while (token != NULL) {
        int job = atoi(token);
        if (job <= 0) {
            fprintf(stderr, "Invalid job size: %s\n", token);
            free(jobs);
            return 1;
        }

        int *temp = realloc(jobs, (size + 1) * sizeof(int));

        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(jobs);
            return 1;
        }

        jobs = temp;
        jobs[size++] = job;
        token = strtok(NULL, ",");
    }

    if (jobs != NULL) {
        float average_response_time;

        if (strcmp(argv[1], "FIFO") == 0) {
            average_response_time = FIFO(jobs, size);
        } else {
            average_response_time = SJF(jobs, size);
        }

        printf("Average response time: %f seconds\n", average_response_time);    
    }

    free(jobs);
    return 0;
}