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
 * Split a list just after the given index.
 * ex: llist_split(head, 1) splits the list after the second element and
 *    returns the head of the new list (the element that was at index 2).
 */
LList* llist_split_after(LList* head, int index);

/**
 * Free all of the memory used by this list.
 * If the list elements use allocated memory, you must free them yourself.
 *
 * @param LList* head the list to free
 */
void llist_free(LList* head);

/**
 * Sort a linked list.
 * Alters the provided list.
 * The head of the given list is not guaranteed to be the head
 * of the sorted list.
 * @param LList* head the head of the list to sort
 * @param int (*cmp)(const void *, const void *) comparator function
 */
LList* llist_sort(LList* head, int (*cmp)(const void *, const void *));

/**
 * Use binary search to find the index of a value in a sorted list.
 * @param LList* head the head of the sorted list
 * @param void* val
 * @param int (*cmp)(const void *, const void *) return positive int
 *  if first arg is greater than second arg, else return negative
 * @return the index of the found value or -1 if not found
 */
int llist_bfind_index(LList* head, void* val, int (*cmp)(const void *, const void *));
