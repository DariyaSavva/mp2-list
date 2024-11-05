#include "tlist.h"

#include <gtest.h>

TEST(List, can_create_list_with_positive_length)
{
  ASSERT_NO_THROW(List<int> list(5));
}

TEST(List, throws_when_create_list_with_negative_length)
{
  ASSERT_ANY_THROW(List<int> list(-5));
}

TEST(List, can_create_list_with_null_length)
{
    ASSERT_NO_THROW(List<int> list(0));
}

TEST(List, can_create_copied_list)
{
  List<int> list1(10);

  ASSERT_NO_THROW(List<int> list2(list1));
}

TEST(List, can_create_copied_empty_list)
{
    List<int> list1(0);
    ASSERT_NO_THROW(List<int> list2(list1));
}

TEST(List, can_create_list_without_parameters)
{
    ASSERT_NO_THROW(List<int> list());
}

TEST(List, copied_list_is_equal_to_source_one)
{
    List<int> list1(9, -5);
    for (int i = 0; i < 4; i++) {
        list1.insert_front(i);
    }
    List<int> list2(list1);
    EXPECT_EQ(true,list1==list2);
}

TEST(List, copied_empty_list_is_equal_to_source_one)
{
    List<int>  list1(0);
    List<int> list2(list1);
    EXPECT_EQ(true,list1==list2);
}

TEST(List, copied_list_has_its_own_memory)
{
    List<int> list1(9, -5);
    for (int i = 0; i < 4; i++) {
        list1.insert_front(i);
    }
    List<int> list2(list1);
    EXPECT_NE(&list2[0], &list1[0]);
}



TEST(List, throws_when_get_element_with_negative_index)
{
  List<int> list1(9, 7);
  ASSERT_ANY_THROW(list1[-1]);
}

TEST(List, throws_an_exception_if_we_access_an_empty_list)
{
    List<int> list1(0);
    ASSERT_ANY_THROW(list1[0]);
}

TEST(List, throws_when_get_element_with_too_large_index)
{
    List<int> list1(9, 7);
    ASSERT_ANY_THROW(list1[9]);
}


TEST(List, can_assign_list_to_itself)
{
    List<int> list(4);
    list.insert_front(2);
    list.insert_front(1);
    list = list;

    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 2);
}

TEST(List, can_assign_lists_of_equal_size)
{
    List<int> list1(5, 0), list2(5, -1);
    list1 = list2;
    EXPECT_EQ(true,list1==list2);
}

TEST(List, assign_operator_change_list_size)
{
    List<int> l1(2, -1), l2(10);

    for (int i = 0; i < 2; i++) {
        l1.insert_front(i);
    }
    // l1 содержит 4 элемента
    l2 = l1;
    EXPECT_EQ(true,l1==l2);
}

TEST(List, can_insert_front_element)
{
    List<int> list(5, 0);
    list.insert_front(1);
    EXPECT_EQ(list[0], 1);
    EXPECT_EQ(list[1], 0);
}

TEST(List, can_erase_front_element)
{
    List<int> list(5, 0);
    list.insert_front(1);
    list.erase_front();
    EXPECT_EQ(list[0], 0);
}

TEST(List, can_insert_element)
{
    List<int> list(3, 0);
    for (int i = 0; i < 3; i++) {
        list.insert_front(1);
    }
    // list = {1, 1, 1, 0, 2, 0, 0}
    list.insert(2, list.find(0));
    EXPECT_EQ(list[4], 2);
}


TEST(List, can_erase_element)
{
    List<int> list(3, 0);
    for (int i = 1; i < 4; i++) {
        list.insert_front(i);
    }
    // list = {3, 2, 1, 0, 0, 0}
    list.erase(2);
    EXPECT_EQ(list[2], 0);
}


TEST(List, compare_equal_lists_return_true)
{
    List<int> l1(3);
    l1.insert_front(1);
    List<int> l2(l1);
    EXPECT_EQ(true,l1==l2);
}

TEST(List, compare_list_with_itself_return_true)
{
    List<int> l1(3);
    l1.insert_front(1);
    EXPECT_EQ(true,l1==l1);
}

TEST(List, lists_with_different_size_are_not_equal)
{
    List<int> l1(3), l2(4);
    for (int i = 1; i < 4; i++) {
        l1.insert_front(i);
        l2.insert_front(i);
    }
    EXPECT_NE(true,l1==l2);
}