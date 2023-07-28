#pragma once 

#include "../tree/tree.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <vector>
#include <unordered_map>

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
        void visualizePath(std::unordered_map<int, Tree::Node*> reached);

        // Search the tree using BFS (Breadth First Search)
        void BFS();

        // Search the tree using UCS (Uniform Cost Search)
        void UCS();

        // Search the tree using DFS (Depth First Search)
        void DFS();

        // Search the tree using IDS (Iterative Deepening Search)
        void IDS();

        // Search the tree using DLS (Depth Limited Search)
        void DLS(int depth);
        void DLS_helper(Tree::Node* node, std::vector<Tree::Node*>& reached, int depth);
    private:
        Tree* tree; // Tree to search
};
