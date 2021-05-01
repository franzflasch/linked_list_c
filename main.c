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
    list_node_td *list_node = llist.get_first(&my_list);
    my_test_data_td *test_data = list_node->data;
    printf("%d %d %d\n", test_data->x, test_data->y, test_data->blabla);

    /* Remove first node */
    llist.remove_front(&my_list);

    /* Now get the secont node, with the data allocated on the stack */
    list_node = llist.get_first(&my_list);
    test_data = list_node->data;
    printf("%d %d %d\n", test_data->x, test_data->y, test_data->blabla);

    /* This will destroy all nodes and frees all data automatically, if
       a free function was given.
     */
    llist.destroy(&my_list);
    llist.print(&my_list);
}
