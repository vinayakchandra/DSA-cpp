#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Queue {
    int *arr;
    int qfront;
    int rear;
    int size;

public:
    Queue() {
        size = 100001;
        arr = new int[size];
        qfront = 0;
        rear = 0;
    }

    bool isEmpty() {
        if (qfront == rear) { return true; }
        else { return false; }
    }

    //push
    void enqueue(int data) {
        if (rear == size) {
            cout << "Queue is Full" << endl;
        } else {
            arr[rear] = data;
            rear++;
        }
    }

    //pop
    int dequeue() {
        if (qfront == rear) { return -1; }
        else {
            // pop = first
            int ans = arr[qfront];
            arr[qfront] = -1;
            qfront++;
            //empty
            if (qfront == rear) {
                qfront = 0;
                rear = 0;
            }
            return ans;
        }
    }

    int front() {
        if (qfront == rear) {
            return -1;
        } else {
            return arr[qfront];
        }
    }
};

class CircularQueue {
    int *arr;
    int size;
    int front;
    int rear;
public:
    CircularQueue(int n) {
        size = n;
        arr = new int[size];
        front = -1;
        rear = -1;
    }

    // Enqueues 'X' into the queue. Returns true if it gets pushed into the stack, and false otherwise.
    bool enqueue(int value) {
        //last element / rear = front
        if ((front == 0 && rear == size - 1) || (rear == (front - 1) % (size - 1))) {
            cout << "Queue is Full" << endl;
            return false;
        }
            // 1st element to push
        else if (front == -1) {
            front = rear = 0;
        }
            //circular
        else if (rear == size - 1 && front != 0) {
            rear = 0;
        } else { // normal
            rear++;
        }
        //push
        arr[rear] = value;
        return true;
    }

    // Dequeues top element from queue. Returns -1 if the stack is empty, otherwise returns the popped element.
    int dequeue() {
        //empty
        if (front == -1) {
            cout << "queue is empty" << endl;
            return -1;
        }
        int ans = arr[front];
        arr[front] = -1;
        //single element
        if (rear == front) {
            front = rear = -1;
        }
            //front = last position
        else if (front == size - 1) {
            front = 0;//to maintain cyclic nature
        } else { // normal
            front++;
        }
        return ans;
    }
};

class DoublyEndedQueue {
    int *arr;
    int front;
    int rear;
    int size;
public:
    DoublyEndedQueue(int n) {
        size = n;
        arr = new int[n];
        front = -1;
        rear = -1;
    }

    // Pushes 'X' in the front of the deque. Returns true if it gets pushed into the deque, and false otherwise.
    bool pushFront(int x) {
        //check full or not
        if (isFull()) {
            return false;
        } else if (isEmpty()) {
            front = rear = 0;
        } else if (front == 0 && rear != size - 1) {
            front = size - 1;
        } else {
            front--;
        }
        arr[front] = x;
        return true;
    }

    // Pushes 'X' in the back of the deque. Returns true if it gets pushed into the deque, and false otherwise.
    bool pushRear(int x) {
        if (isFull()) {
            return false;
        } else if (isEmpty()) {
            front = rear = 0;
        } else if (rear == size - 1 && front != 0) {
            rear = 0;
        } else {
            rear++;
        }
        arr[rear] = x;
        return true;
    }

    // Pops an element from the front of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.
    int popFront() {
        if (isEmpty()) {//to check queue is empty
            //cout << "Queue is Empty " << endl;
            return -1;
        }

        int ans = arr[front];
        arr[front] = -1;

        if (front == rear) { //single element is present
            front = rear = -1;
        } else if (front == size - 1) {
            front = 0; //to maintain cyclic nature
        } else {//normal flow
            front++;
        }
        return ans;
    }

    // Pops an element from the back of the deque. Returns -1 if the deque is empty, otherwise returns the popped element.
    int popRear() {
        if (isEmpty()) {//to check queue is empty
            //cout << "Queue is Empty " << endl;
            return -1;
        }

        int ans = arr[rear];
        arr[rear] = -1;

        if (front == rear) { //single element is present
            front = rear = -1;
        } else if (rear == 0) {
            rear = size - 1; //to maintain cyclic nature
        } else {//normal flow
            rear--;
        }
        return ans;
    }

    // Returns the first element of the deque. If the deque is empty, it returns -1.
    int getFront() {
        if (isEmpty()) { return -1; }
        return arr[front];
    }

    // Returns the last element of the deque. If the deque is empty, it returns -1.
    int getRear() {
        if (isEmpty()) { return -1; }
        return arr[rear];
    }

    // Returns true if the deque is empty. Otherwise, returns false.
    bool isEmpty() {
        if (front == -1) { return true; }
        return false;
    }

    // Returns true if the deque is full. Otherwise returns false.
    bool isFull() {
        if ((front == 0 && rear == size - 1) || (front != 0 && rear == (front - 1) % (size - 1))) {
            return true;
        }
        return false;
    }
};

