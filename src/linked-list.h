struct LListType {
    void* val;
    struct LListType* next;
};
typedef struct LListType LList;

LList* llist_create_list();
LList* llist_pop(LList* head);
LList* llist_push(void* val, LList* next);
int llist_size(LList* head);

void llist_free(LList* head);
