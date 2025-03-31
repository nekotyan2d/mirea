#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    
    Node(int key) : key(key), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* root;
    
    Node* rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }
    
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }
    
    Node* splay(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;
            
        if (key < root->key) {
            if (root->left == nullptr)
                return root;
                
            if (key < root->left->key) {
                root->left->left = splay(root->left->left, key);
                root = rightRotate(root);
            } else if (key > root->left->key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = leftRotate(root->left);
            }
            
            return (root->left == nullptr) ? root : rightRotate(root);
        } else {
            if (root->right == nullptr)
                return root;
                
            if (key < root->right->key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = rightRotate(root->right);
            } else if (key > root->right->key) {
                root->right->right = splay(root->right->right, key);
                root = leftRotate(root);
            }
            
            return (root->right == nullptr) ? root : leftRotate(root);
        }
    }
    
    Node* findMax(Node* root) {
        if (root == nullptr)
            return nullptr;
            
        while (root->right != nullptr)
            root = root->right;
            
        return root;
    }
    
    void del(Node* node) {
        if (node != nullptr) {
            del(node->left);
            del(node->right);
            delete node;
        }
    }
    
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }
    
public:
    SplayTree() : root(nullptr) {}
    
    ~SplayTree() {
        del(root);
    }
    
    void insert(int key) {
        if (root == nullptr) {
            root = new Node(key);
            return;
        }
        
        root = splay(root, key);
        
        if (root->key == key)
            return;
            
        Node* newNode = new Node(key);
        
        if (key < root->key) {
            newNode->right = root;
            newNode->left = root->left;
            root->left = nullptr;
        } else {
            newNode->left = root;
            newNode->right = root->right;
            root->right = nullptr;
        }
        
        root = newNode;
    }
    
    void remove(int key) {
        if (root == nullptr)
            return;
            
        root = splay(root, key);
        
        if (root->key != key)
            return;
            
        if (root->left == nullptr) {
            Node* temp = root;
            root = root->right;

            delete temp;
        } else {
            Node* temp = root;
            root = root->left;
            root = splay(root, temp->key);
            root->right = temp->right;
            
            delete temp;
        }
    }
    
    bool search(int key) {
        if (root == nullptr)
            return false;
            
        root = splay(root, key);
        return (root->key == key);
    }
    
    void display() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    SplayTree tree;
    
    tree.insert(10);
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    
    tree.display();
    
    if (tree.search(30))
        cout << "30 found" << endl;
    else
        cout << "30 not found" << endl;
    
    cout << "tree: ";
    tree.display();

    cout << "delete 30" << endl;
    tree.remove(30);
    cout << "tree: ";
    tree.display();
    
    if (tree.search(70))
        cout << "70 found" << endl;
    else
        cout << "70 not found" << endl;
    
    cout << "tree: ";
    tree.display();
    
    return 0;
}