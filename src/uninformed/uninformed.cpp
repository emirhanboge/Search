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

// Visualize the path
void Uninformed::visualizePath(std::unordered_map<int, Tree::Node*> reached) {
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
    for (auto it = reached.begin(); it != reached.end(); it++) {
        // If the node is the root, continue
        if (it->second->id == path->root->id) {
            continue;
        }

        // If the node is the goal, continue
        if (it->second->id == path->goal->id) {
            continue;
        }

        // If the node is not in the reached vector, remove that node from the tree 
        if (reached.find(it->second->id) == reached.end()) {
            path->removeNode(it->second);
        }
    }

    // Print the path
    std::cout << "Path Taken to the Goal: " << std::endl;
    path->print();
}

void Uninformed::BFS() { // Breadth First Search
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

    // Push the root to the queue and mark it as visited
    queue.push(this->tree->root);
    reached.push_back(this->tree->root);

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

            // If the child is null, continue
            if (child == nullptr) {
                continue;
            }

            // If the child is the goal, add it to the reached vector, visualize the path, and return
            if (child->id == this->tree->goal->id) {
                reached.push_back(child);
                // Visualize the path
                this->visualizePath(reached);
                return;
            }

            // If the child is not in the reached vector, push it to the queue and mark it as visited
            if (std::find(reached.begin(), reached.end(), child) == reached.end()) {
                queue.push(child);
                reached.push_back(child);
            }
        }
    }

    // If the goal is not found, visualize the path
    this->visualizePath(reached);

    // If the goal is not found, return
    return;
}

void Uninformed::UCS() { // Uniform Cost Search
    // Create a tree
    this->createRandomTree(5, false);

    // Create a priority queue
    std::priority_queue<Tree::Node*, std::vector<Tree::Node*>, Tree::CompareG> queue;

    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // Push the root to the queue
    queue.push(this->tree->root);

    // Map to keep track of visited nodes
    std::unordered_map<int, Tree::Node*> reached;

    // While the queue is not empty
    while (!queue.empty()) {
        // pop the front of the queue
        Tree::Node* node = queue.top();
        queue.pop();

        // If the node is the goal, visualize the path and return
        if (node->id == this->tree->goal->id) {
            // Trace the path
            while(node != nullptr) {
                reached[node->id] = node;
                node = node->parent;
            }
            // Visualize the path
            this->visualizePath(reached);
            return;
        }

        // If this node has already been reached with a shorter path, skip it
        if (reached.find(node->id) != reached.end()) {
            continue;
        }

        // We have reached this node with the shortest possible path
        reached[node->id] = node;

        // For the left and right children
        for (int i = 0; i < 2; i++) {
            Tree::Node* child;
            if (i == 0) { // Left child
                child = node->left;
            } else { // Right child
                child = node->right;
            }

            // If the child is null, continue
            if (child == nullptr) {
                continue;
            }

            // If this child has a shorter path from the current node, update its cost and parent
            if (reached.find(child->id) == reached.end() || node->g + node->g < child->g) {
                child->g = node->g + node->g;
                child->parent = node;
                queue.push(child);
            }
        }
    }

    // If the goal is not found, visualize the final reached path
    this->visualizePath(reached);
    return;
}

void Uninformed::DFS() { // Depth First Search
    // Create a tree
    this->createRandomTree(5, true);

    // Create a stack
    std::stack<Tree::Node*> stack;

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

    // Push the root to the stack
    stack.push(this->tree->root);

    // While the stack is not empty
    while (!stack.empty()) {
        // pop the top of the stack
        Tree::Node* node = stack.top();
        stack.pop();

        // If this node has already been reached, skip it
        if (std::find(reached.begin(), reached.end(), node) != reached.end()) {
            continue;
        }

        // We have reached this node
        reached.push_back(node);

        // If this node is the goal, visualize the path and return
        if (node->id == this->tree->goal->id) {
            this->visualizePath(reached);
            return;
        }

        // For the right and left children (order matters for DFS)
        for (int i = 1; i >= 0; i--) {
            Tree::Node* child;
            if (i == 0) { // Left child
                child = node->left;
            } else { // Right child
                child = node->right;
            }

            // If the child is null, continue
            if (child == nullptr) {
                continue;
            }

            // Push the child to the stack
            stack.push(child);
        }
    }

    // If the goal is not found, visualize the final reached path
    this->visualizePath(reached);
}

void Uninformed::IDS() { // Iterative Deepening Search
    this->createRandomTree(5, true);

    // If the root is null, return
    if (this->tree->root == nullptr) {
        return;
    }

    // For each depth
    for (int depth = 0; depth < 100; depth++) {
        // Create a stack
        std::stack<Tree::Node*> stack;

        // Vector to keep track of visited nodes
        std::vector<Tree::Node*> reached;

        // Push the root to the stack
        stack.push(this->tree->root);

        // While the stack is not empty
        while (!stack.empty()) {
            // pop the top of the stack
            Tree::Node* node = stack.top();
            stack.pop();

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

                // If the child is null, continue
                if (child == nullptr) {
                    continue;
                }

                // If the child is the goal, visualize the path and return
                if (child->id == this->tree->goal->id) {
                    reached.push_back(child);
                    this->visualizePath(reached);
                    return;
                }

                // Push the child to the stack if the depth of reached nodes is less than current limit
                if (reached.size() < depth) {
                    stack.push(child);
                }
            }
        }
    }
}

void Uninformed::DLS(int depth) {
    this->createRandomTree(5, true);
    std::vector<Tree::Node*> reached;
    this->DLS_helper(this->tree->root, reached, depth);
    this->visualizePath(reached);
}

void Uninformed::DLS_helper(Tree::Node* node, std::vector<Tree::Node*>& reached, int limit) {
    // Base cases
    if (node == nullptr) {
        return;
    }
    if (node->id == this->tree->goal->id) {
        reached.push_back(node);
        return;
    }
    if (limit <= 0) {
        return;
    }
    
    // Include current node to reached nodes
    reached.push_back(node);

    // Recursive case
    DLS_helper(node->left, reached, limit - 1);
    DLS_helper(node->right, reached, limit - 1);
}
