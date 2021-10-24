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


static inline void swap(list_node_td *a, list_node_td *b)
{
    void *temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/*
 * These are templates for useful linked_list based functions
 * Sorts a linked list by a type specified by the macro call.
 * Can also be a type within a struct, in which case a struct_offs must be specified.
 */

#define LLIST_BUBBLE_SORT(type) \
static inline void llist_bubble_sort_##type(linked_list_td *_linked_list, size_t _struct_offs) \
{ \
    int _swapped = 0; \
    char *_tmp_ptr_1 = NULL; \
    char *_tmp_ptr_2 = NULL; \
    type *_##type_ptr1 = NULL; \
    type *_##type_ptr2 = NULL; \
    list_node_td *_ptr1 = NULL; \
    list_node_td *_lptr = NULL; \
 \
    if (_linked_list == NULL || !llist.count(_linked_list)) \
        return; \
 \
    do \
    { \
        _swapped = 0; \
        _ptr1 = _linked_list->head; \
 \
        while (_ptr1->next != _lptr) \
        { \
            _tmp_ptr_1 = _ptr1->data; \
            _tmp_ptr_2 = _ptr1->next->data; \
            _##type_ptr1 = (type *)(_tmp_ptr_1+_struct_offs); \
            _##type_ptr2 = (type *)(_tmp_ptr_2+_struct_offs); \
            if (*_##type_ptr1 > *_##type_ptr2) \
            { \
                swap(_ptr1, _ptr1->next); \
                _swapped = 1; \
            } \
            _ptr1 = _ptr1->next; \
        } \
        _lptr = _ptr1; \
 \
    } while (_swapped); \
}

/*
 * Removes duplicated of a linked list by a type specified by the macro call.
 * Can also be a type within a struct, in which case a struct_offs must be specified.
 * Also the element size needs to be specified.
 */
#define LLIST_UNIQ(type) \
static inline void llist_uniq_##type(linked_list_td *_uniq_list, linked_list_td *_linked_list, size_t _elem_size, size_t _struct_offs) \
{ \
    int _i = 0; \
    int _j = 0; \
    char *_llist_tmp = NULL; \
    char *_uniq_tmp = NULL; \
    type *_##type_ptr1 = NULL; \
    type *_##type_ptr2 = NULL; \
 \
    if (_linked_list == NULL || !llist.count(_linked_list) || _uniq_list == NULL) \
        return; \
 \
    _llist_tmp = llist.get_item_from_index(_linked_list, 0); \
    llist.append_item(_uniq_list, _llist_tmp, _elem_size); \
 \
    for(_i=0;_i<llist.count(_linked_list);_i++) \
    { \
        _llist_tmp = llist.get_item_from_index(_linked_list, _i); \
        _uniq_tmp = llist.get_item_from_index(_uniq_list, _j); \
        _##type_ptr1 = (type *)(_llist_tmp+_struct_offs); \
        _##type_ptr2 = (type *)(_uniq_tmp+_struct_offs); \
 \
        if(*_##type_ptr1 != *_##type_ptr2) \
        { \
            _j++; \
            llist.append_item(_uniq_list, _llist_tmp, _elem_size); \
        } \
    } \
}

/* As a start we have int based buble sort and int based uniq */
LLIST_BUBBLE_SORT(int)
LLIST_UNIQ(int)

#endif
