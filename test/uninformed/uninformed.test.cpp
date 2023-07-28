#include <catch2/catch_test_macros.hpp>

#include "../../src/uninformed/uninformed.h"

TEST_CASE( "Breath First Search", "[uninformed]" ) {
    Uninformed uninformed;
    uninformed.createRandomTree(5, true);
    uninformed.BFS();
}

TEST_CASE( "Uniform Cost Search", "[uninformed]" ) {
    Uninformed uninformed;
    uninformed.createRandomTree(5, true);
    uninformed.UCS();
}

TEST_CASE( "Depth First Search", "[uninformed]" ) {
    Uninformed uninformed;
    uninformed.createRandomTree(5, true);
    uninformed.DFS();
}

TEST_CASE( "Iterative Deepening Search", "[uninformed]" ) {
    Uninformed uninformed;
    uninformed.createRandomTree(5, true);
    uninformed.IDS();
}

TEST_CASE( "Depth Limited Search", "[uninformed]" ) {
    Uninformed uninformed;
    uninformed.createRandomTree(5, true);
    uninformed.DLS(3);
}
