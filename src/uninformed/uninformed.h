#pragma once 

#include <../tree/tree.h>
#include <queue>
#include <vector>

// Uninformed search algorithms, create a random tree and search it
class Uninformed {
    public:
        // Constructor
        Uninformed();

        // Destructor
        ~Uninformed();

        // Create a random tree
        void createRandomTree(int depth, bool sameCost);

        // Visualize the path
        void visualizePath(std::vector<Tree::Node*> reached);

        // Search the tree using BFS
        void BFS();

        // Search the tree using UCS
        void UCS();
    private:
        Tree* tree; // Tree to search
};
