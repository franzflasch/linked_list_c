# linked_list_c
This is a simple double linked list implemenation in C

The implemenation focusses on simplicity and ease of use.

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
    void (*print)(linked_list_td *list);

} linked_list_interface_td;
```


### Create your list:
```C
linked_list_td my_list = { 0 };
```

### Append an int to your list, the free function can also be any custom function or destructor with a "void free_test_data(void *data)" function signature.
```C
int *test_node = calloc(1, sizeof(int));
*test_node = 42;
llist.append(&my_list, test_node, free);
```

### Prepend an int to your list, the free function can also be any custom function or destructor with a "void free_test_data(void *data)" function signature.
```C
int *test_node = calloc(1, sizeof(int));
*test_node = 42;
llist.prepend(&my_list, test_node, free);
```

### Get first and last entry.
```C
int *test_first = llist.get_first(&my_list);
int *test_last = llist.get_last(&my_list);
```

### Remove first and last entry.
```C
llist.remove_front(&my_list);
llist.remove_last(&my_list);
```

### Remove a specific node from the list.
```C
int *test_node = llist.append(&my_list, NULL, NULL);
llist.remove_entry(&my_list, second_node);
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

## Example usage:

```C
/* initialize test list */
linked_list_td my_list = { 0 };

/* Now allocate some data for putting into the list */
my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
test_node->x = 42;
test_node->y = 43;
test_node->blabla = 44;

/* Add the data to the list, don't forget to add a free function
   so the internal list function can free it for you.
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
```

