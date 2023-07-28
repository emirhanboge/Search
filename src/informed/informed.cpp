#include "informed.h"

Informed::Informed() {
    this->tree = new Tree();
}

Informed::~Informed() {
    delete this->tree;

    this->tree = nullptr;
}

// Create a random tree
void Informed::createRandomTree(int depth, bool sameCost) {
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
void Informed::visualizePath(std::vector<Tree::Node*> reached) {
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

void Informed::AStar() { 
    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // If the goal is null, return
    if (this->tree->goal == nullptr) {
        return;
    }

    // Create a priority queue for the open list
    std::priority_queue<Tree::Node*, std::vector<Tree::Node*>, Tree::CompareF> open;
    std::unordered_set<Tree::Node*> openSet; // Additional set to keep track of what's in the queue

    // Create a vector for the closed list
    std::vector<Tree::Node*> closed;

    // Push the root onto the open list
    open.push(this->tree->root);
    openSet.insert(this->tree->root);

    // While the open list is not empty
    while (!open.empty()) {
        // Pop the top node off the open list
        Tree::Node* current = open.top();
        open.pop();
        openSet.erase(current); // Remove current node from openSet

        // If the current node is the goal, return
        if (current->id == this->tree->goal->id) {
            return;
        }

        // Push the current node onto the closed list
        closed.push_back(current);

        // If the current node has a left child
        if (current->left != nullptr) {
            // If the left child is not in the closed list
            if (std::find(closed.begin(), closed.end(), current->left) == closed.end()) {
                // Set the left child's parent to the current node
                current->left->parent = current;

                // Set the left child's g cost to the current node's g cost plus one
                current->left->g = current->g + 1;

                // Set the left child's h cost to the distance from the left child to the goal
                current->left->h = this->tree->goal->id - current->left->id;

                // Set the left child's f cost to the left child's g cost plus the left child's h cost
                current->left->f = current->left->g + current->left->h;

                // If the left child is not in the open list, push it onto the open list
                if (openSet.find(current->left) == openSet.end()) {
                    open.push(current->left);
                    openSet.insert(current->left);
                }
            }
        }

        // If the current node has a right child
        if (current->right != nullptr) {
            // If the right child is not in the closed list
            if (std::find(closed.begin(), closed.end(), current->right) == closed.end()) {
                // Set the right child's parent to the current node
                current->right->parent = current;

                // Set the right child's g cost to the current node's g cost plus one
                current->right->g = current->g + 1;

                // Set the right child's h cost to the distance from the right child to the goal
                current->right->h = this->tree->goal->id - current->right->id;

                // Set the right child's f cost to the right child's g cost plus the right child's h cost
                current->right->f = current->right->g + current->right->h;

                // If the right child is not in the open list, push it onto the open list
                if (openSet.find(current->right) == openSet.end()) {
                    open.push(current->right);
                    openSet.insert(current->right);
                }
            }
        }
    }
}

void Informed::Greedy() {
    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // If the goal is null, return
    if (this->tree->goal == nullptr) {
        return;
    }

    // Create a priority queue for the frontier with a custom comparison function
    std::priority_queue<Tree::Node*, std::vector<Tree::Node*>, Tree::CompareH> frontier;

    // Vector to keep track of visited nodes
    std::vector<Tree::Node*> visited;

    // Push the root onto the frontier
    frontier.push(this->tree->root);

    // While the frontier is not empty
    while (!frontier.empty()) {
        // Pop the top node off the frontier
        Tree::Node* current = frontier.top();
        frontier.pop();

        // If the current node is the goal, return
        if (current->id == this->tree->goal->id) {
            return;
        }

        // If the current node has not been visited
        if (std::find(visited.begin(), visited.end(), current) == visited.end()) {
            // Mark the current node as visited
            visited.push_back(current);

            // If the current node has a left child and it hasn't been visited, add it to the frontier
            if (current->left != nullptr && std::find(visited.begin(), visited.end(), current->left) == visited.end()) {
                frontier.push(current->left);
            }

            // If the current node has a right child and it hasn't been visited, add it to the frontier
            if (current->right != nullptr && std::find(visited.begin(), visited.end(), current->right) == visited.end()) {
                frontier.push(current->right);
            }
        }
    }
}

