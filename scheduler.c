#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include "matrix.h"


// Matrix multiplication has a nice property-- the size of the matrix correlates directly to the time required to complete the task!
// so we can use the size of the matrix as a proxy for the job's execution time when implementing scheduling algorithms.
float SJF(int* jobs, int size) {
    // Sort jobs from smallest to largest
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (jobs[i] > jobs[j]) {
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }

    // After sorting the jobs by size, we can simply use the FIFO function to calculate the average response time.
    return FIFO(jobs, size);
}

float FIFO(int* jobs, int size) {
    float execution_time = 0;
    float response_time = 0;

    for (int i = 0; i < size; i++) {
        printf("Running job: %dx%d\n", jobs[i], jobs[i]);
        float job_time = do_job(jobs[i], jobs[i], jobs[i], 0);
        execution_time += job_time;
        response_time += execution_time;
    }

    float throughput = size / execution_time;
    float average_response_time = response_time / size;

    printf("Throughput: %f jobs/second\n", throughput);
    printf("Average response time: %f seconds\n", average_response_time);

    return average_response_time;

}
