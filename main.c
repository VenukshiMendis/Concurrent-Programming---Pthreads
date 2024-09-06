#include <stdio.h>
#include <stdlib.h>
#include "random_numbers.h"
#include "serial.h"
#include "mutex.h"
#include "read_write_lock.h"

// // Function to measure and print time for serial and mutex operations
// void run_test_case(int n, int m, float m_member, float m_insert, float m_delete) {
//     unsigned long time_in_microseconds;

//     // Serial execution
//     time_in_microseconds = serial(n, m, m_member, m_insert, m_delete);
//     printf("Elapsed time for serial: %lu microseconds\n\n", time_in_microseconds);

//     // Mutex execution for 1, 2, 4, and 8 threads
//     for (int i = 1; i <= 8; i = i * 2) {
//         time_in_microseconds = mutex_program(n, m, m_member, m_insert, m_delete, i);
//         printf("Elapsed time for mutex with %d threads: %lu microseconds\n\n", i, time_in_microseconds);
//     }

//     // Read Write Lock execution for 1, 2, 4, and 8 threads
//     for (int i = 1; i <= 8; i = i * 2) {
//         time_in_microseconds = read_write_lock_program(n, m, m_member, m_insert, m_delete, i);
//         printf("Elapsed time for read write lock with %d threads: %lu microseconds\n\n", i, time_in_microseconds);
//     }
// }



void run_test_case(int n, int m, float m_member, float m_insert, float m_delete) {
    FILE *file = fopen("results.csv", "a"); // Open file in append mode
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    // Write header to CSV if the file is new
    static int header_written = 0;
    if (!header_written) {
        fprintf(file, "Type,Threads,Elapsed Time (microseconds)\n");
        header_written = 1;
    }

    // Serial execution
    unsigned long time_in_microseconds = serial(n, m, m_member, m_insert, m_delete);
    fprintf(file, "Serial,%d,%lu\n\n", 1, time_in_microseconds); // Serial is single-threaded
    printf("Elapsed time for serial: %lu microseconds\n\n", time_in_microseconds);

    // Mutex execution for 1, 2, 4, and 8 threads
    for (int i = 1; i <= 8; i *= 2) {
        time_in_microseconds = mutex_program(n, m, m_member, m_insert, m_delete, i);
        fprintf(file, "Mutex,%d,%lu\n", i, time_in_microseconds);
        printf("Elapsed time for mutex with %d threads: %lu microseconds\n\n", i, time_in_microseconds);
    }
    fprintf(file, "\n"); 

    // Read Write Lock execution for 1, 2, 4, and 8 threads
    for (int i = 1; i <= 8; i *= 2) {
        time_in_microseconds = read_write_lock_program(n, m, m_member, m_insert, m_delete, i);
        fprintf(file, "ReadWriteLock,%d,%lu\n", i, time_in_microseconds);
        printf("Elapsed time for read write lock with %d threads: %lu microseconds\n\n", i, time_in_microseconds);
    }
    fprintf(file, "\n"); 

    fclose(file);
}

int main() {
    int n = 1000;  // Number of items in the linked list
    int m = 10000; // Total number of operations

    // Test Case 1
    printf("Running Case 1:\n");
    run_test_case(n, m, 0.99, 0.005, 0.005);

    // Test Case 2
    printf("Running Case 2:\n");
    run_test_case(n, m, 0.90, 0.05, 0.05);

    // Test Case 3
    printf("Running Case 3:\n");
    run_test_case(n, m, 0.50, 0.25, 0.25);

    return 0;
}
