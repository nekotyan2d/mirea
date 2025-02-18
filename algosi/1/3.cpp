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

void deleteNode(Node** head, int data){
    Node* elem = *head;

    if(elem->data == data){
        if(elem->prev != NULL){
            elem->prev->next = elem->next;
        }else{
            *head = elem->next;
        }
    }
}

void display(Node* node){
    while(node != NULL){
        cout << node->data << " <-> ";
        node = node->next;
    }
    cout << "NULL" << endl;
}

int main(){

}