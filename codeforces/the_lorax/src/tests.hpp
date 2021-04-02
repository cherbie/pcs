#ifndef _TEST_H
#define _TESTS_H
#endif

#include "main.cpp" // class definitions
#include <cstdlib>
#include <climits>
#include <ctime>
#include "gtest/gtest.h"

class TreeTest : public ::testing::Test
{
protected:
    TreeTest();
    void SetUp() override;

    Tree tree_min_;
    Tree tree_normal_;
    Tree tree_max_;
};