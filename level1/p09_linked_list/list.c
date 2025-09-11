#include "list.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct DefineList {
    Node *tail, *head;
    int size;

    void (*_add_new_node)(struct DefineList *, int);


    void (*_reverse_list)(struct DefineList *);

    Node * (*_head)(const struct DefineList *);

    Node * (*_tail)(const struct DefineList *);

    int (*_size)(const struct DefineList *);
} DefineList;

void Add_new_node(DefineList *self, int value) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->val = value;
    node->next = NULL;
    (self->size)++;
    if (self->tail == NULL) {
        // 0个节点的情况
        self->head = self->tail = node;
        return;
    }
    self->tail->next = node;
    self->tail = node;
}

Node *Head(const DefineList *self) {
    return self->head;
}

Node *Tail(const DefineList *self) {
    return self->tail;
}

int Size(const DefineList *self) {
    return self->size;
}

void Reverse_list(DefineList *self) {
    if (self->head == self->tail) {
        fprintf(stderr, "No need to reversing!");
        return;
    }
    Node *new_head = NULL;
    self->tail = self->head;

    for (Node *next_node = self->head->next;; self->head = next_node, next_node = next_node->next) {
        self->head->next = new_head;
        new_head = self->head;
        if (next_node == NULL)break;
    }
    self->head = new_head;
}

static DefineList base_list = {NULL, NULL, 0, Add_new_node, Reverse_list, Head, Tail, Size};

List *CreatList() {
    List *list = (List *) malloc(sizeof(List));
    list->add_new_node = add_new_node;


    list->reverse_list = reverse_list;
    list->head = head;
    list->tail = tail;
    list->size = size;
    return list;
}

void add_new_node(int value) {
    base_list._add_new_node(&base_list, value);
}

void reverse_list() {
    base_list._reverse_list(&base_list);
}

int size() {
    return base_list._size(&base_list);
}

Node *head() {
    return base_list._head(&base_list);
}

Node *tail() {
    return base_list._tail(&base_list);
}
