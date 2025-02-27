#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
};

class CircularList{
private:
    Node* head;
    int size;
public:
    CircularList(): head(nullptr), size(0) {}
    ~CircularList() {
        clear();
    }

    void clear(){
        if(head == nullptr) return;

        Node* current = head;
        Node* nextNode;

        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while(current != head);

        head = nullptr;
        size = 0;
    }

    void append(int data){
        Node* newNode = new Node(data);

        if(head == nullptr){
            head = newNode;
            head->next = head;
            head->prev = head;
        } else {
            newNode->next = head;
            newNode->prev = head->prev;
            head->prev->next = newNode;
            head->prev = newNode;
        }
        size++;
    }

    void insertBefore(int target, int data){
        if(!head) return;

        Node* current = head;
        do {
            if(current->data == target){
                Node* newNode = new Node(data);
                newNode->next = current;
                newNode->prev = current->prev;
                current->prev->next = newNode;
                current->prev = newNode;
                if(current == head) head == newNode;
                size++;
                return;
            }
            current = current->next;
        } while(current != head);
    }

    void remove(int data){
        if(head == nullptr) return;

        Node* current = head;
        do {
            if(current->data == data){
                if(current == head && head->next == head){
                    delete head;
                    head = nullptr;
                    return;
                }

                current->prev->next = current->next;
                current->next->prev = current->prev;

                if(current == head){
                    head = head->next;
                }

                delete current;
                size--;
                return;
            }
            current = current->next;
        } while(current != head);
    }

    int count() const {
        return size;
    }

    void printForward() {
        if(!head) return;

        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while(current != head);
        std::cout << std::endl;
    }

    void printBackward() {
        if(!head) return;

        Node* current = head->prev;
        do {
            std::cout << current->data << " ";
            current = current->prev;
        } while(current != head->prev);
        std::cout << std::endl;
    }
};

int main(){
    CircularList list;

    list.append(2);
    list.append(8);
    list.append(16);
    list.insertBefore(16, 12);
    list.remove(8);

    std::cout << "forward: " << std::endl;
    list.printForward();

    std::cout << "backward: " << std::endl;
    list.printBackward();

    std::cout << "count: " << list.count() << std::endl;
}