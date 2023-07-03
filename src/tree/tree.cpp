#include "tree.h"

// Default constructor
Tree::Tree() {
    this->depth = 0;
    this->root = nullptr;
    this->goal = nullptr;
}

// Constructor with depth
Tree::Tree(int depth) {
    this->depth = depth;
    this->root = nullptr;
    this->goal = nullptr;
}

// Destructor
Tree::~Tree() {
    this->deleteNodes();

    // Set the depth to 0
    this->depth = 0;

    // Set the goal to null
    this->goal = nullptr;
}

// Delete all nodes in the tree
void Tree::deleteNodes() {
    // If the root is null, return
    if (this->root == nullptr) {
        return;
    }

    // If the root is not null, delete left and right subtrees
    this->deleteNodes(this->root->left);
    this->deleteNodes(this->root->right);

    // Delete the root
    delete this->root;

    // Set the root to null
    this->root = nullptr;
}

// Delete all nodes in the tree
void Tree::deleteNodes(Node* node) {
    // If the node is null, return
    if (node == nullptr) {
        return;
    }

    // If the node is not null, delete left and right subtrees
    this->deleteNodes(node->left);
    this->deleteNodes(node->right);

    // Delete the node
    delete node;

    // Set the node to null
    node = nullptr;
}

// Print the tree
void Tree::print() {
    this->print(this->depth);
}

// Print the tree to a certain depth 
void Tree::print(int depth) {
    // If the tree is empty, print an error message
    if (this->root == nullptr) {
        std::cout << "Error: Tree is empty" << std::endl;
        return;
    }

    // If the depth is less than 0, print an error message
    if (depth < 0) {
        std::cout << "Error: Depth must be greater than or equal to 0" << std::endl;
        return;
    }

    // If the depth is 0, print the root
    if (depth == 0) {
        std::cout << this->root->d << " " << this->root->g << " " << this->root->h << " " << this->root->f << std::endl;
        return;
    }

    for (int i = 0; i < depth; i++) {
        // If the root is null, print an error message
        if (this->root == nullptr) {
            std::cout << "Error: Tree is empty" << std::endl;
            return;
        }

        // If the root is not null, print the root
        std::cout << this->root->d << " " << this->root->g << " " << this->root->h << " " << this->root->f << std::endl;

        // If the root has a left child, print the left child
        if (this->root->left != nullptr) {
            std::cout << this->root->left->d << " " << this->root->left->g << " " << this->root->left->h << " " << this->root->left->f << " ";
        }
        // If the root does not have a left child, print a space
        else {
            std::cout << "  ";
        }

        // If the root has a right child, print the right child
        if (this->root->right != nullptr) {
            std::cout << this->root->right->d << " " << this->root->right->g << " " << this->root->right->h << " " << this->root->right->f << std::endl;
        }
        // If the root does not have a right child, print a newline
        else {
            std::cout << std::endl;
        }

        // Set the root to the left child
        this->root = this->root->left;
    }

    // Print the goal node
    std::cout << "Goal Node:" << std::endl;
    std::cout << this->goal->d << " " << this->goal->g << " " << this->goal->h << " " << this->goal->f << std::endl;

    return;
}

// Generate a random tree with the same cost
Tree::Node* Tree::genRandTreeSameCost(int depth) {
    if (depth == 0) {
        return nullptr;
    }

    Node* newNode = new Node;

    newNode->d = depth; 
    newNode->g = 1;  
    newNode->h = 1;  
    newNode->f = newNode->g + newNode->h;

    newNode->id = rand() % 10000 + 1; // A random number between 1 and 10000

    // generate the left and right subtrees recursively
    newNode->left = genRandTreeSameCost(depth - 1);
    newNode->right = genRandTreeSameCost(depth - 1);

    // set the parent of the children nodes if they exist
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }

    return newNode;
}

// Generate a random tree with different costs
Tree::Node* Tree::genRandTreeDiffCost(int depth) {
    if (depth == 0) {
        return nullptr;
    }

    Node* newNode = new Node;

    newNode->d = depth; 
    newNode->g = rand() % 10 + 1;  
    newNode->h = rand() % 10 + 1;  
    newNode->f = newNode->g + newNode->h;

    newNode->id = rand() % 10000 + 1; // A random number between 1 and 10000

    // generate the left and right subtrees recursively
    newNode->left = genRandTreeDiffCost(depth - 1);
    newNode->right = genRandTreeDiffCost(depth - 1);

    // set the parent of the children nodes if they exist
    if (newNode->left != nullptr) {
        newNode->left->parent = newNode;
    }
    if (newNode->right != nullptr) {
        newNode->right->parent = newNode;
    }

    return newNode;
}

// Generate a goal node 
void Tree::genGoalNode() { 
    // Choose a random node in the tree given the depth
    int randNode = rand() % (this->depth + 1);

    // Set the goal node to the random node
    this->goal = this->root;

    // Traverse the tree to the random node
    for (int i = 0; i < randNode; i++) {
        // If the goal node has a left child, set the goal node to the left child
        if (this->goal->left != nullptr) {
            this->goal = this->goal->left;
        }
        // If the goal node does not have a left child, set the goal node to the right child
        else {
            this->goal = this->goal->right;
        }
    }
}

// Delete a node in the tree
void Tree::removeNode(Node* node) {
    // If the node is null, return
    if (node == nullptr) {
        return;
    }

    // If the node is the root, delete the root
    if (node == this->root) {
        delete this->root;
        this->root = nullptr;
        return;
    }

    // If the node is not the root, delete the node
    delete node;
    node = nullptr;
}