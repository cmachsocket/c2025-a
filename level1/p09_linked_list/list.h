#ifndef LIST_HEAD

#define LIST_HEAD
#define and &&
#define NOT_FIND_ERROR (-1)
#define OUT_OF_MEMORY_ERROR (-1)

typedef struct Node {
    int val;
    struct Node *next;
} Node;

typedef struct List {
    void (*add_new_node)(int);


    void (*reverse_list)();

    int (*size)();

    Node *(*head)();

    Node * (*tail)();
} List;

List *CreatList();

void add_new_node(int value);

void reverse_list();

int size();

Node *head();

Node *tail();


#endif
