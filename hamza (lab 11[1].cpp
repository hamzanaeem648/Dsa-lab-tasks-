#include <iostream>
using namespace std;

class QueueArray {
    int arr[100];
    int front, rear;
public:
    QueueArray() {
        front = -1;
        rear = -1;
    }

    void enqueue(int val) {
        if (rear == 99) return;
        if (front == -1) front = 0;
        arr[++rear] = val;
    }

    void dequeue() {
        if (front == -1 || front > rear) {
            front = rear = -1;
            return;
        }
        front++;
    }

    void display() {
        if (front == -1 || front > rear) {
            cout << "Array Queue is Empty\n";
            return;
        }
        for (int i = front; i <= rear; i++)
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

class QueueLinkedList {
    Node* front;
    Node* rear;
public:
    QueueLinkedList() {
        front = rear = nullptr;
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue() {
        if (!front) return;
        Node* temp = front;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
    }

    void display() {
        if (!front) {
            cout << "Linked List Queue is Empty\n";
            return;
        }
        Node* temp = front;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

int main() {
    QueueArray qa;
    qa.enqueue(1);
    qa.enqueue(2);
    qa.enqueue(3);
    qa.display();
    qa.dequeue();
    qa.display();

    QueueLinkedList ql;
    ql.enqueue(10);
    ql.enqueue(20);
    ql.enqueue(30);
    ql.display();
    ql.dequeue();
    ql.display();

    return 0;
}
