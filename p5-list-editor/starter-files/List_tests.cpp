  #include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_copy_constructor_copies_empty_list) {
    List<int> original;
    List<int> copy(original);
    ASSERT_TRUE(copy.empty());
    ASSERT_EQUAL(copy.size(),0);
    ASSERT_TRUE(copy.begin()==copy.end());
}
TEST(test_copy_constructor_makes_deep_copy) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    original.push_back(3);
    List<int> copy(original);
    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_EQUAL(copy.front(), 1);
    ASSERT_EQUAL(copy.back(), 3);
    copy.pop_front();
    ASSERT_EQUAL(copy.size(), 2);
    ASSERT_EQUAL(copy.front(), 2);
    ASSERT_EQUAL(original.size(), 3);
    ASSERT_EQUAL(original.front(), 1);
    ASSERT_EQUAL(original.back(), 3);
}
TEST(test_copy_constructor_original_changes_do_not_affect_copy) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    List<int> copy(original);
    original.pop_back();
    ASSERT_EQUAL(original.size(), 1);
    ASSERT_EQUAL(copy.size(), 2);
    ASSERT_EQUAL(copy.back(), 2);
}
TEST(test_assignment_operator_original_changes_not_affect_assigned_copy) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int> b;
    b = a;
    a.pop_back();
    ASSERT_EQUAL(a.size(), 1);
    ASSERT_EQUAL(b.size(), 2);
    ASSERT_EQUAL(b.back(), 2);
}
TEST(test_assignment_operator_empty_to_nonempty) {
    List<int> a;
    List<int> b;
    b.push_back(5);
    b.push_back(6);
    b = a;
    ASSERT_TRUE(b.empty());
    ASSERT_EQUAL(b.size(), 0);
    ASSERT_TRUE(b.begin()==b.end());
}
TEST(test_assignment_operator_nonempty_to_empty) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int> b;
    b = a;
    ASSERT_EQUAL(b.size(), 2);
    ASSERT_EQUAL(b.front(), 1);
    ASSERT_EQUAL(b.back(), 2);
}
TEST(test_assignment_operator_makes_deep_copy) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int> b;
    b.push_back(9);
    b = a;
    ASSERT_EQUAL(b.size(), 2);
    ASSERT_EQUAL(b.front(), 1);
    ASSERT_EQUAL(b.back(), 2);
    b.pop_back();
    ASSERT_EQUAL(b.size(), 1);
    ASSERT_EQUAL(a.size(), 2);
    ASSERT_EQUAL(a.back(), 2);
}
TEST(test_assignment_operator_self_assignment) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a = a;
    ASSERT_EQUAL(a.size(), 3);
    ASSERT_EQUAL(a.front(), 1);
    ASSERT_EQUAL(a.back(), 3);
    List<int>::Iterator it = a.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_insert_into_empty_list_at_end) {
    List<int> l;
    List<int>::Iterator it = l.insert(l.end(), 10);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 10);
    ASSERT_EQUAL(l.back(), 10);
    ASSERT_EQUAL(*it, 10);
}

