#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <sstream>
#include <queue>
#include <vector>

class AVLTree {
private:
    
    struct Node {
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int val);
    };

    Node* root;

    
    int height(Node* node);
    int getBalance(Node* node);

    
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* y);

    
    Node* insert(Node* node, int value);
    Node* deleteNode(Node* node, int value);
    Node* minValueNode(Node* node);

    
    void serialize(Node* root, std::ostringstream& out);
    Node* deserializeHelper(std::vector<std::string>& nodes, int& index);

public:
    
    AVLTree();
    void insert(int value);
    void deleteValue(int value);

    std::string serialize();
    void deserialize(const std::string& data);
};

#endif