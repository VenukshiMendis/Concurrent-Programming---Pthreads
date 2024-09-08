#include <stdio.h>
#include <stdlib.h>
#include "random_numbers.h"
#include "serial.h"
#include "mutex.h"
#include "read_write_lock.h"
#include <math.h>

// number of samples used
int NUMBER_OF_SAMPLES = 20;
int needed_samples;

#include <math.h>
#include <stdio.h>

void calculate_mean_and_std(unsigned long *times, double *mean, double *std) {
    unsigned long total = 0;
    for (int i = 0; i < NUMBER_OF_SAMPLES; i++) {
        //printf("time %lu\n", times[i]);
        total += times[i];
    }
    *mean = (double)total / NUMBER_OF_SAMPLES;  // Cast to double for fractional precision

    double sum_of_squares = 0.0;
    for (int i = 0; i < NUMBER_OF_SAMPLES; i++) {
        sum_of_squares += pow((double)times[i] - *mean, 2);  // Cast times[i] to double as well
    }
    *std = sqrt(sum_of_squares / (NUMBER_OF_SAMPLES - 1));  // Use double for sqrt and result
}


void run_test_case(int n, int m, float m_member, float m_insert, float m_delete) {
    FILE *file = fopen("results.csv", "a"); // Open file in append mode
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // run the serial execution NUMBER_OF_SAMPLES times
    unsigned long serial_times[NUMBER_OF_SAMPLES];           
    for (int i=0; i<NUMBER_OF_SAMPLES; i++){
        serial_times[i] = serial(n, m, m_member, m_insert, m_delete);
    }

    double serial_mean, serial_std;
    calculate_mean_and_std(serial_times, &serial_mean, &serial_std);
    needed_samples = (int)ceil(pow(((100*1.96*serial_std)/(5*serial_mean)), 2));

    printf("Mean time for serial: %f microseconds\n", serial_mean);
    printf("Standard deviation for serial: %f microseconds\n", serial_std);
    printf("Number of samples needed: %d\n\n", needed_samples);

    fprintf(file, "Serial,%d,%f,%f,%d\n\n", 1, serial_mean, serial_std,needed_samples); // Serial is single-threaded

    // Mutex execution for 1, 2, 4, and 8 threads         
    for (int i=1; i <= 8; i *= 2){
        unsigned long mutex_times[NUMBER_OF_SAMPLES];
        for (int j=0; j<NUMBER_OF_SAMPLES; j++){            
            mutex_times[j] = mutex_program(n, m, m_member, m_insert, m_delete, i);
        }
        double mutex_mean, mutex_std;
        calculate_mean_and_std(mutex_times, &mutex_mean, &mutex_std);
        needed_samples = (int)ceil(pow(((100*1.96*mutex_std)/(5*mutex_mean)), 2));
        
        printf("Mean time for mutex with %d threads: %f microseconds\n", i, mutex_mean);
        printf("Standard deviation for mutex with %d threads: %f microseconds\n", i, mutex_std);
        printf("Number of samples needed: %d\n\n", needed_samples);     

        fprintf(file, "Mutex,%d,%f,%f,%d\n", i, mutex_mean, mutex_std,needed_samples);  
        
    }

    fprintf(file, "\n"); 

    //Read Write Lock execution for 1, 2, 4, and 8 threads
    for (int i=1; i <= 8; i *= 2){
        unsigned long rwlock_times[NUMBER_OF_SAMPLES];
        for (int j=0; j<NUMBER_OF_SAMPLES; j++){            
            rwlock_times[j] = read_write_lock_program(n, m, m_member, m_insert, m_delete, i);
        }
        double rwlock_mean, rwlock_std;
        calculate_mean_and_std(rwlock_times, &rwlock_mean, &rwlock_std);
        needed_samples = (int)ceil(pow(((100*1.96*rwlock_std)/(5*rwlock_mean)), 2));
        
        printf("Mean time for ReadWriteLock with %d threads: %f microseconds\n", i, rwlock_mean);
        printf("Standard deviation for ReadWriteLock with %d threads: %f microseconds\n", i, rwlock_std);        
        printf("Number of samples needed: %d\n\n", needed_samples); 

        fprintf(file, "ReadWriteLock,%d,%f,%f,%d\n", i, rwlock_mean, rwlock_std,needed_samples);      
        
    }

    fprintf(file, "\n"); 
    fclose(file);
}

int main() {
    int n = 1000;  // Number of items in the linked list
    int m = 10000; // Total number of operations

    // Open the file once and pass the file pointer
    FILE *file = fopen("results.csv", "a");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    // Write header to CSV if the file is new
    fprintf(file, "Type,Threads,Mean(ms),Standard Deviation, No of samples\n");
    fclose(file);

    // Test Case 1
    printf("Running Case 1:\n");
    run_test_case(n, m, 0.99, 0.005, 0.005);

    // Test Case 2
    printf("Running Case 2:\n");
    run_test_case( n, m, 0.90, 0.05, 0.05);

    // Test Case 3
    printf("Running Case 3:\n");
    run_test_case(n, m, 0.50, 0.25, 0.25);

    return 0;
}
