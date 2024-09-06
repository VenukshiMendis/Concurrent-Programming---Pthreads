#ifndef RANDOM_NUMBERS_H
#define RANDOM_NUMBERS_H

#include <stddef.h> 

//Generate random values for initial array and insert, delete and member arrays by takin current time as seed
void generateUniqueRandomNumbers(int* initial_arr, int* member_arr, int* insert_arr, int* delete_arr, int initial_arr_size,
                                     int member_arr_size, int insert_arr_size, int delete_arr_size);

#endif 
