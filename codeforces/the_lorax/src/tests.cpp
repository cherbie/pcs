#include "tests.hpp"

#define MAX_TEST_SIZE 100000

TreeTest::TreeTest() : tree_min_(2), tree_normal_(6), tree_max_(MAX_TEST_SIZE) {}

void TreeTest::SetUp()
{
    // minimum
    tree_min_.add_edge(1, 2);

    // normal
    tree_normal_.add_edge(1, 2);
    tree_normal_.add_edge(2, 3);
    tree_normal_.add_edge(3, 1);
    tree_normal_.add_edge(4, 5);
    tree_normal_.add_edge(4, 6);

    std::srand(std::time(0));

    for (int i = 1; i < MAX_TEST_SIZE; ++i)
    {
        int parent = std::rand() % MAX_TEST_SIZE + 1;
        int child = std::rand() % MAX_TEST_SIZE + 1;
        tree_max_.add_edge(parent, child);
    }
}

TEST_F(TreeTest, TreeSizeInitialisation)
{
    EXPECT_EQ(tree_min_.size(), 2);
    EXPECT_EQ(tree_normal_.size(), 6);
    EXPECT_EQ(tree_max_.size(), MAX_TEST_SIZE);

}

TEST_F(TreeTest, CircularEdgeNoThrow) {
    ASSERT_NO_THROW(tree_min_.add_edge(1, 1));
}

using TreeDeathTest = TreeTest;

TEST_F(TreeDeathTest, OutOfRangeEdgeThrow)
{
    ASSERT_ANY_THROW(tree_min_.add_edge(2, 3));
    ASSERT_ANY_THROW(tree_min_.add_edge(0, 1));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}