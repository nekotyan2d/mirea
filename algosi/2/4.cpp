#include <iostream>

enum Color
{
    BLACK,
    RED
};

template <typename T>
class RBTree
{

    struct Node
    {
        T data;
        Color color;
        Node *parent, *left, *right;

        Node(T data, Color color) : data(data), color(color), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void rotateLeft(Node *&node)
    {
    }

public:
    void insert(T data)
    {
        Node *node = new Node(data);
        Node *parent = nullptr;
        Node *current = root;

        while (current)
        {
            parent = current;
            if (node->data < current->data)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        node->right = parent;

        if (!parent)
        {
            root = node;
        }
        else if (node->data > parent->data)
        {
            parent->right = node;
        }
        else
        {
            parent->left = node;
        }
    }
};

int main()
{
}