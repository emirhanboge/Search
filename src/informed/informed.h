#pragma once 

#include "../tree/tree.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

class Informed {
    public:
        Informed();
        ~Informed();

        // Create a random tree
        void createRandomTree(int depth, bool sameCost);

        // Visualize the path
        void visualizePath(std::vector<Tree::Node*> reached);

        // Search the tree using A* (A Star)
        void AStar();

        // Search the tree using Greedy
        void Greedy();
    private: 
        Tree* tree; // Tree to search
};