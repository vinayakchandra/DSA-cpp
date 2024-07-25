#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    //constructor
    Node(int d) {
        this->data = d;
        this->next = NULL;
    }

    // destructor
    ~Node() {
        int value = this->data;
        if (this->next != NULL) {
            delete next;
            next = NULL;
        }
        cout << "memory is free for node with data " << value << endl;
    }
};

void insertNode(Node *&tail, int element, int d) {
    //empty list
    if (tail == NULL) {
        Node *newNode = new Node(d);
        tail = newNode;
        newNode->next = newNode;
        return;
    }
    //non-empty list
    //assuming that the element is present in the list
    Node *curr = tail;

    while (curr->data != element) {
        curr = curr->next;
    }
    //element found -> curr is representing element wala node
    Node *temp = new Node(d);
    temp->next = curr->next;
    curr->next = temp;

}

void printNode(Node *tail) {
    Node *temp = tail;

    //empty list
    if (tail == NULL) {
        cout << "List is Empty " << endl;
        return;
    }

    do {
        cout << tail->data << " ";
        tail = tail->next;
    } while (tail != temp);
    cout << endl;
}

void deleteNode(Node *&tail, int value) {
    //empty node
    if (tail == NULL) {
        cout << "list is empty" << endl;
        return;
    }
    //value is there
    Node *prev = tail;
    Node *curr = prev->next;

    while (curr->data != value) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;
    //1 node LL
    if (curr == prev) {
        tail = NULL;
    }
        //>=2 node LL
    else if (tail == curr) {
        tail = prev;
    }
    curr->next = NULL;
    delete curr;
}

int main() {
    Node *tail = NULL;

    insertNode(tail, 5, 10);
    insertNode(tail, 10, 5);
    printNode(tail);
    insertNode(tail, 5, 15);
    printNode(tail);
    insertNode(tail, 10, 20);
    printNode(tail);
    insertNode(tail, 5, 10);
    printNode(tail);
    deleteNode(tail, 15);
    printNode(tail);
    return 0;
}