#include "AVLTree.h"
#include <algorithm>
#include <iostream>
#include <sstream>


AVLTree::Node::Node(int val)
    : value(val), left(nullptr), right(nullptr), height(1) {}


AVLTree::AVLTree() : root(nullptr) {}


int AVLTree::height(Node* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}


AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}


AVLTree::Node* AVLTree::insert(Node* node, int value) {
    if (!node) return new Node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else if (value > node->value)
        node->right = insert(node->right, value);
    else
        return node; 

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = getBalance(node);

    
    if (balance > 1 && value < node->left->value)
        return rotateRight(node);

    if (balance < -1 && value > node->right->value)
        return rotateLeft(node);

    if (balance > 1 && value > node->left->value) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && value < node->right->value) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}


AVLTree::Node* AVLTree::deleteNode(Node* root, int value) {
    if (!root) return root;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
    }

    if (!root) return root;

    root->height = 1 + std::max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}


void AVLTree::serialize(Node* root, std::ostringstream& out) {
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node) {
            out << node->value << ",";
            q.push(node->left);
            q.push(node->right);
        } else {
            out << "nil,";
        }
    }
}


AVLTree::Node* AVLTree::deserializeHelper(std::vector<std::string>& nodes, int& index) {
    if (index >= (int)nodes.size() || nodes[index] == "nil") {
        index++;
        return nullptr;
    }

    Node* root = new Node(std::stoi(nodes[index++]));
    root->left = deserializeHelper(nodes, index);
    root->right = deserializeHelper(nodes, index);
    root->height = 1 + std::max(height(root->left), height(root->right));
    return root;
}


void AVLTree::insert(int value) {
    root = insert(root, value);
}

void AVLTree::deleteValue(int value) {
    root = deleteNode(root, value);
}

std::string AVLTree::serialize() {
    std::ostringstream out;
    serialize(root, out);
    std::string result = out.str();
    if (!result.empty()) result.pop_back(); 
    return result;
}

void AVLTree::deserialize(const std::string& data) {
    std::vector<std::string> nodes;
    std::stringstream ss(data);
    std::string token;
    while (std::getline(ss, token, ',')) {
        nodes.push_back(token);
    }
    int index = 0;
    root = deserializeHelper(nodes, index);
}