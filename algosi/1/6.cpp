#include <iostream>
#include <ctime>

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

class BSL {
    Node* root;
private:
    Node* insert(Node* root, int data){
        Node* newNode = new Node(data);

        if(!root) return newNode;
        
        if(root->data > data) {
            root->left = insert(root->left, data);
        }else{
            root->right = insert(root->right, data);
        }
        return root;
    }

    int find_depth(Node* node){
        if(!node) return 0;
        return 1 + std::max(find_depth(node->left), find_depth(node->right));
    }

    bool find(Node* node, int data){
        if(!node) return false;

        if(node->data == data){
            return true;
        }else{
            return node->data > data ? find(node->left, data) : find(node->right, data);
        }
    }

    Node* remove(Node* node, int data){
        if(!node) return nullptr;

        if(node->data > data){
            node->left = remove(node->left, data);
        } else if(node->data < data) {
            node->right = remove(node->right, data);
        } else {
            if(!node->left){
                Node* temp = node->right;
                delete node;
                return temp;
            } else if(!node->right){
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = total_left();
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        return node;
    }

    Node* total_left(){
        Node* node = root;
        while(node->left != nullptr){
            node = node->left;
        }
        return node;
    }
public:
    BSL(int data) {
        root = new Node(data);
    }

    void insert(int data){
        insert(root, data);
    }

    void preorder(Node* root){
        if(root){
            std::cout << root->data << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    int find_depth(){
        return find_depth(root);
    }

    bool find(int data){
        return find(root, data);
    }

    void remove(int data){
        remove(root, data);
    }

    Node* get_root(){
        return root;
    }
};

int random(){
    return std::rand() % 101;
}

int main(){
    srand(time(NULL));
    int n;

    std::cout << "n: ";
    std::cin >> n;

    BSL* bsl = new BSL(random());

    for(int i = 0; i < n; i++){
        bsl->insert(random());
    }

    bsl->preorder(bsl->get_root());

    std::cout << std::endl << "depth: " << bsl->find_depth() << std::endl;

    int i;
    std::cout << "find: ";
    std::cin >> i;

    std::cout << (bsl->find(i) ? "found" : "not found") << std::endl;

    int d;
    std::cout << "delete: ";
    std::cin >> d;
    bsl->remove(d);

    bsl->preorder(bsl->get_root());
}