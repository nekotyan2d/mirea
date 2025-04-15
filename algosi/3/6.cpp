#include <iostream>
#include <stdexcept>

// Структура узла для очереди с приоритетом
struct Node {
    int data;        // Значение элемента
    int priority;    // Приоритет элемента (меньшее значение - более высокий приоритет)
    Node* next;      // Указатель на следующий узел
    
    Node(int d, int p) : data(d), priority(p), next(nullptr) {}
};

class PriorityQueue {
private:
    Node* front;  // Указатель на начало очереди
    
public:
    PriorityQueue() : front(nullptr) {}
    
    ~PriorityQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    
    bool isEmpty() {
        return front == nullptr;
    }
    
    void enqueue(int data, int priority) {
        Node* newNode = new Node(data, priority);
        
        if (isEmpty() || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        } else {
            Node* current = front;
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }
            
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    
    int dequeue() {
        Node* temp = front;
        int data = temp->data;
        
        front = front->next;
        delete temp;
        
        return data;
    }
    
    int first() {
        return front->data;
    }
    
    void display() {
        Node* current = front;
        std::cout << "priority queue: ";
        while (current != nullptr) {
            std::cout << "(" << current->data << ", " << current->priority << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    PriorityQueue queue;
    
    queue.enqueue(10, 2);
    queue.enqueue(30, 1); // более высокий приоритет
    queue.enqueue(20, 3);
    queue.enqueue(40, 1); // такой же приоритет, как у 30, будет после него
    
    queue.display();
    
    std::cout << "dequeue: " << queue.dequeue() << std::endl;
    std::cout << "dequeue: " << queue.dequeue() << std::endl;
    
    queue.display();
    
    return 0;
}