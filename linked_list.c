#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linked_list.h>

static void linked_list_remove_entry(linked_list_td *list, void *entry)
{
    list_node_td **curr = &list->head;
    list_node_td *list_entry = entry;
    while(*curr != list_entry)
        curr = &(*curr)->next;
    *curr = list_entry->next;
    if(list_entry->free_func != NULL)
        list_entry->free_func(list_entry->data);
    free(list_entry);
}

static void *linked_list_get_first(linked_list_td *list)
{
    return list->head->data;
}

static void linked_list_remove_front(linked_list_td *list)
{
    linked_list_remove_entry(list, list->head);
}

static void *linked_list_append(linked_list_td *list, void *node_data, void (*free_func)(void *data))
{
    list_node_td **curr = &list->head;
    list_node_td *node = calloc(1, sizeof(list_node_td));
    node->data = node_data;
    node->free_func = free_func;
    while(*curr != NULL)
        curr = &(*curr)->next;
    *curr = node;
    return node;
}

static void linked_list_destroy(linked_list_td *list)
{
    list_node_td **curr = &list->head;
    while((*curr) != NULL)
    {
        if((*curr)->free_func != NULL)
        {
            (*curr)->free_func((*curr)->data);
            //(*curr)->free_func = NULL;
            //(*curr)->data = NULL;
        }
        free(*curr);
        curr = &(*curr)->next;
    }

    // list_node_td *curr = list->head;
    // list_node_td *prev = NULL;
    // if(list->head == NULL) return;
    // while(curr->next != NULL)
    // {
    //     prev = curr;
    //     curr = curr->next;
    //     if(prev->free_func != NULL)
    //     {
    //         prev->free_func(prev->data);
    //         prev->free_func = NULL;
    //         prev->data = NULL;
    //     }
    //     free(prev);
    //     prev = NULL;
    // }
    // if(curr->free_func != NULL)
    // {
    //     curr->free_func(curr->data);
    //     curr->free_func = NULL;
    //     curr->data = NULL;
    // }
    // free(curr);
    // curr = NULL;
    // list->head = NULL;
}

static int linked_list_count(linked_list_td *list)
{
    int count = 0;
    list_node_td *curr = list->head;
    if(list->head == NULL)
    {
        return 0;
    }
    while (curr->next != NULL)
    {
        count++;
        curr = curr->next;
    }
    return ++count;
}

static void linked_list_print(linked_list_td *list)
{
    list_node_td *curr = list->head;
    if(list->head == NULL)
    {
        printf("Nothing to print\n");
        return;
    }
    while (curr->next != NULL)
    {
        printf("entry: %p\n", (void *)curr);
        curr = curr->next;
    }
    printf("entry: %p\n", (void *)curr);
}

linked_list_interface_td llist =
{
    .remove_entry = linked_list_remove_entry,
    .remove_front = linked_list_remove_front,
    .append = linked_list_append,
    .destroy = linked_list_destroy,
    .count = linked_list_count,
    .get_first = linked_list_get_first,
    .print = linked_list_print,
};
