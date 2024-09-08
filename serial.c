#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "random_numbers.h"
#include "linked_list.h"
#include "serial.h"

unsigned long serial(int n , int m ,float m_member, float m_insert, float m_delete){

    int no_of_member_operations = (int) m * m_member;
    int no_of_insert_operations = (int) m * m_insert;
    int no_of_delete_operations = (int) m * m_delete;

    
    //printf("%d, %d, %d \n", no_of_member_operations, no_of_insert_operations, no_of_delete_operations);

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

    //printf("size of the linked list %d \n", getLinkedlistSize(head));


    int member_op = 0;
    int insert_op = 0;
    int delete_op = 0;
    int total_op = 0;
    
    struct timeval start, stop;
    gettimeofday(&start, NULL);  // Start time
   
    
    while (total_op < m) {
        int op =  rand() % 3;
        if (op == 0 && member_op < no_of_member_operations ) {
            Member(member_arr[member_op], head);
            member_op++ ;
            total_op++ ;
        }

        else if (op == 1 && insert_op < no_of_insert_operations) {
            Insert(insert_arr[insert_op], &head);  
            insert_op++ ;
            total_op++ ;   
        }

        else if(op == 2 && delete_op < no_of_delete_operations ) {
            Delete(delete_arr[delete_op], &head);
            delete_op++ ;
            total_op++; 
        }
    }

    gettimeofday(&stop, NULL); //End time
    unsigned long elapsed_time_in_microseconds = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

    //printf("Elapsed time: %lu microseconds\n", elapsed_time_in_microseconds);
    
    //printf("total no of operations %d \n", total_op);
    
    //printf("size of the linked list %d \n", getLinkedlistSize(head));

    free(head);
    free(initial_arr);
    free(member_arr);
    free(insert_arr);
    free(delete_arr);


    return elapsed_time_in_microseconds;

}


