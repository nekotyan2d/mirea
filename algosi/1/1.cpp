#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void append(Node** head, int data){
    Node* new_node = new Node();
    Node* last = *head;
    new_node->data = data;
    new_node->next = NULL;
    if(*head == NULL){
        new_node->prev = NULL;
        *head = new_node;
        return;
    }
    while(last->next != NULL){
        last = last->next;
    }
    last->next = new_node;
    new_node->prev = last;
}

void display(Node* node){
    while(node != NULL){
        cout << node->data << " <-> ";
        node = node->next;
    }
    cout << "NULL" << endl;
}

bool hasCycle(Node* head){
    Node* slow = head;
    Node* fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast){
            return true;
        }
    }

    return false;
}

int main(){
    Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);

    // проверяем, работает ли функция, должно вывести "no"
    cout << (hasCycle(head) ? "yes" : "no") << endl;

    Node* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = head->next;
    
    cout << (hasCycle(head) ? "yes" : "no") << endl;
}