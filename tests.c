#include <stdio.h>
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
    return UNITY_END();
}