TEST(test_insert_before_begin) {
    List<int> l;
    l.push_back(20);
    l.push_back(30);
    List<int>::Iterator it = l.insert(l.begin(), 10);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 10);
    ASSERT_EQUAL(l.back(), 30);
    ASSERT_EQUAL(*it, 10);
    List<int>::Iterator check = l.begin();
    ASSERT_EQUAL(*check,10);
    ++check;
    ASSERT_EQUAL(*check,20);
    ++check;
    ASSERT_EQUAL(*check,30);
}
TEST(test_insert_before_middle_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    List<int>::Iterator pos = l.begin();
    ++pos;
    List<int>::Iterator inserted = l.insert(pos, 2);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(*inserted, 2);
    List<int>::Iterator it = l.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_insert_at_end_of_nonempty_list) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    List<int>::Iterator it=l.insert(l.end(),3);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(*it, 3);
}
TEST(test_insert_before_begin_in_single_element_list) {
    List<int> l;
    l.push_back(20);
    List<int>::Iterator it = l.insert(l.begin(), 10);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 10);
    ASSERT_EQUAL(l.back(), 20);
    ASSERT_EQUAL(*it, 10);
}
TEST(test_erase_first_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator result = l.erase(l.begin());
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(*result, 2);
}
TEST(test_erase_middle_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it = l.begin();
    ++it;
    List<int>::Iterator result = l.erase(it);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_EQUAL(*result, 3);
    List<int>::Iterator check = l.begin();
    ASSERT_EQUAL(*check, 1);
    ++check;
    ASSERT_EQUAL(*check, 3);
    List<int>::Iterator reverse = l.end();
    reverse--;
    ASSERT_EQUAL(*reverse, 3);
    reverse--;
    ASSERT_EQUAL(*reverse, 1);

}
TEST(test_erase_last_element_returns_end) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it = l.begin();
    ++it;
    ++it;
    List<int>::Iterator result = l.erase(it);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_TRUE(result == l.end());
}
TEST(test_erase_only_element_makes_list_empty) {
    List<int> l;
    l.push_back(10);
    List<int>::Iterator result = l.erase(l.begin());
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
    ASSERT_TRUE(l.begin() == l.end());
    ASSERT_TRUE(result == l.end());
}
TEST(test_erase_first_of_two_elements) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    List<int>::Iterator result = l.erase(l.begin());
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 2);
    ASSERT_EQUAL(*result, 2);
}
TEST(test_erase_last_of_two_elements_returns_end) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    List<int>::Iterator it = l.begin();
    ++it;
    List<int>::Iterator result = l.erase(it);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 1);
    ASSERT_TRUE(result == l.end());
}
TEST(test_empty_and_size_default){
    List<int> l;
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(),0);
}
TEST(test_empty_push_back){
    List<int> l;
    l.push_back(2);
    ASSERT_TRUE(l.empty()==false);
    ASSERT_EQUAL(l.size(),1);
}
TEST(test_empty_push_front){
    List<int> l;
    l.push_front(2);
    ASSERT_TRUE(l.empty()==false);
    ASSERT_EQUAL(l.size(),1);
}
TEST(test_empty_multiple_push_back){
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    ASSERT_TRUE(l.empty()==false);
    ASSERT_EQUAL(l.size(),3);
}
TEST(test_empty_pop_back){
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.pop_back();
    ASSERT_TRUE(l.empty()==false);
    ASSERT_EQUAL(l.size(),2);
}
TEST(test_empty_pop_front){
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.pop_front();
    ASSERT_TRUE(l.empty()==false);
    ASSERT_EQUAL(l.size(),2);
}
TEST(test_clear_empty){
    List<int> l;
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.clear();
    ASSERT_TRUE(l.empty()==true);
    ASSERT_EQUAL(l.size(),0);
}
TEST(test_clear_on_empty_list) {
    List<int> l;
    l.clear();
    ASSERT_TRUE(l.empty());
    ASSERT_EQUAL(l.size(), 0);
    ASSERT_TRUE(l.begin() == l.end());
}
TEST(test_clear_allows_reuse_after_clearing) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.clear();
    l.push_back(7);
    ASSERT_FALSE(l.empty());
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 7);
    ASSERT_EQUAL(l.back(), 7);
}
TEST(test_front_returns_reference_to_first_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    ASSERT_EQUAL(l.front(), 10);
    l.front() = 99;
    ASSERT_EQUAL(l.front(), 99);
    ASSERT_EQUAL(l.back(), 20);
}
TEST(test_front_single_element) {
    List<int> l;
    l.push_back(10);
    ASSERT_EQUAL(l.front(), l.back());
    ASSERT_EQUAL(l.front(), 10);
    ASSERT_EQUAL(l.back(), 10);
}
TEST(test_front_push_front_element) {
    List<int> l;
    l.push_back(10);
    l.push_front(20);
    ASSERT_EQUAL(l.front(), 20);
    ASSERT_EQUAL(l.back(), 10);
}
TEST(test_front_pop_front_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.pop_front();
    ASSERT_EQUAL(l.front(), 20);
    ASSERT_EQUAL(l.back(), 20);
}
TEST(test_front_push_front_and_push_back_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_front(30);
    ASSERT_EQUAL(l.front(), 30);
    ASSERT_EQUAL(l.back(), 20);
}
TEST(test_front_reference_after_copy) {
    List<int> original;
    original.push_back(1);
    original.push_back(2);
    List<int> copy(original);
    copy.front() = 99;
    ASSERT_EQUAL(copy.front(), 99);
    ASSERT_EQUAL(original.front(), 1);
}
TEST(test_back_returns_reference_to_last_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    ASSERT_EQUAL(l.back(), 20);
    l.back() = 77;
    ASSERT_EQUAL(l.back(), 77);
    ASSERT_EQUAL(l.front(), 10);
}
TEST(test_back_single_element) {
    List<int> l;
    l.push_back(10);
    ASSERT_EQUAL(l.back(), 10);
    ASSERT_EQUAL(l.front(), 10);
}
TEST(test_back_after_pop_back) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.pop_back();
    ASSERT_EQUAL(l.back(), 10);
    ASSERT_EQUAL(l.front(), 10);
}
TEST(test_push_front_reverse_insertion_order) {
    List<int> l;
    l.push_front(3);
    l.push_front(2);
    l.push_front(1);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    List<int>::Iterator it = l.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_push_front_single_element) {
    List<int> l;
    ASSERT_TRUE(l.empty());
    l.push_front(3);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 3);
    ASSERT_FALSE(l.empty());
    List<int>::Iterator it = l.begin();
    ASSERT_EQUAL(*it, 3);
}
TEST(test_push_front_change_empty_size) {
    List<int> l;
    l.push_back(3);
    ASSERT_EQUAL(l.size(), 1);
    ASSERT_EQUAL(l.front(), 3);
    ASSERT_EQUAL(l.back(), 3);
    l.push_front(2);
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 3);
}
TEST(test_mixed_push_front_and_push_back_order) {
    List<int> l;
    l.push_back(2);
    l.push_front(1);
    l.push_back(3);
    ASSERT_EQUAL(l.size(), 3);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 3);
    List<int>::Iterator it = l.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_push_back_insertion_order) {
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);

    ASSERT_EQUAL(lst.size(), 3);
    ASSERT_EQUAL(lst.front(), 1);
    ASSERT_EQUAL(lst.back(), 3);

    List<int>::Iterator it = lst.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_pop_front_removes_first_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_front();
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 2);
    ASSERT_EQUAL(l.back(), 3);
    List<int>::Iterator it1 = l.begin();
    ASSERT_EQUAL(*it1, 2);
    ++it1;
    ASSERT_EQUAL(*it1, 3);

    List<int> ls;
    ls.push_back(1);
    ls.pop_front();
    ASSERT_EQUAL(ls.size(), 0);
    ASSERT_EQUAL(ls.begin(),ls.end());

    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.pop_front();
    ASSERT_EQUAL(lst.size(), 1);
    ASSERT_EQUAL(lst.front(), 2);
    ASSERT_EQUAL(lst.back(), 2);
    List<int>::Iterator it2 = lst.begin();
    ASSERT_EQUAL(*it2, 2);

    List<int> lr;
    lr.push_back(1);
    lr.push_back(2);
    lr.pop_front();
    ASSERT_EQUAL(lr.size(), 1);
    ASSERT_EQUAL(lr.back(), 2);
    ASSERT_EQUAL(lr.front(), 2);
    List<int>::Iterator it3 = lr.begin();
    ASSERT_EQUAL(*it3, 2);

    List<int> llst;
    llst.push_back(1);
    llst.push_back(2);
    llst.pop_front();
    llst.pop_front();
    ASSERT_EQUAL(llst.size(), 0);
    ASSERT_EQUAL(llst.begin(),llst.end());

}

