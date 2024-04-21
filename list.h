#ifndef _LIST_H_
#define _LIST_H_

typedef struct lnode_ {
    void *data;
    struct lnode_ *prev;
    struct lnode_ *next;
} lnode;

typedef struct list_ {
    lnode *head;
    lnode *tail;
} list;

typedef list Cdataframe;


lnode *lst_create_lnode(void *dat);
list *lst_create_list();
void lst_delete_list(list * lst);
void lst_insert_head(list * lst, lnode * pnew);
void lst_insert_tail(list * lst, lnode * pnew);
void lst_insert_after(list * lst, lnode * pnew, lnode * ptr);
void lst_delete_head(list * lst);
void lst_delete_tail(list * lst);
void lst_delete_lnode(list * lst, lnode * ptr);
void lst_erase(list * lst);
lnode *get_first_node(list * lst);
lnode *get_last_node(list * lst);
lnode *get_next_node(list * lst, lnode * lnode);
void *get_previous_elem(list * lst, lnode * lnode);


#endif 