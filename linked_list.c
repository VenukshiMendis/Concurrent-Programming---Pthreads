#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


int Member(int value, struct node* head_p) {
    struct node* curr_p = head_p;
    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value) {
        return 0;
    } else {
        return 1;
    }
}



int Insert(int value, struct node** head_pp) {
    struct node* curr_p = *head_pp;
    struct node* pred_p = NULL;
    struct node* temp_p;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value) {
        temp_p = (struct node*) malloc(sizeof(struct node));
        temp_p->data = value;
        temp_p->next = curr_p;
    
        if (pred_p == NULL) { // New first node 
            *head_pp = temp_p;  
            //printf("inserted head %d \n",value); 
        } else {
            pred_p->next = temp_p;
        }
        //printf("inserted %d \n",value);
        return 1;
    } else { // Value already in list 
        //printf("NOT inserted %d \n",value);
        return 0;


    }
}


int Delete(int value, struct node** head_pp) {
    struct node* curr_p = *head_pp;
    struct node* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value) {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }


    if (curr_p != NULL && curr_p->data == value) {
        if (pred_p == NULL) { // Deleting first node in the list
            *head_pp = curr_p->next;
        } 
     else {
            pred_p->next = curr_p->next;
        }
        free(curr_p);
        //printLinkedlist(*head_pp);
        //printf("deleted %d \n",value);
        return 1; 
    }
    // printLinkedlist(*head_pp);
    // printf("NOT deleted %d \n",value);
    return 0; 
}


void printLinkedlist(struct node* head_p) {
    while (head_p != NULL) {
        printf("%d ", head_p->data);
        head_p = head_p->next;
    }
    printf("\n");  
}

int getLinkedlistSize(struct node* head_p) {
    int size = 0;
    while (head_p != NULL) {
        size++;
        head_p = head_p->next;
    }
    return size;
}



