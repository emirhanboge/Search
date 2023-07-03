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
            int id; // ID of the node
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

        Node* genRandTreeSameCost(int depth); // Generate a random tree with the same cost
        Node* genRandTreeDiffCost(int depth); // Generate a random tree with different costs

        void genGoalNode(); // Generate a goal node

        void removeNode(Node* node); // Delete a node

        struct CompareG { // Compare the g cost of two nodes
            bool operator()(const Node* lhs, const Node* rhs) const {
                return lhs->g > rhs->g;
            }
        };

        struct CompareH { // Compare the h cost of two nodes
            bool operator()(const Node* lhs, const Node* rhs) const {
                return lhs->h > rhs->h;
            }
        };

        struct CompareF { // Compare the f cost of two nodes
            bool operator()(const Node* lhs, const Node* rhs) const {
                return lhs->f > rhs->f;
            }
        };

        int depth; // Depth of the tree
        Node* root; // Root of the tree
        Node* goal; // Goal of the tree
};