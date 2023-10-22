struct NodeType {
    void* val;
    struct NodeType* tail;
};

typedef struct NodeType Node;

Node* EmptyList();
Node* Pop(Node* head);
Node* Push(void* val, Node* tail);
int SizeOf(Node* head);

void FreeList(Node* head);