TEST(test_pop_back_removes_last_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.pop_back();
    ASSERT_EQUAL(l.size(), 2);
    ASSERT_EQUAL(l.front(), 1);
    ASSERT_EQUAL(l.back(), 2);

    List<int>::Iterator it = l.begin();
    ASSERT_EQUAL(*it, 1);
    it++;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_TRUE(it ==l.end());

    List<int> single;
    single.push_back(1);
    single.pop_back();
    ASSERT_TRUE(single.empty());
    ASSERT_EQUAL(single.size(), 0);
    ASSERT_TRUE(single.begin() == single.end());

    List<int> two;
    two.push_back(1);
    two.push_back(2);
    two.pop_back();
    ASSERT_EQUAL(two.size(), 1);
    ASSERT_EQUAL(two.front(), 1);
    ASSERT_EQUAL(two.back(), 1);
    ASSERT_TRUE(two.begin() != two.end());
    List<int>::Iterator two_it = two.begin();
    ASSERT_EQUAL(*two_it, 1);
    ++two_it;
    ASSERT_TRUE(two_it == two.end());
}


TEST(test_begin_equals_end_on_empty_list) {
    List<int> l;
    ASSERT_TRUE(l.begin() == l.end());
}
TEST(test_begin_not_equal_end_on_nonempty_list) {
    List<int> l;
    l.push_back(10);
    ASSERT_TRUE(l.begin() != l.end());
}
TEST(test_single_element_increment_begin_reaches_end) {
    List<int> l;
    l.push_back(10);
    List<int>::Iterator it = l.begin();
    ++it;
    ASSERT_TRUE(it==l.end());
}
TEST(test_default_constructed_iterators_compare_equal) {
    List<int>::Iterator it1;
    List<int>::Iterator it2;
    ASSERT_TRUE(it1 == it2);
}
TEST(test_default_constructed_iterator_not_equal) {
    List<int> l;
    List<int>::Iterator it;
    ASSERT_TRUE(it !=l.end());
}
TEST(test_iterator_dereference_returns_reference) {
    List<int> l;
    l.push_back(5);
    l.push_back(6);
    List<int>::Iterator it = l.begin();
    *it = 100;
    ASSERT_EQUAL(l.front(),100);
    ASSERT_EQUAL(l.back(),6);
}
TEST(test_iterators_to_same_position_compare_equal) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    List<int>::Iterator it1 = l.begin();
    List<int>::Iterator it2 = l.begin();
    ASSERT_TRUE(it1 == it2);
}
TEST(test_iterators_to_different_positions_compare_not_equal) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    List<int>::Iterator it1 = l.begin();
    List<int>::Iterator it2 = l.begin();
    ++it2;
    ASSERT_TRUE(it1 != it2);
}
TEST(test_prefix_increment_moves_iterator_forward) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it = l.begin();
    ++it;
    ASSERT_EQUAL(*it, 2);
    ++it;
    ASSERT_EQUAL(*it, 3);
}

