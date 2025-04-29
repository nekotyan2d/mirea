#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//проверка на полноту бинарного дерева
bool isComplete(TreeNode* root) {
    if (!root) return true;
    queue<TreeNode*> q;
    q.push(root);
    bool end = false;
    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        if (!node) {
            end = true;
        } else {
            if (end) return false;
            q.push(node->left);
            q.push(node->right);
        }
    }
    return true;
}

//проверка на max-heap
bool isMaxHeap(TreeNode* root) {
    if (!root) return true;
    if (root->left) {
        if (root->val < root->left->val) return false;
        if (!isMaxHeap(root->left)) return false;
    }
    if (root->right) {
        if (root->val < root->right->val) return false;
        if (!isMaxHeap(root->right)) return false;
    }
    return true;
}

//проверка на min-heap
bool isMinHeap(TreeNode* root) {
    if (!root) return true;
    if (root->left) {
        if (root->val > root->left->val) return false;
        if (!isMinHeap(root->left)) return false;
    }
    if (root->right) {
        if (root->val > root->right->val) return false;
        if (!isMinHeap(root->right)) return false;
    }
    return true;
}

// Основная функция
bool isHeap(TreeNode* root) {
    if (!isComplete(root)) return false;
    return isMaxHeap(root) || isMinHeap(root);
}

int main(){
    //max-heap
    TreeNode* root1 = new TreeNode(10);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(8);
    root1->left->left = new TreeNode(7);
    root1->left->right = new TreeNode(6);
    root1->right->left = new TreeNode(5);

    cout << "max-heap: " << (isHeap(root1) ? "yes" : "no") << endl;

    //min-heap
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    root2->left->left = new TreeNode(4);
    root2->left->right = new TreeNode(5);

    cout << "min-heap: " << (isHeap(root2) ? "yes" : "no") << endl;

    //не куча
    TreeNode* root3 = new TreeNode(10);
    root3->left = new TreeNode(15);
    root3->right = new TreeNode(8);

    cout << "not heap: " << (isHeap(root3) ? "yes" : "no") << endl;

}