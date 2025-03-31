#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
    
    Node(int value) : data(value), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* node) {
    return node ? node->height : 0;
}

void updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

int balanceFactor(Node* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Node* insert(Node* root, int value) {
    if (!root) return new Node(value);
    
    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    
    updateHeight(root);
    return root;
}

void print(Node* root, const std::string& prefix = "", bool isLeft = false) {
    if (!root) return;
    
    std::cout << prefix << " ";
    std::cout << root->data << " [balance: " << balanceFactor(root) << "]" << std::endl;
    
    print(root->left, prefix + (isLeft ? "   " : "    "), true);
    print(root->right, prefix + (isLeft ? "   " : "    "), false);
}

void del(Node* root) {
    if (!root) return;
    del(root->left);
    del(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    
    root = insert(root, 8);
    root = insert(root, 4);
    root = insert(root, 12);
    root = insert(root, 3);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 10);
    
    print(root);
    
    del(root);
    return 0;
}