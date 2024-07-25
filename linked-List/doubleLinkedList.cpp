#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *prev;
    Node *next;

    //constructor
    Node(int d) {
        this->data = d;
        this->prev = NULL;
        this->next = NULL;
    }

    //destructor
    ~Node() {
        int val = this->data;
        if (this->next != NULL) {
            delete this->next;
            next = NULL;
        }
        cout << "memory for node with data: " << val << endl;
    }
};

void printNode(Node *&head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
};

//length of nodes
int getLength(Node *&head) {
    Node *temp = head;
    int length = 0;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
};

void insertAtHead(Node *&head, Node *&tail, int d) {
    //empty node
    if (head == NULL) {
        Node *temp = new Node(d);
        head = temp;
        tail = temp;
        return;
    }
    Node *temp = new Node(d);
    temp->next = head;
    head->prev = temp;
    head = temp;
}


void insertAtTail(Node *&head, Node *&tail, int d) {
    //empty node
    if (tail == NULL) {
        Node *temp = new Node(d);
        head = temp;
        tail = temp;

        return;
    }
    Node *temp = new Node(d);
    tail->next = temp;
    temp->prev = tail;
    tail = temp;

}


void insertAtPosition(Node *&head, Node *&tail, int position, int d) {
    //at 1st
    if (position == 1) {
        insertAtHead(head, tail, d);
        return;
    }

    Node *temp = head;
    int count = 0;
    while (count < position - 1) {
        temp = temp->next;
        count++;
    }
    //insert at last
    if (temp->next == NULL) {
        insertAtTail(head, tail, d);
        return;
    }
    //creating a node for d
    Node *nodeToInsert = new Node(d);
    nodeToInsert->next = temp->next;//new node ka next = next temp node
    temp->next->prev = nodeToInsert;//temp ke next node ka prev
    temp->next = nodeToInsert;
    nodeToInsert->prev = temp;

}

void deleteNodeAtPosition(Node *&head, int position) {
    //start
    if (position == 1) {
        Node *temp = head;
        temp->next->prev = NULL;
        head = temp->next;
        temp->next = NULL;
        delete temp;
        return;
    }
    //mid/last
    Node *curr = head;
    Node *prev = NULL;
    int count = 1;
    while (count < position) {
        prev = curr;
        curr = curr->next;
        count++;
    }
    curr->prev = NULL;
    prev->next = curr->next;
    curr->next = NULL;
    delete curr;
}

int main() {
    Node *node1 = new Node(10);
    Node *head = node1;
    Node *tail = node1;
    printNode(head);
    insertAtHead(head, tail, 15);
    insertAtTail(head, tail, 20);
    insertAtPosition(head, tail, 2, 5);
    printNode(head);
    deleteNodeAtPosition(head, 4);
    printNode(head);
//    cout << getLength(head) << endl;
    return 0;
}