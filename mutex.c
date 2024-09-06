#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include "random_numbers.h"
#include "mutex.h"

void *mutex_func(void *arg) {

    thread_arg_t *thread_arg = (thread_arg_t *)arg;
    thread_data_t *data = thread_arg->data;
    int rank = thread_arg->thread_rank;
    
    int member_start = ((float)data->no_of_member_operations / data->no_of_threads) * rank;
    int member_end = ((float)data->no_of_member_operations / data->no_of_threads) * (rank + 1) - 1;
    
    int insert_start = ((float)data->no_of_insert_operations / data->no_of_threads) * rank;
    int insert_end = ((float)data->no_of_insert_operations / data->no_of_threads) * (rank + 1) - 1;

    int delete_start = ((float)data->no_of_delete_operations / data->no_of_threads) * rank;
    int delete_end = ((float)data->no_of_delete_operations / data->no_of_threads) * (rank + 1) - 1;


    // printf("rank %d insert start %d insert end %d \n",rank, insert_start, insert_end);
    // printf("rank %d delete start %d delete end %d \n", rank, delete_start, delete_end);

    int member_index = member_start;
    int insert_index = insert_start;
    int delete_index = delete_start;

    while (member_index <= member_end || insert_index <= insert_end || delete_index <= delete_end) {
        int op =  rand() % 3;
        
        if (op == 0 && member_index <= member_end ) {
            pthread_mutex_lock(data->list_mutex);
            Member(data->member_arr[member_index], data->head);
            member_index++ ;
            pthread_mutex_unlock(data->list_mutex);
        }

        else if (op == 1 && insert_index<= insert_end) {
            pthread_mutex_lock(data->list_mutex);
            Insert(data->insert_arr[insert_index], &data->head);  
            insert_index++;
            pthread_mutex_unlock(data->list_mutex);
        }

        else if(op == 2 && delete_index <= delete_end) {
            pthread_mutex_lock(data->list_mutex);
            Delete(data->delete_arr[delete_index], &data->head);
            delete_index++ ;
            pthread_mutex_unlock(data->list_mutex); 
        }
    }

     return NULL;
}

// Function to print an integer array
void print_array(const char* name, int* array, int size) {
    
    printf("%s: ", name);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


unsigned long mutex_program(int n , int m ,float m_member, float m_insert, float m_delete, int no_of_threads){

    int no_of_member_operations = (int) m * m_member;
    int no_of_insert_operations = (int) m * m_insert;
    int no_of_delete_operations = (int) m * m_delete;

    
    printf("%d, %d, %d \n", no_of_member_operations, no_of_insert_operations, no_of_delete_operations);

    int *initial_arr = (int*)malloc(n * sizeof(int));
    int *member_arr  = (int*)malloc(no_of_member_operations * sizeof(int));
    int *insert_arr  = (int*)malloc(no_of_insert_operations * sizeof(int));
    int *delete_arr  = (int*)malloc(no_of_delete_operations * sizeof(int));

    generateUniqueRandomNumbers(initial_arr, member_arr, insert_arr , delete_arr , n, no_of_member_operations, no_of_insert_operations, no_of_delete_operations);

    struct node* head = NULL;
    //initialize the linked list
    for (int i = 0; i < n; i++) {
        Insert(initial_arr[i], &head);
    }

    printf("size of the linked list %d \n", getLinkedlistSize(head));
    //printLinkedlist(head);

    // print_array("Member Array", member_arr, no_of_member_operations);
    // print_array("Insert Array", insert_arr, no_of_insert_operations);
    // print_array("Delete Array", delete_arr, no_of_delete_operations);

    //initalize the mutex
    pthread_mutex_t list_mutex;
    pthread_mutex_init(&list_mutex, NULL);

    thread_data_t data = {
        .member_arr = member_arr,
        .insert_arr = insert_arr,
        .delete_arr = delete_arr,
        .head = head,
        .no_of_member_operations = no_of_member_operations,
        .no_of_insert_operations = no_of_insert_operations,
        .no_of_delete_operations = no_of_delete_operations,
        .no_of_threads = no_of_threads,
        .list_mutex = &list_mutex
    };

    pthread_t threads[no_of_threads];
    // Create an array of thread_arg_t for each thread
    thread_arg_t thread_args[no_of_threads];

    struct timeval start, stop;
    gettimeofday(&start, NULL);  // Start time
    
    for (int i = 0; i < no_of_threads; i++) {
        // Initialize thread_arg_t for each thread
        thread_args[i].data = &data;
        thread_args[i].thread_rank = i;

        // Pass thread_args[i] to the thread
        pthread_create(&threads[i], NULL, mutex_func, &thread_args[i]);
    }

    for (int i = 0; i < no_of_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    gettimeofday(&stop, NULL); //End time
    unsigned long elapsed_time_in_microseconds = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

   
    //printLinkedlist(data.head);
    printf("size of the linked list %d \n", getLinkedlistSize(data.head));

    pthread_mutex_destroy(&list_mutex);
    free(head);
    free(initial_arr);
    free(member_arr);
    free(insert_arr);
    free(delete_arr);

    return elapsed_time_in_microseconds;
}

// int main(){
//     int n=10;
//     int m =40;
//     float m_member = 0.5;
//     float m_insert = 0.25;
//     float m_delete = 0.25;
//     int time =  mutex_program(n, m, m_member, m_insert, m_delete, 4);
//     printf(" time %d",time);
// }