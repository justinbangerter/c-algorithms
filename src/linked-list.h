struct LListType {
    void* val;
    struct LListType* next;
};
typedef struct LListType LList;

/**
 * Create a node with the given val
 */
LList* llist_node(void* val);

/**
 * Get a node from the list at the given index
 */
LList* llist_get(LList* list, int index);

/**
 * Pop the first element off of this list, delete the head, and return the tail.
 *
 * @param LList* head the first element of the list
 * @return the value of the head
 */
void* llist_pop(LList* head);

/**
 * Push a new node with the given value onto the front of this list.
 * @param LList* tail push to this list
 * @param void* val the value to push
 * @return the new list head
 */
LList* llist_push(LList* tail, void* val);

/**
 * Insert the given value after this node.
 * If the node is an empty list marker, the new value will be inserted before it.
 *
 * @param LList* head insert a node with val after this node
 * @param void* val the value to insert
 * @return the newly created and inserted node
 */
LList* llist_insert_after(LList* head, void* val);

/**
 * Get the number of nodes in the list
 */
int llist_size(LList* head);

/**
 * Free all of the memory used by this list.
 * If the list elements have allocated memory, they should be freed first.
 *
 * @param LList* head the list to free
 */
void llist_free(LList* head);
