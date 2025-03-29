#include <iostream>
#include <algorithm>

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    Node* root;
    
    int height(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
    
    int balance(Node* N) {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }
    
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        
        x->right = y;
        y->left = T2;
        
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
        
        return x;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        
        y->left = x;
        x->right = T2;
        
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;
        
        return y;
    }
    
    Node* insertNode(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);
            
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else return node;
            
        node->height = 1 + std::max(height(node->left), height(node->right));
        int bal = balance(node);
        
        if (bal > 1 && key < node->left->key)
            return rightRotate(node);
            
        if (bal < -1 && key > node->right->key)
            return leftRotate(node);
            
        if (bal > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        
        if (bal < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        
        return node;
    }
    
    void inOrder(Node* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->key << " ";
            inOrder(node->right);
        }
    }
    
    void del(Node* node) {
        if (node != nullptr) {
            del(node->left);
            del(node->right);
            delete node;
        }
    }
    
public:
    AVLTree() : root(nullptr) {}
    
    ~AVLTree() {
        del(root);
    }
    
    void insert(int key) {
        root = insertNode(root, key);
    }
    
    void print() {
        inOrder(root);
        std::cout << std::endl;
    }
};

int main() {
    AVLTree tree;
    
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);  //перебалансировка
    tree.insert(40);
    tree.insert(50);  //перебалансировка
    tree.insert(25);
    
    tree.print();
    
    return 0;
}