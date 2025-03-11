#include <iostream>

struct Node {
    int data, balance;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr), balance(0) {}
};

Node* insert(Node* node, int data){
    if(node == nullptr){
        return new Node(data);
    }

    if(data < node->data){
        node->left = insert(node->left, data);
    } else {
        node->right = insert(node->right, data);
    }

    return node;
}

int height(Node* node){
    if(node == nullptr){
        return 0;
    }

    return 1 + std::max(height(node->left), height(node->right));
}

void balance(Node* root){
    if(root == nullptr){
        return;
    }

    root->balance = height(root->left) - height(root->right);

    balance(root->left);
    balance(root->right);
}

void inOrder(Node* node){
    if(node != nullptr){
        inOrder(node->left);
        std::cout << node->data << "(" << node->balance << ")" << " ";
        inOrder(node->right);
    }
}

int main(){
    Node* root = nullptr;

    root = insert(root, 14);
    root = insert(root, 52);
    root = insert(root, 88);
    root = insert(root, 7);
    root = insert(root, 52);
    root = insert(root, 1);

    balance(root);

    inOrder(root);

    std::cout << std::endl;

    return 0;
}