TEST(test_prefix_decrement_from_end_moves_to_last_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it = l.end();
    --it;
    ASSERT_EQUAL(*it, 3);
}
TEST(test_prefix_decrement_moves_to_previous_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it = l.end();
    --it;
    --it;
    ASSERT_EQUAL(*it, 2);
}

TEST(test_decrement_from_end_reach_first_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    List<int>::Iterator it3 = l.end();
    --it3;
    --it3;
    --it3;
    ASSERT_EQUAL(*it3, 1);

    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    List<int>::Iterator it = lst.begin();
    List<int>::Iterator old = it++;
    ASSERT_EQUAL(*old, 1);
    ASSERT_EQUAL(*it, 2);
    List<int>::Iterator it2 = lst.end();
    --it2;
    List<int>::Iterator old2 = it2--;
    ASSERT_EQUAL(*old2, 3);
    ASSERT_EQUAL(*it2, 2);
}
struct Thing {
    int value;
};
TEST(test_iterator_arrow_operator_accesses_member) {
    List<Thing> l;
    Thing t;
    t.value = 7;
    l.push_back(t);
    List<Thing>::Iterator it = l.begin();
    ASSERT_EQUAL(it->value,7);
}
TEST(test_iterator_arrow_operator_can_modify_member) {
    List<Thing> l;
    Thing t;
    t.value = 7;
    l.push_back(t);
    List<Thing>::Iterator it = l.begin();
    it->value = 42;
    ASSERT_EQUAL(l.front().value, 42);
}
TEST_MAIN()
