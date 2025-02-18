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

void divideLists(Node* head, Node** left, Node** right, int x){
    Node* elem = head;

    while(elem != NULL){
        if(elem->data < x){
            append(left, elem->data);
        } else {
            append(right, elem->data);
        }
        elem = elem->next;
    }
}

int main(){
    Node* head = NULL;

    append(&head, 1);
    append(&head, 2);
    append(&head, 3);
    append(&head, 4);
    append(&head, 5);
    append(&head, 6);
    append(&head, 7);
    append(&head, 8);

    Node* left = NULL;
    Node* right = NULL;

    divideLists(head, &left, &right, 4);

    display(left);
    display(right);

    return 0;
}