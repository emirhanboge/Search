#include "tree.h"

// Default constructor
Tree::Tree() {
    this->depth = 0;
    this->root = nullptr;
}

// Constructor with depth
Tree::Tree(int depth) {
    this->depth = depth;
    this->root = nullptr;
}

// Destructor
Tree::~Tree() {
    this->deleteNodes();

    // Set the depth to 0
    this->depth = 0;
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

    return;
}

// Set the depth of the tree
void Tree::setDepth(int depth) {
    this->depth = depth;
}

// Get the depth of the tree
int Tree::getDepth() {
    return this->depth;
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

