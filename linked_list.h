#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct list_node_struct
{
    void *data;
    void (*free_func)(void *data);
    struct list_node_struct *next;
    struct list_node_struct *prev;

} list_node_td;

typedef struct linked_list_struct
{
    list_node_td *head;
    list_node_td *tail;
    int count;

} linked_list_td;

typedef struct linked_list_interface_struct
{
    void (*remove_entry)(linked_list_td *list, void *entry);
    void (*remove_front)(linked_list_td *list);
    void (*remove_last)(linked_list_td *list);
    void *(*append)(linked_list_td *list, void *node_data, void (*free_func)(void *data));
    void *(*prepend)(linked_list_td *list, void *node_data, void (*free_func)(void *data));
    void *(*append_item)(linked_list_td *list, void *data, int size);
    void *(*prepend_item)(linked_list_td *list, void *data, int size);
    void (*destroy)(linked_list_td *list);
    int (*count)(linked_list_td *list);
    void *(*get_first)(linked_list_td *list);
    void *(*get_last)(linked_list_td *list);
    void *(*get_from_index)(linked_list_td *list, int index);
    void *(*get_item_from_index)(linked_list_td *list, int index);
    void (*print)(linked_list_td *list);

} linked_list_interface_td;

extern linked_list_interface_td llist;

#endif
