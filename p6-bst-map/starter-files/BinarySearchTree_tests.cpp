#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.size(), 0u);
    ASSERT_EQUAL(tree.height(), 0u);
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_TRUE(tree.begin() == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
}

// 捕获将 height 算作节点总数，或者没有正确接住 insert 返回值的 bug。
TEST(test_basic_insert_and_metrics) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    
    ASSERT_FALSE(tree.empty());
    ASSERT_EQUAL(tree.size(), 3u);
    ASSERT_EQUAL(tree.height(), 2u); // 3 个节点平衡时，高度应为 2
    ASSERT_EQUAL(*tree.begin(), 3);
    ASSERT_EQUAL(*tree.max_element(), 7);
}

// 捕获未正确处理左倾或右倾树（Left-heavy / Right-heavy）的逻辑。
TEST(test_unbalanced_trees) {
    BinarySearchTree<int> right_heavy;
    right_heavy.insert(1);
    right_heavy.insert(2);
    right_heavy.insert(3);
    ASSERT_EQUAL(right_heavy.size(), 3u);
    ASSERT_EQUAL(right_heavy.height(), 3u); 

    BinarySearchTree<int> left_heavy;
    left_heavy.insert(3);
    left_heavy.insert(2);
    left_heavy.insert(1);
    ASSERT_EQUAL(left_heavy.size(), 3u);
    ASSERT_EQUAL(left_heavy.height(), 3u);
}

// Shallow Copy的实现，这会导致多棵树共享相同节点。
TEST(test_deep_copy_and_assignment) {
    BinarySearchTree<int> t1;
    t1.insert(5);
    t1.insert(3);

    BinarySearchTree<int> t2(t1);
    t1.insert(7); // 修改 t1 不应影响 t2
    ASSERT_EQUAL(t1.size(), 3u);
    ASSERT_EQUAL(t2.size(), 2u);

    BinarySearchTree<int> t3;
    t3.insert(100);
    t3 = t1;
    t1.insert(9); // 修改 t1 不应影响 t3
    ASSERT_EQUAL(t3.size(), 3u);
    ASSERT_EQUAL(*t3.max_element(), 7);
}

// 捕获遍历顺序写错，或者末尾没有正确输出空格的实现。
TEST(test_traversals) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);

    std::ostringstream os_in, os_pre;
    tree.traverse_inorder(os_in);
    tree.traverse_preorder(os_pre);

    // 必须是升序
    ASSERT_EQUAL(os_in.str(), "1 2 3 4 5 6 7 ");
    // 前序必须符合 根-左-右
    ASSERT_EQUAL(os_pre.str(), "4 2 1 3 6 5 7 ");
}

// 捕获未能正确查找到左/右子树深处节点的实现。
TEST(test_find) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    ASSERT_TRUE(tree.find(5) != tree.end());
    ASSERT_EQUAL(*tree.find(5), 5);
    
    // 查找不存在的元素应该返回 end()
    ASSERT_TRUE(tree.find(7) == tree.end());
    ASSERT_TRUE(tree.find(20) == tree.end());
}

// 捕获 min_greater_than 逻辑错误（例如：直接返回当前节点而不是左子树的最优解）。
TEST(test_min_greater_than) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);
    tree.insert(20);

    // 存在比 11 大的最小值，应该找到 12（在 15 的左子树）
    ASSERT_EQUAL(*tree.min_greater_than(11), 12);
    // 等于现有节点时，应返回严格大于该节点的最小值
    ASSERT_EQUAL(*tree.min_greater_than(10), 12);
    // 没有比 20 更大的元素了
    ASSERT_TRUE(tree.min_greater_than(20) == tree.end());
    ASSERT_TRUE(tree.min_greater_than(100) == tree.end());
}

// 捕获迭代器遍历不完整的 bug。
TEST(test_iterator_increment) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    auto it = tree.begin(); // 指向 5
    ASSERT_EQUAL(*it, 5);
    ++it; // 指向 10
    ASSERT_EQUAL(*it, 10);
    ++it; // 指向 15
    ASSERT_EQUAL(*it, 15);
    ++it; // 指向 end()
    ASSERT_TRUE(it == tree.end());
}

// Pro-tip，通过解引用迭代器强行改错数据，检测 check_sorting_invariant。
TEST(test_sorting_invariant_broken) {
    BinarySearchTree<int> tree;
    tree.insert(4);
    tree.insert(2);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);

    // 树起初是合法的
    ASSERT_TRUE(tree.check_sorting_invariant());

    // 找到 2，把它改成 5。这样 5 在 4 的左子树里，违反了不变式
    auto it = tree.find(2);
    *it = 5;

    ASSERT_FALSE(tree.check_sorting_invariant());
}

// Custom Comparator Functor
TEST(test_custom_comparator_greater) {
    // std::greater，左边放大的，右边放小的
    BinarySearchTree<int, std::greater<int>> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);

    // 7 应该在 5 的"左边" (被认为是更小的)
    // begin() 返回的应该是 7，而不是 3
    ASSERT_EQUAL(*tree.begin(), 7);
    ASSERT_EQUAL(*tree.max_element(), 3);
    
    // min_greater_than(5) 在降序下意思是找 "比 5 小的数里最大的那个" 
    ASSERT_EQUAL(*tree.min_greater_than(5), 3);
}

TEST_MAIN()
