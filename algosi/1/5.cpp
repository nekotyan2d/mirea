#include <iostream>

struct Node {
    int data;
    Node* next;
    Node(int x) : data(x), next(nullptr) {}
};

Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
    }
    return prev;
}

Node* addTwoNumbers(Node* l1, Node* l2, bool isReversed) {
    if (!isReversed) {
        l1 = reverseList(l1);
        l2 = reverseList(l2);
    }

    Node* dummyHead = new Node(0); // фиктивный узел для упрощения кода
    Node* current = dummyHead;
    int carry = 0; // переменная для хранения переноса

    // проходим по обоим спискам
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }

        carry = sum / 10; // вычисляем перенос
        current->next = new Node(sum % 10); // создаем новый узел с текущей цифрой
        current = current->next;
    }

    Node* result = dummyHead->next;
    delete dummyHead; // удаляем фиктивный узел

    if (!isReversed) {
        // если цифры хранились в прямом порядке, реверсируем результат
        result = reverseList(result);
    }

    return result;
}

void printList(Node* head) {
    while (head) {
        std::cout << head->data;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << std::endl;
}

// освобождение памяти
void freeList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // из примера (перевернутые)
    Node* l1 = new Node(2);
    l1->next = new Node(4);
    l1->next->next = new Node(3);

    Node* l2 = new Node(5);
    l2->next = new Node(6);
    l2->next->next = new Node(4);

    Node* result = addTwoNumbers(l1, l2, true);

    printList(result);

    // освобождаем память
    freeList(l1);
    freeList(l2);
    freeList(result);
}
