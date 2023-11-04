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

LList* llist_sort(LList* head, int (*cmp)(const void*, const void*)) {
    /* merge sort */
    int size = llist_size(head);
    if (1 == size) {
        return head;
    }

    /* split array */
    int half = size / 2;
    LList* tail = llist_split_after(head, half - 1);

    /* sort both arrays */
    head = llist_sort(head, cmp);
    tail = llist_sort(tail, cmp);

    /* create a dummy node to pop off at the end */
    LList* new_head = llist_node(NULL);
    LList* new_end = new_head; /* where to append new nodes */

    while (head != NULL || tail != NULL) {
        if (head == NULL) {
            new_end->next = tail;
            tail = tail->next;
        }
        else if (tail == NULL) {
            new_end->next = head;
            head = head->next;
        }
        else {
            if (cmp((void*) &head->val, (void*) &tail->val) < 0) {
                /* head is less than tail */
                new_end->next = head;
                head = head->next;
            }
            else {
                new_end->next = tail;
                tail = tail->next;
            }
            new_end = new_end->next;
            new_end->next = NULL;
        }
    }

    head = new_head->next;
    llist_pop(new_head); /* free the dummy node */
    return head;
}

int llist_bfind_index(LList* head, void* val, int (*cmp)(const void *, const void *)) {
    /*
     * The key to keeping the binary search algorithm simple is to
     * modify the bounds and calculate the index from the bounds.
     */
    int lower_bound = 0;
    int upper_bound = llist_size(head) - 1;
    while (1) {
        if (upper_bound < lower_bound) {
            return -1;
        }

        int index = (upper_bound + lower_bound) / 2;
        LList* node = llist_get(head, index);

        if (node->val == val) {
            return index;
        }

        if (cmp((void*) &node->val, &val) > 0) {
            upper_bound = index - 1;
        }
        else {
            lower_bound = index + 1;
        }
    }
}

int llist_find_index(LList* head, void* val) {
    int index = 0;
    while (head != NULL) {
        if (head->val == val) {
            return index;
        }
        head = head->next;
        index++;
    }
    return -1;
}
