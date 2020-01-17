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
    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;

    llist.append(&my_list, test_node, free_test_data);

    llist.print(&my_list);

    my_test_data_td *test_data = llist.get_first(&my_list);
    printf("%d %d %d\n", test_data->x, test_data->y, test_data->blabla);

    llist.destroy(&my_list);
    llist.print(&my_list);
}
