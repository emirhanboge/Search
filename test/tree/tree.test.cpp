#include <catch2/catch_test_macros.hpp>

#include "../../src/tree/tree.h"

TEST_CASE( "Delete all nodes in tree", "[tree]" ) {
    Tree tree(3);
    Tree::Node* root = tree.genRandTreeSameCost(3);
    REQUIRE_NOTHROW(tree.deleteNodes());
}

TEST_CASE( "Printing the tree", "[tree]" ) {
    Tree tree(3);
    REQUIRE_NOTHROW(tree.print());
}

TEST_CASE( "Printing the tree to a certain depth", "[tree]" ) {
    Tree tree(5);
    REQUIRE_NOTHROW(tree.print(3));
}

TEST_CASE( "Generate a random tree with the same cost", "[tree]" ) {
    Tree tree;
    Tree::Node* root = tree.genRandTreeSameCost(3);
    REQUIRE(root != nullptr);
}

TEST_CASE( "Generate a random tree with different costs", "[tree]" ) {
    Tree tree;
    Tree::Node* root = tree.genRandTreeDiffCost(3);
    REQUIRE(root != nullptr);
}