#include <stdio.h>
#include <stdlib.h>
#include <unity.h>
#include <linked_list.h>

void test_remove_first_single_node(void)
{
    linked_list_td my_list = { 0 };

    llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_EQUAL(1, llist.count(&my_list));

    llist.remove_front(&my_list);
    TEST_ASSERT_NULL(my_list.head);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));

    llist.destroy(&my_list);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));
    TEST_ASSERT_NULL(my_list.head);
}

void test_remove_second_node(void)
{
    linked_list_td my_list = { 0 };
    void *second_node = 0;

    llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_EQUAL(1, llist.count(&my_list));

    second_node = llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_NOT_NULL(my_list.head);
    TEST_ASSERT_NOT_NULL(second_node);
    TEST_ASSERT_EQUAL(2, llist.count(&my_list));

    llist.remove_entry(&my_list, second_node);
    TEST_ASSERT_EQUAL(1, llist.count(&my_list));

    llist.destroy(&my_list);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));
    TEST_ASSERT_NULL(my_list.head);
}

void test_remove_middle_node(void)
{
    linked_list_td my_list = { 0 };
    void *tmp_node = 0;

    llist.append(&my_list, NULL, NULL);
    tmp_node = llist.append(&my_list, NULL, NULL);
    llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_NOT_NULL(tmp_node);
    TEST_ASSERT_EQUAL(3, llist.count(&my_list));

    llist.remove_entry(&my_list, tmp_node);
    TEST_ASSERT_EQUAL(2, llist.count(&my_list));

    llist.destroy(&my_list);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));
    TEST_ASSERT_NULL(my_list.head);
}

void test_remove_last_node(void)
{
    linked_list_td my_list = { 0 };
    void *tmp_node = 0;

    llist.append(&my_list, NULL, NULL);
    llist.append(&my_list, NULL, NULL);
    tmp_node = llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_NOT_NULL(tmp_node);
    TEST_ASSERT_EQUAL(3, llist.count(&my_list));

    llist.remove_entry(&my_list, tmp_node);
    TEST_ASSERT_EQUAL(2, llist.count(&my_list));

    llist.destroy(&my_list);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));
    TEST_ASSERT_NULL(my_list.head);
}

void test_remove_first_node(void)
{
    linked_list_td my_list = { 0 };
    void *tmp_node = 0;

    llist.append(&my_list, NULL, NULL);
    tmp_node = llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_NOT_NULL(tmp_node);

    llist.append(&my_list, NULL, NULL);
    TEST_ASSERT_EQUAL(3, llist.count(&my_list));

    llist.remove_entry(&my_list, my_list.head);
    TEST_ASSERT_EQUAL(2, llist.count(&my_list));
    TEST_ASSERT_NOT_NULL(tmp_node);
    TEST_ASSERT_NOT_NULL(my_list.head);
    TEST_ASSERT_EQUAL(my_list.head, tmp_node);

    llist.destroy(&my_list);
    TEST_ASSERT_EQUAL(0, llist.count(&my_list));
    TEST_ASSERT_NULL(my_list.head);
}

void free_test_data(void *data) { free(data); }

