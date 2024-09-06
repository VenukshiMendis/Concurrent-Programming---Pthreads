#ifndef THREAD_DATA_H
#define THREAD_DATA_H

#include <pthread.h>
#include "linked_list.h"  

typedef struct {
    int *member_arr;                // Array for member operations
    int *insert_arr;                // Array for insert operations
    int *delete_arr;                // Array for delete operations
    struct node* head;              // Pointer to the head of the linked list
    int no_of_member_operations;    
    int no_of_insert_operations;    
    int no_of_delete_operations;    
    int no_of_threads;
    pthread_mutex_t *list_mutex;    // Pointer to a mutex for thread synchronization
} thread_data_t;

typedef struct {
    thread_data_t *data;  // Pointer to shared thread data
    int thread_rank;      // Rank of the thread
} thread_arg_t;

unsigned long mutex_program(int n , int m ,float m_member, float m_insert, float m_delete, int no_of_threads);

#endif 
