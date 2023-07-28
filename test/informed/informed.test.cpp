#include <catch2/catch_test_macros.hpp>

#include "../../src/informed/informed.h"

TEST_CASE( "A Star Search", "[informed]" ) {
    Informed informed;
    informed.createRandomTree(5, true);
    informed.AStar();
}

TEST_CASE( "Greedy Search", "[informed]" ) {
    Informed informed;
    informed.createRandomTree(5, true);
    informed.Greedy();
}

TEST_CASE( "A Star Search with different costs", "[informed]" ) {
    Informed informed;
    informed.createRandomTree(5, false);
    informed.AStar();
}

TEST_CASE( "Greedy Search with different costs", "[informed]" ) {
    Informed informed;
    informed.createRandomTree(5, false);
    informed.Greedy();
}

