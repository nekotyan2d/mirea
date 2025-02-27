#include <iostream>

struct Node {
    int l, r;
    Node* left;
    Node* right;

    Node(int l, int r) : l(l), r(r), left(nullptr), right(nullptr) {}
};

Node* buildTree(int l, int r){
    if(l > r) return nullptr;

    Node* node = new Node(l, r);
    if(l == r) return node;

    int mid = (l + r) / 2;
    node->left = buildTree(l, mid);
    node->right = buildTree(mid + 1, r);

    return node;
}

void inOrderTraversal(Node* node){
    if(node == nullptr) return;

    inOrderTraversal(node->left);
    std::cout << "[" << node->l << ", " << node->r << "]" << std::endl;
    inOrderTraversal(node->right);
}

int countIntervalsContainingX(Node* node, int X){
    if(node == nullptr) return 0;

    int count = 0;
    if(node->l <= X && X <= node->r){
        count = 1;
    }
    count += countIntervalsContainingX(node->left, X);
    count += countIntervalsContainingX(node->right, X);

    return count;
}

int main(){
    int l, r;
    std::cout << "l: ";
    std::cin >> l;

    std::cout << "r: ";
    std::cin >> r;

    Node* root = buildTree(l, r);

    inOrderTraversal(root);

    int x;
    std::cout << "x: ";
    std::cin >> x;
    int count = countIntervalsContainingX(root, x);
    std::cout << "intervals containing " << x << " count: " << count << std::endl;
}