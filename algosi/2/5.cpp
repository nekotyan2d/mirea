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
void insert(Node*& root, const int value) {
    auto newNode = new Node(value);
    Node* parent = nullptr;
    Node* current = root;

    while (current != nullptr) {
        parent = current;
        if (newNode->value < current->value) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == nullptr) {
        root = newNode;
    }
    else if (newNode->value < parent->value) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }
    fixViolation(root, newNode);
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

void fixDelete(Node*& root, Node* x, Node* xParent) {
    while (x != root && (x == nullptr || x->color == BLACK)) {
        if (x == xParent->left) {
            Node* w = xParent->right;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateLeft(root, xParent);
                w = xParent->right;
            }
            if ((w->left == nullptr || w->left->color == BLACK) &&
                (w->right == nullptr || w->right->color == BLACK)) {
                if (w) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->right == nullptr || w->right->color == BLACK) {
                    if (w->left) w->left->color = BLACK;
                    if (w) w->color = RED;
                    rotateRight(root, w);
                    w = xParent->right;
                }
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->right) w->right->color = BLACK;
                rotateLeft(root, xParent);
                x = root;
            }
        } else {
            Node* w = xParent->left;
            if (w && w->color == RED) {
                w->color = BLACK;
                xParent->color = RED;
                rotateRight(root, xParent);
                w = xParent->left;
            }
            if ((w->right == nullptr || w->right->color == BLACK) &&
                (w->left == nullptr || w->left->color == BLACK)) {
                if (w) w->color = RED;
                x = xParent;
                xParent = x->parent;
            } else {
                if (w->left == nullptr || w->left->color == BLACK) {
                    if (w->right) w->right->color = BLACK;
                    if (w) w->color = RED;
                    rotateLeft(root, w);
                    w = xParent->left;
                }
                if (w) w->color = xParent->color;
                xParent->color = BLACK;
                if (w && w->left) w->left->color = BLACK;
                rotateRight(root, xParent);
                x = root;
            }
        }
    }
    if (x) x->color = BLACK;
}
//заменяет корень поддерева в узле U на поддерево с корнем V
void rbTransplant(Node*& root, Node* u, Node* v) {
    if (u->parent == nullptr)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v)
        v->parent = u->parent;
}

void deleteNode(Node*& root, int key) {
    Node* z = root;
    while (z != nullptr && z->value != key) {
        if (key < z->value)
            z = z->left;
        else
            z = z->right;
    }
    if (z == nullptr) return; //не найден

    Node* y = z;
    Color yOriginalColor = y->color;
    Node* x = nullptr;
    Node* xParent = nullptr;

    if (z->left == nullptr) {
        x = z->right;
        xParent = z->parent;
        rbTransplant(root, z, z->right);
    } else if (z->right == nullptr) {
        x = z->left;
        xParent = z->parent;
        rbTransplant(root, z, z->left);
    } else {
        y = minValueNode(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            if (x) x->parent = y;
            xParent = y;
        } else {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            if (y->right) y->right->parent = y;
            xParent = y->parent;
        }
        rbTransplant(root, z, y);
        y->left = z->left;
        if (y->left) y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == BLACK)
        fixDelete(root, x, xParent);
}

int main() {
    Node* root = nullptr;

    insert(root, 7);
    insert(root, 2);
    insert(root, 17);
    insert(root, 9);
    insert(root, 21);
    insert(root, 6);
    insert(root, 15);

    printNode(root);
    cout << endl;

    deleteNode(root, 17);
    printNode(root);
    cout << endl;

    return 0;
}