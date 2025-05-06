#include <iostream>
using namespace std;

class StackArray {
    int arr[100];
    int top;
public:
    StackArray() { top = -1; }

    void push(int val) {
        if (top < 99) arr[++top] = val;
        else cout << "Stack Overflow\n";
    }

    void pop() {
        if (top >= 0) top--;
        else cout << "Stack Underflow\n";
    }

    void display() {
        if (top == -1) {
            cout << "Stack is Empty\n";
            return;
        }
        for (int i = top; i >= 0; i--)
            cout << arr[i] << " ";
        cout << "\n";
    }
};

struct Node {
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class StackLinkedList {
    Node* top;
public:
    StackLinkedList() { top = nullptr; }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    void pop() {
        if (top) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
        else cout << "Stack Underflow\n";
    }

    void display() {
        if (!top) {
            cout << "Stack is Empty\n";
            return;
        }
        Node* temp = top;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

int main() {
    StackArray sa;
    sa.push(10);
    sa.push(20);
    sa.push(30);
    sa.display();
    sa.pop();
    sa.display();

    StackLinkedList sl;
    sl.push(100);
    sl.push(200);
    sl.push(300);
    sl.display();
    sl.pop();
    sl.display();

    return 0;
}
