#include <stdlib.h>
#include "linked-list.h"

Node* EmptyList() {
    return malloc(sizeof(Node));
}

Node* Pop(Node* head) {
    Node* tail = head->tail;
    head->tail = NULL;
    return tail;
}

Node* Push(void* val, Node* tail) {
    Node* node = malloc(sizeof(Node));
    node->val = val;
    node->tail = tail;
    return node;
}

int SizeOf(Node* head) {
    int size = -1;
    while(head != NULL) {
        size++;
        head = head->tail;
    }
    return size;
}

void FreeList(Node* head) {
    while (head != NULL) {
        Node* next = head->tail;
        // values should always come from stack variables
        //free(head->val);
        free(head);
        head = next;
    }
}
