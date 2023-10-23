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

LList* llist_push(void* val, LList* next) {
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

void llist_free(LList* head) {
    while (head != NULL) {
        LList* next = head->next;
        free(head);
        head = next;
    }
}

