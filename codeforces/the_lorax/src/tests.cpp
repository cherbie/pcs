#include "tests.hpp"

#define MAX_TEST_SIZE UINT_MAX

TreeTest::TreeTest() : _tree_min(2), _tree_normal(6), _tree_max(MAX_TEST_SIZE) {}

void TreeTest::SetUp()
{
    // minimum
    _tree_min.add_edge(1, 2);

    // normal
    _tree_normal.add_edge(1, 2);
    _tree_normal.add_edge(2, 3);
    _tree_normal.add_edge(3, 1);
    _tree_normal.add_edge(4, 5);
    _tree_normal.add_edge(4, 6);

    std::srand(std::time(0));

    for (unsigned int i = 1; i < MAX_TEST_SIZE; ++i)
    {
        unsigned int parent = std::rand() % MAX_TEST_SIZE + 1;
        unsigned int child = std::rand() % MAX_TEST_SIZE + 1;

        std::cout << parent << " | " << child << std::endl;
        _tree_max.add_edge(parent, child);
    }
}

TEST_F(TreeTest, EmptyTreeInitialisation)
{
    Tree test_tree;
    ASSERT_EQ(test_tree.size(), 0);
}

TEST_F(TreeTest, TreeNumberNodesInitialisation)
{
    unsigned int num_nodes = std::rand() / RAND_MAX * UINT_MAX;
    Tree test_tree(num_nodes);
    ASSERT_EQ(test_tree.size(), num_nodes);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}