#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linked_list.h>

static void linked_list_remove_entry(linked_list_td *list, void *entry)
{
    int i = 0;
    list_node_td **curr = &list->head;
    list_node_td *list_entry = entry;
    for(i=0;i<list->count;i++)
    {
        if(*curr == list_entry) break;
        curr = &(*curr)->next;
    }
    if(i==list->count) return;
    *curr = list_entry->next;
    if(list_entry->free_func != NULL)
        list_entry->free_func(list_entry->data);
    free(list_entry);
    list->count--;
}

static void *linked_list_get_first(linked_list_td *list)
{
    return list->head->data;
}

static void *linked_list_get_last(linked_list_td *list)
{
    int i = 0;
    list_node_td *curr = list->head;
    if(list->head == NULL)
        return NULL;
    for(i=0;i<(list->count-1);i++)
        curr = curr->next;
    return curr->data;
}

static void linked_list_remove_front(linked_list_td *list)
{
    linked_list_remove_entry(list, list->head);
}

static void *linked_list_append(linked_list_td *list, void *node_data, void (*free_func)(void *data))
{
    int i = 0;
    list_node_td **curr = &list->head;
    list_node_td *node = calloc(1, sizeof(list_node_td));
    node->data = node_data;
    node->free_func = free_func;
    for(i=0;i<list->count;i++)
        curr = &(*curr)->next;
    *curr = node;
    list->count++;
    return node;
}

static void linked_list_destroy(linked_list_td *list)
{
    int i = 0;
    list_node_td *curr = list->head;
    list_node_td *prev = NULL;
    if(list->head == NULL) return;
    for(i=0;i<list->count;i++)
    {
        prev = curr;
        curr = curr->next;
        if(prev->free_func)
        {
            prev->free_func(prev->data);
            prev->free_func = NULL;
            prev->data = NULL;
        }
        free(prev);
        prev = NULL;
    }
    list->head = NULL;
    list->count = 0;
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
    .append = linked_list_append,
    .destroy = linked_list_destroy,
    .count = linked_list_count,
    .get_first = linked_list_get_first,
    .get_last = linked_list_get_last,
    .print = linked_list_print,
};
