// TASK 2.4.1
#include <iostream>
#include <stack>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int value;
    Color color;
    Node *left;
    Node *right;
    Node *parent;

    explicit Node(const int val) : value(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

void rotateLeft(Node *&root, Node *node)
{
    Node *rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != nullptr)
    {
        node->right->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr)
    {
        root = rightChild;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = rightChild;
    }
    else
    {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

void rotateRight(Node *&root, Node *node)
{
    Node *leftChild = node->left;
    node->left = leftChild->right;

    if (node->left != nullptr)
    {
        node->left->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr)
    {
        root = leftChild;
    }
    else if (node == node->parent->left)
    {
        node->parent->left = leftChild;
    }
    else
    {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

void fixViolation(Node *&root, Node *&pt)
{
    Node *parent_pt = nullptr;
    Node *grand_parent_pt = nullptr;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED))
    {
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;

        if (parent_pt == grand_parent_pt->left)
        {
            Node *uncle_pt = grand_parent_pt->right;

            if (uncle_pt != nullptr && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->right)
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateRight(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        else
        {
            Node *uncle_pt = grand_parent_pt->left;

            if (uncle_pt != nullptr && uncle_pt->color == RED)
            {
                grand_parent_pt->color = RED;
                parent_pt->color = BLACK;
                uncle_pt->color = BLACK;
                pt = grand_parent_pt;
            }
            else
            {
                if (pt == parent_pt->left)
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }

                rotateLeft(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }

    root->color = BLACK;
}

void printNode(const Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    std::stack<const Node *> stack;
    const Node *current = root;

    while (current != nullptr || !stack.empty())
    {
        while (current != nullptr)
        {
            stack.push(current);
            current = current->left;
        }

        current = stack.top();
        stack.pop();
        cout << current->value << " " << (current->color == RED ? "RED" : "BLACK") << endl;
        current = current->right;
    }
}
