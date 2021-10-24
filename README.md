# linked_list_c
This is a simple double linked list implemenation in C. The implemenation focuses on simplicity and ease of use.

This repo contains an example CMakeLists.txt but it is sufficient to just integrate linked_list.c and linked_list.h into
your project and you should be ready to go.

main.c contains an example usage.  
tests.c contains unity tests.  
valgrind.sh executes the tests with memchecks.  

## Notes
This implementation is not thread safe! If you want to use this in a multithreaded environment you need to care for thread-safety outside of
the linked list. E.g. adding mutex-lock and mutex-unlock before and after every linked list method call.

## These are the methods available:

```C
typedef struct linked_list_interface_struct
{
    void (*remove_entry)(linked_list_td *list, void *entry);
    void (*remove_front)(linked_list_td *list);
    void (*remove_last)(linked_list_td *list);
    void *(*append)(linked_list_td *list, void *node_data, void (*free_func)(void *data));
    void *(*prepend)(linked_list_td *list, void *node_data, void (*free_func)(void *data));
    void (*destroy)(linked_list_td *list);
    int (*count)(linked_list_td *list);
    void *(*get_first)(linked_list_td *list);
    void *(*get_last)(linked_list_td *list);
    void *(*get_from_index)(linked_list_td *list, int index);
    void (*print)(linked_list_td *list);

} linked_list_interface_td;
```


### Create your list:
```C
linked_list_td my_list = { 0 };
```

### Append an int to your list. If you add a free-function then the node will be freed automatically by the linked list when any remove method or destroy method is called. The free function can also be any custom function or destructor with a "void free_test_data(void *data)" function signature.
```C
int *test_node = calloc(1, sizeof(int));
*test_node = 42;
llist.append(&my_list, test_node, free);
```

It is also possible to directly add an int into the list. Internally memory will be allocated and automatically freed, when
the node is destroyed
```C
llist.append_item(&my_list, &(int){123}, sizeof(int));
```

### Prepend an int to your list. Otherwise same as append.
```C
int *test_node = calloc(1, sizeof(int));
*test_node = 42;
llist.prepend(&my_list, test_node, free);
```

Convenient prepending. Same as append_item
```C
llist.prepend_item(&my_list, &(int){123}, sizeof(int));
```

### Get first and last entry.
```C
list_node_td *list_node = llist.get_first(&my_list);
int *test_first = list_node->data;

list_node_td *list_node = llist.get_last(&my_list);
int *test_last = list_node->data;
```

### Get node via index.
```C
list_node_td *list_node = llist.get_from_index(&my_list, 1);
int *test_index = list_node->data;
```

### Get item via index.
```C
int *test_index = llist.get_item_from_index(&my_list, 1);
```

### Remove first and last entry.
```C
llist.remove_front(&my_list);
llist.remove_last(&my_list);
```

### Remove a specific node from the list.
```C
int *test_node = llist.append(&my_list, NULL, NULL);
llist.remove_entry(&my_list, test_node);
```

### Destroy a complete list.
```C
llist.destroy(&my_list);
```

### Other self explaining methods.
```C
llist.print(&my_list);
llist.count(&my_list);
```

### Sort a linked list in ascending order.
```C
llist.append_item(&my_list, &(int){999}, sizeof(int));
llist.append_item(&my_list, &(int){123}, sizeof(int));
llist.append_item(&my_list, &(int){789}, sizeof(int));
llist.append_item(&my_list, &(int){1200}, sizeof(int));
llist.append_item(&my_list, &(int){23}, sizeof(int));
llist.append_item(&my_list, &(int){76}, sizeof(int));

llist_bubble_sort_int(&my_list, 0);
```

### Remove duplicates.
```C
llist.append_item(&my_list, &(int){999}, sizeof(int));
llist.append_item(&my_list, &(int){123}, sizeof(int));
llist.append_item(&my_list, &(int){789}, sizeof(int));
llist.append_item(&my_list, &(int){789}, sizeof(int));

llist_uniq_int(&my_list_uniq, &my_list, sizeof(int), 0);
```

## Example usage:

```C
#include <stdio.h>
#include <stdlib.h>
#include <linked_list.h>

typedef struct my_test_data_struct
{
    int x;
    int y;
    int blabla;

} my_test_data_td;

void free_test_data(void *data)
{
    printf("BLABLABLA\n");
    free(data);
}

int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
    /* initialize test list */
    linked_list_td my_list = { 0 };

    /* Now allocate some data for putting into the list */
    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;

    /* Add the data to the list, don't forget to add a free function
       so the internal list function can free it for you
     */
    llist.append(&my_list, test_node, free_test_data);

    /* It's also possible to add data to the list which is allocated on the stack.
       Be aware that it the list node will point to garbage if the data goes out of
       scope.
     */
    my_test_data_td test_node2 = { 45, 46, 47};
    llist.append(&my_list, &test_node2, NULL);

    /* Print current node pointer */
    llist.print(&my_list);

    /* Now check if we can get the data back from the list */
    my_test_data_td *test_data = llist.get_first(&my_list);
    printf("%d %d %d\n", test_data->x, test_data->y, test_data->blabla);

    /* Remove first node */
    llist.remove_front(&my_list);

    /* Now get the secont node, with the data allocated on the stack */
    test_data = llist.get_first(&my_list);
    printf("%d %d %d\n", test_data->x, test_data->y, test_data->blabla);

    /* This will destroy all nodes and frees all data automatically, if
       a free function was given.
     */
    llist.destroy(&my_list);
    llist.print(&my_list);
}
```

