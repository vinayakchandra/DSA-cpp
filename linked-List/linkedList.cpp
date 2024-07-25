#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node *next;

    //constructor
    Node(int data) {
        this->data = data;
        this->next = NULL;
    }

    //destructor
    ~Node() {
        int value = this->data;
        //freeing the memory
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
        }
        cout << "memory is free for node with data: " << value << endl;
    }
};

void insertAtHead(Node *&head, int d) {
    // new node
    Node *temp = new Node(d);

    temp->next = head;
    head = temp;
    // new node banake Head me insert kardi
}

void insertAtTail(Node *&tail, int d) {
    Node *temp = new Node(d);
    tail->next = temp;
//    tail = tail->next;
    tail = temp;
}

void insertAtPosition(Node *&tail, Node *&head, int position, int d) {
    // (n-1)th node position
    Node *temp = head;
    int count = 1;
    //traverse
    while (count < position - 1) {
        temp = temp->next;
        count++;
    }
    // inserting at 1st position
    if (position == 1) {
        insertAtHead(head, d);
        return;
    }
    //inserting in last position
    if (temp->next == NULL) {
        insertAtTail(tail, d);
        return;
    }
    // creating a node for d
    Node *nodeToInsert = new Node(d);
    nodeToInsert->next = temp->next;
    temp->next = nodeToInsert;
}

void printNode(Node *&head) {
    Node *temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
};

void deleteNodeAtPosition(Node *&head, int position) {
    // deleting at start
    if (position == 1) {
        Node *temp = head;
        head = head->next;
        //memory free
        temp->next = NULL;
        delete temp;
        return;
    }
    // deleting at middle or last
    Node *curr = head;
    Node *prev = NULL;
    int count = 1;

    while (count < position) {
        prev = curr;
        curr = curr->next;
        count++;
    }
    prev->next = curr->next;
    curr->next = NULL;
    delete curr;
}

int main() {
    //new node
    Node *node1 = new Node(5);
//    cout << node1->data << endl;
//    cout << node1->next << endl;

    // head pointed to node1
    Node *head = node1;
    printNode(head);
    Node *tail = node1;

    insertAtTail(tail, 15);
    printNode(head);

    insertAtTail(tail, 10);
    printNode(head);

    insertAtPosition(tail, head, 4, 7);
    printNode(head);

    deleteNodeAtPosition(head, 1);
    printNode(head);

    return 0;
}