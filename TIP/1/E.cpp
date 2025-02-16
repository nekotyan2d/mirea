#include <iostream>

using namespace std;

class MyStack {
    private:
        int *arr;
        int capacity;
        int top;

        void resize() {
            int newCapacity = capacity * 2;
            int* newArr = new int[newCapacity];
            for (int i = 0; i < capacity; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
    public:
        MyStack(){
            capacity = 2;
            arr = new int[capacity];
            top = -1;
        }

        ~MyStack() {
            delete[] arr;
        }

        void push(int x) {
            if (top == capacity - 1) {
                resize();
            }
            arr[++top] = x;
        }

        void pop(){
            if(top >= 0) {
                cout << arr[top--] << endl;
            }
        }

        void back(){
            if(top >= 0) {
                cout << arr[top] << endl;
            }
        }

        void size(){
            cout << top + 1 << endl;
        }

        void clear(){
            top = -1;
        }
};