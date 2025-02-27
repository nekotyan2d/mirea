#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

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
    Node* head1_1 = new Node(1);
    Node* head2_1 = new Node(2);
    Node* head3_1 = new Node(3);
    Node* head4_1 = new Node(4);

    head1_1->next = head2_1;
    head2_1->next = head3_1;
    head3_1->next = head4_1;

    // проверяем, работает ли функция, должно вывести "no"
    cout << (hasCycle(head1_1) ? "yes" : "no") << endl;

    Node* head1_2 = new Node(1);
    Node* head2_2 = new Node(2);
    Node* head3_2 = new Node(3);
    Node* head4_2 = new Node(4);

    head1_2->next = head2_2;
    head2_2->next = head3_2;
    head3_2->next = head2_2; // ссылаемся на узел из середины
    
    cout << (hasCycle(head1_2) ? "yes" : "no") << endl;
}