#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linked_list.h>

static void linked_list_remove_entry(linked_list_td *list, void *entry)
{
    list_node_td *curr = entry;
    list_node_td *tmp = NULL;

    if(entry == NULL)
        return;

    if(entry == list->head)
        list->head = curr->next;

    if(entry == list->tail)
        list->tail = curr->prev;

    tmp = curr->prev;
    if(tmp != NULL)
        tmp->next = curr->next;

    tmp = curr->next;
    if(tmp != NULL)
        tmp->prev = curr->prev;

    if(curr->free_func)
    {
        curr->free_func(curr->data);
        curr->free_func = NULL;
        curr->data = NULL;
    }
    free(curr);
    list->count--;
}

static void *linked_list_get_first(linked_list_td *list)
{
    if((list->head == NULL) || (list->head->data == NULL)) return NULL;
    return list->head;
}

static void *linked_list_get_last(linked_list_td *list)
{
    if((list->tail == NULL) || (list->tail->data == NULL)) return NULL;
    return list->tail;
}

static void *linked_list_get_next(linked_list_td *list, void *entry)
{
    (void) list;
    list_node_td *curr = entry;

    if(entry == NULL)
        return NULL;

    if(curr->next == NULL)
        return NULL;

    return curr->next;
}

static void *linked_list_get_prev(linked_list_td *list, void *entry)
{
    (void) list;
    list_node_td *curr = entry;

    if(entry == NULL)
        return NULL;

    if(curr->prev == NULL)
        return NULL;

    return curr->prev;
}

static void *linked_list_get_from_index(linked_list_td *list, int index)
{
    int i = 0;
    list_node_td *curr = list->head;

    if( (list->head == NULL) || ( index >= list->count))
        return NULL;

    for(i=0;i<index;i++)
    {
        curr = curr->next;
    }

    return curr;
}

static void *linked_list_get_item_from_index(linked_list_td *list, int index)
{
    int i = 0;
    list_node_td *curr = list->head;

    if( (list->head == NULL) || ( index >= list->count))
        return NULL;

    for(i=0;i<index;i++)
    {
        curr = curr->next;
    }

    return curr->data;
}

static void linked_list_remove_front(linked_list_td *list)
{
    linked_list_remove_entry(list, list->head);
}

static void linked_list_remove_last(linked_list_td *list)
{
    linked_list_remove_entry(list, list->tail);
}

static void *linked_list_append(linked_list_td *list, void *node_data, void (*free_func)(void *data))
{
    list_node_td *curr = list->tail;
    list_node_td *node = calloc(1, sizeof(list_node_td));
    node->data = node_data;
    node->free_func = free_func;

    if(list->count == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        curr->next = node;
        node->prev = curr;
        list->tail = node;
    }

    list->count++;
    return node;
}

static void *linked_list_prepend(linked_list_td *list, void *node_data, void (*free_func)(void *data))
{
    list_node_td *curr = list->head;
    list_node_td *node = calloc(1, sizeof(list_node_td));
    node->data = node_data;
    node->free_func = free_func;

    if(list->count == 0)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        curr->prev = node;
        node->next = curr;
        list->head = node;
    }

    list->count++;
    return node;
}

static void *linked_list_append_item(linked_list_td *list, void *data, int size)
{
    void *tmp_data = malloc(size);
    memcpy(tmp_data, data, size);
    return linked_list_append(list, tmp_data, free);
}

static void *linked_list_prepend_item(linked_list_td *list, void *data, int size)
{
    void *tmp_data = malloc(size);
    memcpy(tmp_data, data, size);
    return linked_list_prepend(list, tmp_data, free);
}

static void linked_list_destroy(linked_list_td *list)
{
    int i = 0;
    int count = list->count;
    list_node_td *curr = list->head;
    list_node_td *prev = NULL;
    if(list->head == NULL) return;
    for(i=0;i<count;i++)
    {
        prev = curr;
        curr = curr->next;
        linked_list_remove_entry(list, prev);
    }
    list->head = NULL;
    list->tail = NULL;
}

static int linked_list_count(linked_list_td *list)
{
    return list->count;
}

static void linked_list_print(linked_list_td *list)
{
    int i = 0;
    list_node_td *curr = list->head;
    if(list->head == NULL)
    {
        printf("Nothing to print\n");
        return;
    }
    printf("list count %d\n", list->count);
    for(i=0;i<list->count;i++)
    {
        printf("entry: %p\n", (void *)curr);
        curr = curr->next;
    }
}

linked_list_interface_td llist =
{
    .remove_entry = linked_list_remove_entry,
    .remove_front = linked_list_remove_front,
    .remove_last = linked_list_remove_last,
    .append = linked_list_append,
    .prepend = linked_list_prepend,
    .append_item = linked_list_append_item,
    .prepend_item = linked_list_prepend_item,
    .destroy = linked_list_destroy,
    .count = linked_list_count,
    .get_first = linked_list_get_first,
    .get_last = linked_list_get_last,
    .get_next = linked_list_get_next,
    .get_prev = linked_list_get_prev,
    .get_from_index = linked_list_get_from_index,
    .get_item_from_index = linked_list_get_item_from_index,
    .print = linked_list_print,
};
