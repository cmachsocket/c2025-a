#include "list.h"
#include <stdio.h>
const int N =10;
int Find_value(Node **, int);

void output_whole_list();

int main() {
    List *list = CreatList();
    for (int i = 1; i <= N; i++) {
        int tmp;
        scanf("%d", &tmp);
        list->add_new_node(tmp);
    }
    Node *iterator = list->head();
    int position = 0, tmp;
    output_whole_list();
    for (int i = 1; i <= 2; i++) {
        if ((tmp = Find_value(&iterator, 5)) != -1) {
            position += tmp;
            printf("the positon of number 5:%d\n", position);
        }
        else {
            puts("Not found!");
        }
    }

    puts("Reverse...");
    list->reverse_list();
    output_whole_list();
    return 0;
}

int Find_value(Node **iterator, int value) {
    int count = 1;
    for (; (*iterator) != NULL and (*iterator)->val != value;
           (*iterator) = (*iterator)->next, count++) {
    }
    if ((*iterator) == NULL) {
        return NOT_FIND_ERROR;
    } else {
        (*iterator) = (*iterator)->next;
        return count;
    }
}

void output_whole_list() {
    Node *iterator = head();
    for (; iterator != NULL; iterator = iterator->next) {
        printf("%d ", iterator->val);
    }
    puts("");
}
