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
public:
    CircularList(): head(nullptr) {}
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
                return;
            }
            current = current->next;
        } while(current != head);
    }

    void print() {
        if(head == nullptr){
            std::cout << "empty list" << std::endl;
            return;
        }

        Node* current = head;
        do {
            std::cout << current->data << " ";
            current = current->next;
        } while(current != head);
        std::cout << std::endl;
    }

    bool isCircular() {
        if(head == nullptr) return true;

        Node* current = head;
        while(current->next != head){
            if(current->next == nullptr){
                return false;
            }
            current = current->next;
        }
        return false;
    }
};

int main(){
    CircularList list;

    list.append(2);
    list.append(8);
    list.append(16);

    list.print();

    list.remove(8);
    list.print();

    std::cout << "list is circular: " << (list.isCircular() ? "yes" : "no") << std::endl;

    list.remove(2);
    list.remove(16);

    list.print();
}