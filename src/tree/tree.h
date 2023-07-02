#pragma once 

#include <iostream>

// A tree class for simulating search algorithms like A* and Dijkstra's
class Tree {
    public:
        struct Node {
            int d; // Depth of the node
            int g; // G cost of the node (distance from start)
            int h; // H cost of the node (distance from end)
            int f; // F cost of the node (g + h)
            Node* parent; // Parent of the node
            Node* left; // Left child of the node
            Node* right; // Right child of the node
        };

        Tree(); // Default constructor
        Tree(int depth); // Constructor with depth
        ~Tree(); // Destructor

        void deleteNodes(); // Delete all nodes in the tree
        void deleteNodes(Node* node); // Delete all nodes in the tree

        void print(); // Print the tree
        void print(int depth); // Print the tree to a certain depth

        void setDepth(int depth); // Set the depth of the tree
        int getDepth(); // Get the depth of the tree

        Node* genRandTreeSameCost(int depth); // Generate a random tree with the same cost
        Node* genRandTreeDiffCost(int depth); // Generate a random tree with different costs

        private:
            int depth; // Depth of the tree
            Node* root; // Root of the tree
};