void test_add_data_nodes(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

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

    /* Now check if we can get the data back from the list */
    list_node_td *list_node = llist.get_first(&my_list);
    my_test_data_td *test_data = list_node->data;
    TEST_ASSERT_EQUAL(42, test_data->x);
    TEST_ASSERT_EQUAL(43, test_data->y);
    TEST_ASSERT_EQUAL(44, test_data->blabla);

    /* Remove first node */
    llist.remove_front(&my_list);

    /* Now get the secont node, with the data allocated on the stack */
    list_node = llist.get_first(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(45, test_data->x);
    TEST_ASSERT_EQUAL(46, test_data->y);
    TEST_ASSERT_EQUAL(47, test_data->blabla);

    /* This will destroy all nodes and frees all data automatically, if
       a free function was given.
     */
    llist.destroy(&my_list);
}

void test_get_last(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 51;
    test_node->y = 52;
    test_node->blabla = 53;
    llist.append(&my_list, test_node, free_test_data);

    list_node_td *list_node = llist.get_last(&my_list);
    my_test_data_td *test_data = list_node->data;
    TEST_ASSERT_EQUAL(51, test_data->x);
    TEST_ASSERT_EQUAL(52, test_data->y);
    TEST_ASSERT_EQUAL(53, test_data->blabla);

    llist.destroy(&my_list);
}

void test_remove_first(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    void *tmp_node = llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 51;
    test_node->y = 52;
    test_node->blabla = 53;
    llist.append(&my_list, test_node, free_test_data);

    llist.remove_front(&my_list);
    TEST_ASSERT_EQUAL(my_list.head, tmp_node);

    llist.destroy(&my_list);
}

void test_remove_last(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    void *tmp_node = llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 51;
    test_node->y = 52;
    test_node->blabla = 53;
    llist.append(&my_list, test_node, free_test_data);

    llist.remove_last(&my_list);
    TEST_ASSERT_EQUAL(my_list.tail, tmp_node);

    llist.destroy(&my_list);
}

void test_remove_front_last(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    void *tmp_node = llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    llist.remove_last(&my_list);
    llist.remove_front(&my_list);
    TEST_ASSERT_EQUAL(my_list.tail, tmp_node);
    TEST_ASSERT_EQUAL(my_list.head, tmp_node);
    TEST_ASSERT_EQUAL(my_list.head, my_list.tail);

    llist.destroy(&my_list);
}

void test_remove_all(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    llist.remove_last(&my_list);
    llist.remove_front(&my_list);
    llist.remove_front(&my_list);
    TEST_ASSERT_EQUAL(my_list.head, my_list.tail);
    TEST_ASSERT_NULL(my_list.head);
    TEST_ASSERT_NULL(my_list.tail);

    llist.destroy(&my_list);
}

void test_prepend(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };
    my_test_data_td *test_data = NULL;

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    /* check for first entry*/
    list_node_td *list_node = llist.get_first(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(42, test_data->x);
    TEST_ASSERT_EQUAL(43, test_data->y);
    TEST_ASSERT_EQUAL(44, test_data->blabla);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 123;
    test_node->y = 456;
    test_node->blabla = 789;
    llist.prepend(&my_list, test_node, free_test_data);

    /* now check for first entry again */
    list_node = llist.get_first(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(123, test_data->x);
    TEST_ASSERT_EQUAL(456, test_data->y);
    TEST_ASSERT_EQUAL(789, test_data->blabla);

    llist.remove_last(&my_list);
    llist.remove_last(&my_list);
    llist.remove_front(&my_list);
    llist.remove_front(&my_list);
    TEST_ASSERT_EQUAL(my_list.head, my_list.tail);
    TEST_ASSERT_NULL(my_list.head);
    TEST_ASSERT_NULL(my_list.tail);

    llist.destroy(&my_list);
}

void test_append(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };
    my_test_data_td *test_data = NULL;

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    /* check for first entry*/
    list_node_td *list_node = llist.get_first(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(42, test_data->x);
    TEST_ASSERT_EQUAL(43, test_data->y);
    TEST_ASSERT_EQUAL(44, test_data->blabla);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 123;
    test_node->y = 456;
    test_node->blabla = 789;
    llist.prepend(&my_list, test_node, free_test_data);

    /* now check for last entry */
    list_node = llist.get_last(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(48, test_data->x);
    TEST_ASSERT_EQUAL(49, test_data->y);
    TEST_ASSERT_EQUAL(50, test_data->blabla);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 345;
    test_node->y = 678;
    test_node->blabla = 234;
    llist.append(&my_list, test_node, free_test_data);

    /* now check for last entry again */
    list_node = llist.get_last(&my_list);
    test_data = list_node->data;
    TEST_ASSERT_EQUAL(345, test_data->x);
    TEST_ASSERT_EQUAL(678, test_data->y);
    TEST_ASSERT_EQUAL(234, test_data->blabla);

    llist.remove_last(&my_list);
    llist.remove_last(&my_list);
    llist.remove_front(&my_list);
    llist.remove_front(&my_list);
    llist.remove_front(&my_list);
    TEST_ASSERT_EQUAL(my_list.head, my_list.tail);
    TEST_ASSERT_NULL(my_list.head);
    TEST_ASSERT_NULL(my_list.tail);

    llist.destroy(&my_list);
}

void test_get_empty_list(void)
{
    int *test_data = calloc(1, sizeof(int));
    *test_data = 42;
    linked_list_td my_list = { 0 };
    list_node_td *list_node = llist.get_first(&my_list);
    TEST_ASSERT_NULL(list_node);

    list_node = llist.get_last(&my_list); 
    TEST_ASSERT_NULL(list_node);

    /* Try to remove empty list */
    llist.remove_front(&my_list);
    llist.remove_last(&my_list);

    /* Now add one item and check */
    llist.append(&my_list, test_data, free);
    list_node = llist.get_first(&my_list);
    int *test_ptr = list_node->data;
    TEST_ASSERT_NOT_NULL(test_ptr);
    TEST_ASSERT_EQUAL(42, *test_ptr);

    llist.destroy(&my_list);
}

void test_get_from_index(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td *test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 42;
    test_node->y = 43;
    test_node->blabla = 44;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 45;
    test_node->y = 46;
    test_node->blabla = 47;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 48;
    test_node->y = 49;
    test_node->blabla = 50;
    llist.append(&my_list, test_node, free_test_data);

    test_node = calloc(1, sizeof(my_test_data_td));
    test_node->x = 51;
    test_node->y = 52;
    test_node->blabla = 53;
    llist.append(&my_list, test_node, free_test_data);

    list_node_td *list_node = llist.get_from_index(&my_list, 2);
    my_test_data_td *tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(48, tmp_data->x);
    TEST_ASSERT_EQUAL(49, tmp_data->y);
    TEST_ASSERT_EQUAL(50, tmp_data->blabla);

    list_node = llist.get_from_index(&my_list, 1);
    tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(45, tmp_data->x);
    TEST_ASSERT_EQUAL(46, tmp_data->y);
    TEST_ASSERT_EQUAL(47, tmp_data->blabla);

    /* Now remove one node */
    llist.remove_entry(&my_list, list_node);

    /* The last node was deleted, so when now trying to get index 1 we should get the same data
     * as we had when using index 2 before
     */
    list_node = llist.get_from_index(&my_list, 1);
    tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(48, tmp_data->x);
    TEST_ASSERT_EQUAL(49, tmp_data->y);
    TEST_ASSERT_EQUAL(50, tmp_data->blabla);

    llist.destroy(&my_list);
}

void test_get_item_from_index(void)
{
    typedef struct my_test_data_struct
    {
        int x;
        int y;
        int blabla;

    } my_test_data_td;

    linked_list_td my_list = { 0 };

    my_test_data_td test_node;
    test_node.x = 42;
    test_node.y = 43;
    test_node.blabla = 44;
    llist.append_item(&my_list, &test_node, sizeof(my_test_data_td));

    test_node.x = 45;
    test_node.y = 46;
    test_node.blabla = 47;
    llist.append_item(&my_list, &test_node, sizeof(my_test_data_td));

    test_node.x = 48;
    test_node.y = 49;
    test_node.blabla = 50;
    llist.append_item(&my_list, &test_node, sizeof(my_test_data_td));

    test_node.x = 51;
    test_node.y = 52;
    test_node.blabla = 53;
    llist.append_item(&my_list, &test_node, sizeof(my_test_data_td));

    list_node_td *list_node = llist.get_from_index(&my_list, 2);
    my_test_data_td *tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(48, tmp_data->x);
    TEST_ASSERT_EQUAL(49, tmp_data->y);
    TEST_ASSERT_EQUAL(50, tmp_data->blabla);

    list_node = llist.get_from_index(&my_list, 1);
    tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(45, tmp_data->x);
    TEST_ASSERT_EQUAL(46, tmp_data->y);
    TEST_ASSERT_EQUAL(47, tmp_data->blabla);

    /* Now remove one node */
    llist.remove_entry(&my_list, list_node);

    /* The last node was deleted, so when now trying to get index 1 we should get the same data
     * as we had when using index 2 before
     */
    list_node = llist.get_from_index(&my_list, 1);
    tmp_data = list_node->data;
    TEST_ASSERT_EQUAL(48, tmp_data->x);
    TEST_ASSERT_EQUAL(49, tmp_data->y);
    TEST_ASSERT_EQUAL(50, tmp_data->blabla);

    llist.destroy(&my_list);
}

void test_append_item(void)
{
    linked_list_td my_list = { 0 };

    /* Now add one item and check */
    llist.append_item(&my_list, &(int){123}, sizeof(int));
    llist.append_item(&my_list, &(int){456}, sizeof(int));
    llist.append_item(&my_list, &(int){789}, sizeof(int));

    list_node_td *list_node = llist.get_from_index(&my_list, 1);
    int *tmp = list_node->data;

    TEST_ASSERT_EQUAL(456, *tmp);

    llist.destroy(&my_list);
}

void test_prepend_item(void)
{
    linked_list_td my_list = { 0 };

    /* Now add one item and check */
    llist.prepend_item(&my_list, &(int){123}, sizeof(int));
    llist.prepend_item(&my_list, &(int){456}, sizeof(int));
    llist.prepend_item(&my_list, &(int){789}, sizeof(int));

    list_node_td *list_node = llist.get_from_index(&my_list, 0);
    int *tmp = list_node->data;

    TEST_ASSERT_EQUAL(789, *tmp);

    llist.destroy(&my_list);
}

void test_bubble_sort(void)
{
    linked_list_td my_list = { 0 };

    /* Now add one item and check */
    llist.append_item(&my_list, &(int){999}, sizeof(int));
    llist.append_item(&my_list, &(int){123}, sizeof(int));
    llist.append_item(&my_list, &(int){789}, sizeof(int));
    llist.append_item(&my_list, &(int){1200}, sizeof(int));
    llist.append_item(&my_list, &(int){23}, sizeof(int));
    llist.append_item(&my_list, &(int){76}, sizeof(int));

    int *tmp = llist.get_item_from_index(&my_list, 0);
    TEST_ASSERT_EQUAL(999, *tmp);

    tmp = llist.get_item_from_index(&my_list, 1);
    TEST_ASSERT_EQUAL(123, *tmp);

    tmp = llist.get_item_from_index(&my_list, 2);
    TEST_ASSERT_EQUAL(789, *tmp);

    /* Now sort ascending */
    llist_bubble_sort_int(&my_list, 0);

    tmp = llist.get_item_from_index(&my_list, 0);
    TEST_ASSERT_EQUAL(23, *tmp);

    tmp = llist.get_item_from_index(&my_list, 1);
    TEST_ASSERT_EQUAL(76, *tmp);

    tmp = llist.get_item_from_index(&my_list, 2);
    TEST_ASSERT_EQUAL(123, *tmp);

    llist.destroy(&my_list);
}

void test_uniq(void)
{
    linked_list_td my_list = { 0 };
    linked_list_td my_list_uniq = { 0 };

    /* Now add one item and check */
    llist.append_item(&my_list, &(int){999}, sizeof(int));
    llist.append_item(&my_list, &(int){123}, sizeof(int));
    llist.append_item(&my_list, &(int){789}, sizeof(int));
    llist.append_item(&my_list, &(int){789}, sizeof(int));

    int *tmp = llist.get_item_from_index(&my_list, 0);
    TEST_ASSERT_EQUAL(999, *tmp);

    tmp = llist.get_item_from_index(&my_list, 1);
    TEST_ASSERT_EQUAL(123, *tmp);

    tmp = llist.get_item_from_index(&my_list, 2);
    TEST_ASSERT_EQUAL(789, *tmp);

    tmp = llist.get_item_from_index(&my_list, 3);
    TEST_ASSERT_EQUAL(789, *tmp);

    TEST_ASSERT_EQUAL(4, llist.count(&my_list));

    /* Now sort ascending */
    llist_uniq_int(&my_list_uniq, &my_list, sizeof(int), 0);

    tmp = llist.get_item_from_index(&my_list_uniq, 0);
    TEST_ASSERT_EQUAL(999, *tmp);

    tmp = llist.get_item_from_index(&my_list_uniq, 1);
    TEST_ASSERT_EQUAL(123, *tmp);

    tmp = llist.get_item_from_index(&my_list_uniq, 2);
    TEST_ASSERT_EQUAL(789, *tmp);

    /* The secont 789 should be removed now */
    TEST_ASSERT_EQUAL(3, llist.count(&my_list_uniq));

    llist.destroy(&my_list);
    llist.destroy(&my_list_uniq);
}

void setUp(void)
{
    //printf("setUp\n");
}

void tearDown(void)
{
    //printf("tearDown\n");
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_remove_first_single_node);
    RUN_TEST(test_remove_second_node);
    RUN_TEST(test_remove_middle_node);
    RUN_TEST(test_remove_last_node);
    RUN_TEST(test_remove_first_node);
    RUN_TEST(test_add_data_nodes);
    RUN_TEST(test_get_last);
    RUN_TEST(test_remove_first);
    RUN_TEST(test_remove_last);
    RUN_TEST(test_remove_front_last);
    RUN_TEST(test_remove_all);
    RUN_TEST(test_prepend);
    RUN_TEST(test_append);
    RUN_TEST(test_get_empty_list);
    RUN_TEST(test_get_from_index);
    RUN_TEST(test_get_item_from_index);
    RUN_TEST(test_append_item);
    RUN_TEST(test_prepend_item);
    RUN_TEST(test_bubble_sort);
    RUN_TEST(test_uniq);

    return UNITY_END();
}
