#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree tree;

    
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    std::cout << "Serialized AVL Tree: " << tree.serialize() << std::endl;

    
    tree.deleteValue(6);
    std::cout << "After deleting 6: " << tree.serialize() << std::endl;

    
    std::string data = "4,3,5,nil,nil,nil,nil";
    AVLTree newTree;
    newTree.deserialize(data);
    std::cout << "Deserialized Tree: " << newTree.serialize() << std::endl;

    return 0;
}
