#ifndef LINKED_LIST_H
#define LINKED_LIST_H

struct node {
    int data;
    struct node *next;
};

void printLinkedlist(struct node* head_p);
int getLinkedlistSize(struct node* head_p);
int Member(int value, struct node* head_p);
int Insert(int value, struct node** head_pp);
int Delete(int value, struct node** head_pp);

#endif 
