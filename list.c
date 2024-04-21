#include "list.h"
#include <stdio.h>
#include <stdlib.h>

lnode *lst_create_lnode(void *dat) {
    lnode *new_node = (lnode *)malloc(sizeof(lnode));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nouveau noeud\n");
        return NULL;
    }
    new_node->data = dat;
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

list *lst_create_list() {
    list *new_list = (list *)malloc(sizeof(list));
    if (new_list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la nouvelle liste\n");
        return NULL;
    }
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

void lst_delete_list(list *lst) {
    lnode *current = lst->head;
    while (current != NULL) {
        lnode *temp = current;
        current = current->next;
        free(temp);
    }
    free(lst);
}

void lst_insert_tail(list *lst, lnode *pnew) {
    if (lst->head == NULL) {
        lst->head = pnew;
    } else {
        lst->tail->next = pnew;
        pnew->prev = lst->tail;
    }
    lst->tail = pnew;
}

void lst_erase(list *lst) {
    lnode *current = lst->head;
    while (current != NULL) {
        lnode *temp = current;
        current = current->next;
        free(temp);
    }
    lst->head = NULL;
    lst->tail = NULL;
}

lnode *get_first_node(list *lst) {
    return lst->head;
}

lnode *get_last_node(list *lst) {
    return lst->tail;
}

lnode *get_next_node(list *lst, lnode *lnode) {
    return lnode->next;
}

void *get_previous_elem(list *lst, lnode *lnode) {
    if (lnode->prev != NULL) {
        return lnode->prev->data;
    } else {
        return NULL;
    }
}
