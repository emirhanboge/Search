#include "uninformed.h"

// Constructor
Uninformed::Uninformed() {
    this->tree = nullptr;
}

// Destructor
Uninformed::~Uninformed() {
    // Delete the tree
    delete this->tree;

    // Set the tree to null
    this->tree = nullptr;
}

// Create a random tree
void Uninformed::createRandomTree(int depth, bool sameCost) {
    // Delete the tree
    delete this->tree;

    // Set the tree to null
    this->tree = nullptr;

    // Create a new tree
    this->tree = new Tree(depth);

    // Generate a random tree
    if (sameCost) {
        this->tree->root = this->tree->genRandTreeSameCost(depth);
    } else {
        this->tree->root = this->tree->genRandTreeDiffCost(depth);
    }

    // Generate a goal node
    this->tree->genGoalNode();

    // Print the tree
    this->tree->print();
}

// Visualize the path
void Uninformed::visualizePath(std::vector<Tree::Node*> reached) {
    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // If the goal is null, return
    if (this->tree->goal == nullptr) {
        return;
    }

    // If the reached vector is empty, return
    if (reached.empty()) {
        return;
    }

    // Create a new tree with only the nodes in the reached vector
    Tree* path = new Tree(this->tree->depth);

    // Set the root to the root of the tree
    path->root = this->tree->root;

    // Set the goal to the goal of the tree
    path->goal = this->tree->goal;

    // For each node in the reached vector
    for (int i = 0; i < reached.size(); i++) {
        // If the node is the root, continue
        if (reached[i]->id == path->root->id) {
            continue;
        }

        // If the node is the goal, continue
        if (reached[i]->id == path->goal->id) {
            continue;
        }

        // If the node is not in the reached vector, remove that node from the tree 
        if (std::find(reached.begin(), reached.end(), reached[i]) == reached.end()) {
            path->removeNode(reached[i]);
        }
    }

    // Print the path
    std::cout << "Path Taken to the Goal: " << std::endl;
    path->print();
}

// Search the tree using BFS 
void Uninformed::BFS() {
    // Create a tree
    this->createRandomTree(5, true);

    // Create a queue
    std::queue<Tree::Node*> queue;

    // Vector to keep track of visited nodes
    std::vector<Tree::Node*> reached;

    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // If the root is the goal, return
    if (this->tree->root->id == this->tree->goal->id) {
        reached.push_back(this->tree->root);
        // Visualize the path
        this->visualizePath(reached);
        return;
    }

    // Push the root to the queue
    queue.push(this->tree->root);

    // While the queue is not empty
    while (!queue.empty()) {
        // pop the front of the queue
        Tree::Node* node = queue.front();
        queue.pop();

        // For the left and right children
        for (int i = 0; i < 2; i++) {
            Tree::Node* child;
            if (i == 0) { // Left child
                child = node->left;
            } else { // Right child
                child = node->right;
            }

            int id = child->id;

            // If the child is null, continue
            if (child == nullptr) {
                continue;
            }

            // If the child is the goal, return
            if (id == this->tree->goal->id) {
                // Visualize the path
                this->visualizePath(reached);
                return;
            }

            // If the child is not in the reached vector, push it to the queue
            if (std::find(reached.begin(), reached.end(), child) == reached.end()) {
                queue.push(child);
                reached.push_back(child);
            }
        }
    }

    // Visualize the path
    this->visualizePath(reached);

    // If the goal is not found, return
    return;
}

// Search the tree using UCS
void Uninformed::UCS() { // Uniform Cost Search
    // Create a tree
    this->createRandomTree(5, false);

    // Create a priority queue
    std::priority_queue<Tree::Node*, std::vector<Tree::Node*>, Tree::CompareG> queue;

    // Vector to keep track of visited nodes
    std::vector<Tree::Node*> reached;

    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // If the root is the goal, return
    if (this->tree->root->id == this->tree->goal->id) {
        reached.push_back(this->tree->root);
        // Visualize the path
        this->visualizePath(reached);
        return;
    }

    // Push the root to the queue
    queue.push(this->tree->root);

    // While the queue is not empty
    while (!queue.empty()) {
        // pop the front of the queue
        Tree::Node* node = queue.top();
        queue.pop();

        // If this node has already been reached with a shorter path, skip it
        if (std::find(reached.begin(), reached.end(), node) != reached.end()) {
            continue;
        }

        // We have reached this node with the shortest possible path
        reached.push_back(node);

        // For the left and right children
        for (int i = 0; i < 2; i++) {
            Tree::Node* child;
            if (i == 0) { // Left child
                child = node->left;
            } else { // Right child
                child = node->right;
            }

            int id = child->id;

            // If the child is null, continue
            if (child == nullptr) {
                continue;
            }

            // If the child is the goal, return
            if (id == this->tree->goal->id) {
                // Add the goal to the reached vector
                reached.push_back(child);
                // Visualize the path
                this->visualizePath(reached);
                return;
            }

            // Push the child to the queue
            queue.push(child);
        }
    }

    // Visualize the path
    this->visualizePath(reached);

    // If the goal is not found, return
    return;
}