//reverse a queue
queue<int> rev(queue<int> q) {
    stack<int> s;
    queue<int> q2;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q2.push(s.top());
        s.pop();
    }
    return q2;
}

vector<int> printFirstNegativeInteger(int A[], int N, int K) {
    deque<int> dq;
    vector<int> ans;
// k = window
    //process first window of k size
    for (int i = 0; i < K; i++) {
        if (A[i] < 0) {
            dq.push_back(i);
        }
    }
    //store answer of first k sized window
    if (dq.size() > 0) {
        ans.push_back(A[dq.front()]);
    } else {
        ans.push_back(0);
    }
    //process for remaining windows
    for (int i = K; i < N; i++) {
        //removal
        if (!dq.empty() && i - dq.front() >= K) {
            dq.pop_front();
        }
        //then push current element; addition
        if (A[i] < 0) { dq.push_back(i); }
        //ans store
        if (dq.size() > 0) {
            ans.push_back(A[dq.front()]);
        } else {
            ans.push_back(0);
        }
    }
    return ans;
}

queue<int> reverseFirstK(queue<int> q, int k) {
    stack<int> s;
    for (int i = 0; i < k; i++) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    for (int i = 0; i < q.size() - k; i++) {
        q.push(q.front());
        q.pop();
    }
    return q;
}

string FirstNonRepeating(string A) {
    unordered_map<char, int> count;
    queue<int> q;
    string ans = "";
    for (int i = 0; i < A.length(); i++) {
        char ch = A[i];
        //count ++
        count[ch]++;
        //push
        q.push(ch);
        while (!q.empty()) {
            if (count[q.front()] > 1) {
                q.pop();
            } else {
                ans.push_back(q.front());
                break;
            }
        }

        if (q.empty()) {
            ans.push_back('#');
        }
    }
    return ans;
}

struct petrolPump {
    int petrol;
    int distance;
};

int tour(petrolPump p[], int n) {
    int deficit = 0;
    int balance = 0;
    int start = 0;
    for (int i = 0; i < n; i++) {
        balance += p[i].petrol - p[i].distance;
        if (balance < 0) {
            deficit += balance;
            start = i + 1;
            balance = 0;
        }
    }
    if (deficit + balance >= 0) {
        return start;
    } else { return -1; }
}

class kQueue {
public:
    int n;
    int k;
    int *front;
    int *rear;
    int *arr;
    int freeSpot;
    int *next;

    kQueue(int n, int k) {
        this->n = n;
        this->k = k;
        front = new int[k];
        rear = new int[k];

        for (int i = 0; i < k; i++) {
            front[i] = -1;
            rear[i] = -1;
        }

        for (int i = 0; i < n; i++) {
            next[i] = i + 1;
        }
        next[n - 1] = -1; //last

        next = new int[n];
        arr = new int[n];
        freeSpot = 0;
    }

    void enqueue(int data, int qn) {
        //overflow
        if (freeSpot == -1) {
            cout << "no empty space left" << endl;
        }
        //free index
        int index = freeSpot;
        freeSpot = next[index];

        //check for 1st element
        if (front[qn - 1] == -1) {
            front[qn - 1] = index;
        } else {
            //link new element to the prev
            next[rear[qn - 1]] = index;
        }
        //update next
        next[index] = -1;
        //update rear
        rear[qn - 1] = index;
        //push
        arr[index] = data;
    }

    int dequeue(int qn) {
        //underflow
        if (front[qn - 1] == -1) {
            cout << "queue underFlow" << endl;
            return -1;
        }
        //find index to pop
        int index = front[qn - 1];
        //front ko aage badhao
        front[qn - 1] = next[index];
        //free slots ko manage
        next[index] = freeSpot;
        freeSpot = index;
        return arr[index];
    }
};

int sumMaxMinK(int *arr, int n, int k) {
    deque<int> maxi(k);
    deque<int> mini(k);

    //Addition of first k size window
    for (int i = 0; i < k; i++) {

        while (!maxi.empty() && arr[maxi.back()] <= arr[i])
            maxi.pop_back();

        while (!mini.empty() && arr[mini.back()] >= arr[i])
            mini.pop_back();

        maxi.push_back(i);
        mini.push_back(i);
    }
    int ans = 0;
    ans += arr[maxi.front()] + arr[mini.front()];

    //remaining windows ko process karlo
    for (int i = k; i < n; i++) {
        //next window
        //removal
        while (!maxi.empty() && i - maxi.front() >= k) {
            maxi.pop_front();
        }

        while (!mini.empty() && i - mini.front() >= k) {
            mini.pop_front();
        }

        //addition
        while (!maxi.empty() && arr[maxi.back()] <= arr[i])
            maxi.pop_back();

        while (!mini.empty() && arr[mini.back()] >= arr[i])
            mini.pop_back();

        maxi.push_back(i);
        mini.push_back(i);

        ans += arr[maxi.front()] + arr[mini.front()];
    }
    return ans;
}


int main() {
    return 0;
}