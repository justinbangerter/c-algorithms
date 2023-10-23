#include <stdlib.h>
#include "linked-list.h"

LList* llist_create_list() {
    return malloc(sizeof(LList));
}

LList* llist_pop(LList* head) {
    LList* next = head->next;
    head->next = NULL;
    return next;
}

LList* llist_push(void* val, LList* next) {
    LList* LList = malloc(sizeof(LList));
    LList->val = val;
    LList->next = next;
    return LList;
}

int llist_size(LList* head) {
    int size = -1;
    while(head != NULL) {
        size++;
        head = head->next;
    }
    return size;
}

void llist_free(LList* head) {
    while (head != NULL) {
        LList* next = head->next;
        // values should always come from stack variables
        //free(head->val);
        free(head);
        head = next;
    }
}
