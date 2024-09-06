#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_VALUE 65535 

// int* generateUniqueRandomNumbers(int random_number_count) {
void generateUniqueRandomNumbers(int* initial_arr, int* member_arr, int* insert_arr, int* delete_arr, int initial_arr_size,
                                     int member_arr_size, int insert_arr_size, int delete_arr_size) {

    // Hash set to track unique numbers
    char *hash_set = (char *)calloc(MAX_VALUE + 1, sizeof(char));
   
    int generated = 0;
    //Give current time as seed
    srand((unsigned int)time(NULL)); 

    // Generate unique numbers for initial_arr and insert_arr
    while (generated < initial_arr_size + insert_arr_size) {
        int num = rand() % (MAX_VALUE + 1);

        if (hash_set[num] == 0) {
            hash_set[num] = 1; 
            
            if(generated < initial_arr_size) {
                initial_arr[generated] = num;
            }
            
            else {
                insert_arr[generated - initial_arr_size] = num;
            }
            generated++;
        }
    }

    // Reinitialize hash set to track unique numbers for member_arr
    memset(hash_set, 0, MAX_VALUE + 1);

    // Generate unique numbers for member_arr
    for (int i = 0; i < member_arr_size; i++) {
        int num;
        do {
            num = rand() % (MAX_VALUE + 1);
        } while (hash_set[num] != 0);

        hash_set[num] = 1;
        member_arr[i] = num;
    }

    // Reinitialize hash set to track unique numbers for delete_arr
    memset(hash_set, 0, MAX_VALUE + 1);

    // Generate unique numbers for delete_arr
    for (int i = 0; i < delete_arr_size; i++) {
        int num;
        do {
            num = rand() % (MAX_VALUE + 1);
        } while (hash_set[num] != 0);

        hash_set[num] = 1;
        delete_arr[i] = num;
    }

    free(hash_set);

    return;
}


