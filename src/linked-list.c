#include <stdlib.h>
#include "linked-list.h"

LList* llist_node(void* val) {
    LList* head = malloc(sizeof(LList));
    head->val = val;
    return head;
}

LList* llist_get(LList* head, int index) {
    LList* node = head;
    while(index-- > 0) {
        node = node->next;
    }
    return node;
}

void* llist_pop(LList* head) {
    void* val = head->val;
    head->next = NULL;
    llist_free(head);
    return val;
}

LList* llist_push(LList* next, void* val) {
    LList* head = llist_node(val);
    head->next = next;
    return head;
}

LList* llist_insert_after(LList* head, void* val) {
    LList* inserted = llist_node(val);
    inserted->next = head->next;
    head->next = inserted;

    return inserted;
}

int llist_size(LList* head) {
    int size = 0;
    while(head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

LList* llist_split_after(LList* head, int index) {
    LList* next = head->next;
    while (index-- > 0) {
        head = head->next;
        next = head->next;
    }
    head->next = NULL;
    return next;
}

void llist_free(LList* head) {
    while (head != NULL) {
        LList* next = head->next;
        free(head);
        head = next;
    }
}

#include <stdio.h>
LList* llist_sort(LList* head, int (*cmp)(const void *, const void *)) {
    //printf("== llist_sort begin ==\n");
    int size = llist_size(head);
    //printf("llist_size(head) == %i\n", llist_size(head));
    if (1 == size) {
        return head;
    }
    int half = size / 2;
    LList* tail = llist_split_after(head, half);
    printf("half == %i\n", half);
    head = NULL;
    head = llist_push(head, (void*) 9);
    head = llist_push(head, (void*) 8);
    head = llist_push(head, (void*) 4);
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 3);
    head = llist_push(head, (void*) 2);
    head = llist_push(head, (void*) 2);
    printf("== llist_sort end ==\n");
    return head;
}
