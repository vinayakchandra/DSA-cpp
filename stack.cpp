#include <iostream>
#include <stack>

using namespace std;

void basicStack() {
    //create stack
    stack<int> s;

    //push
    s.push(2);
    s.push(5);

    //pop
    s.pop();

    cout << "printing the top element " << s.top() << endl;

    //empty
    if (s.empty()) { cout << "empty stack" << endl; }
    else { cout << "not empty" << endl; }

    //size
    cout << "size of stack is " << s.size() << endl;
}

class Stack {
    //properties
public:
    int *arr;
    int top;
    int size;

    //behaviour
    Stack(int size) {
        this->size = size;
        arr = new int[size];
        top = -1;
    }

    void push(int element) {
        if (size - top > 1) {
            top++;
            arr[top] = element;
        } else {
            cout << "stack overflow" << endl;
        }
    }

    void pop() {
        if (top >= 0) {
            top--;
        } else {
            cout << "stack underflow" << endl;
        }
    }

    int peek() {
        if (top >= 0) {
            return arr[top];
        } else {
            cout << "stack is empty" << endl;
            return -1;
        }
    }

    bool isEmpty() {
        if (top == -1) { return true; }
        else { return false; }
    }

};

//SP: O(N), TC: O(N)
string reverseString(string str) {
    stack<char> st;
    for (int i = 0; i < str.length(); i++) {
        st.push(str[i]);
    }
    string ans = "";
    while (!st.empty()) {
        char ch = st.top();
        ans.push_back(ch);
        st.pop();
    }
    return ans;
}

//delete middle element
void solve(stack<int> &inputStack, int count, int size) {
    if (count == size / 2) {
        inputStack.pop();
        return;
    }
    //side me nikal ke rakh liya
    int num = inputStack.top();
    inputStack.pop();
    //recursive call
    solve(inputStack, count + 1, size);
    //phir add kar diya
    inputStack.push(num);
}

void deleteMid(stack<int> &inputStack, int size) {
    int count = 0;
    solve(inputStack, count, size);
}

// [({})]
bool isValidParenthesis(string str) {
    stack<char> st;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        //is opening; stack push
        //is closing; stack top check and pop

        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        } else {
            if (!st.empty()) {
                if ((ch == ')' && st.top() == '(') ||
                    (ch == '}' && st.top() == '{') ||
                    (ch == ']' && st.top() == '[')) {
                    cout << "valid" << endl;
                    st.pop();
                } else { return false; }
            } else {
                return false;
            }
        }
    }
    if (st.empty()) {
        return true;
    } else {
        return false;
    }
}

//add element at the bottom of the stack
void solve(stack<int> &s, int x) {
    //empty stack
    if (s.empty()) {
        s.push(x);
        return;
    }
    int num = s.top();
    s.pop();
    solve(s, x);
    s.push(num);
}

stack<int> pushAtBottom(stack<int> &myStack, int x) {
    solve(myStack, x);
    return myStack;
}

//reverse a stack
void reverseStack(stack<int> &stack) {
    //empty
    if (stack.empty()) {
        return;
    }
    int num = stack.top();
    stack.pop();
    //recursive
    reverseStack(stack);

    //insert at bottom
    pushAtBottom(stack, num);
}

//sort a stack
void sortedInsert(stack<int> &stack, int num) {
    if (stack.empty() || (num > stack.top())) {
        stack.push(num);
        return;
    }
    int n = stack.top();
    stack.pop();
    sortedInsert(stack, num);
    stack.push(n);
}

void sortStack(stack<int> &stack) {
    //empty
    if (stack.empty()) { return; }
    int num = stack.top();
    stack.pop();

    //recursive call
    sortStack(stack);

    sortedInsert(stack, num);
}

// (a+b+(c))
bool findRedundantBrackets(string &s) {
    stack<char> st;
    // pushing symbols for stack
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        if (ch == '(' || ch == '+' || ch == '-' || ch == '/' || ch == '*') {
            st.push(ch);
        } else if (ch == ')') {
            bool isRedundant = true;
            while (st.top() != '(') {
                char top = st.top();
                if (top == '+' || top == '-' || top == '/' || top == '*') {
                    isRedundant = false;
                }
                st.pop();
            }
            if (isRedundant == true) {
                return true;
            }
            //'(' mil gaya
            st.pop();
        }
    }
    return false;
}

// {}{}{}{}
int findMinimumCost(string str) {
    //odd length
    if (str.length() % 2 == 1) { return -1; }
    //even length
    stack<char> st;
    for (int i = 0; i < str.length(); i++) {
        char ch = str[i];
        if (ch == '{') {
            st.push(ch);
        } else {
            //removal of valid-> {}
            if (!st.empty() && st.top() == '{') {
                // {} found
                st.pop();
            } else {
                // other than {}
                st.push(ch);
            }
        }
    }
    //stack contains invalid expression
    int close = 0, open = 0;
    while (!st.empty()) {
        if (st.top() == '{') { open++; }
        else { close++; }
        st.pop();
    }
    //expression
    int ans = (open + 1) / 2 + (close + 1) / 2;
    return ans;
}

//TC: O(n)
vector<int> nextSmallerElement(vector<int> &arr, int n) {
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; i--) {
        //jab tak chota na mile, pop kardo
        while (s.top() >= arr[i]) {
            s.pop();
        }
        //ans is stack ka top
        ans[i] = s.top();
        //chote wale ko push kardo
        s.push(arr[i]);
    }
    return ans;
}

// hard levels 😭😭😭😭😭😭

//largest area - histogram; TC, SC = O(N)
vector<int> nextSmallerElement2(vector<int> arr, int n) {
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);

    for (int i = n - 1; i >= 0; i--) {
        int curr = arr[i];
        while (s.top() != -1 && arr[s.top()] >= curr) {
            s.pop();
        }
        //ans is stack ka top
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

vector<int> prevSmallerElement2(vector<int> arr, int n) {
    stack<int> s;
    s.push(-1);
    vector<int> ans(n);

    for (int i = 0; i < n; i++) {
        int curr = arr[i];
        while (s.top() != -1 && arr[s.top()] >= curr) {
            s.pop();
        }
        //ans is stack ka top
        ans[i] = s.top();
        s.push(i);
    }
    return ans;
}

int largestRectangleArea(vector<int> &heights) {
    int n = heights.size();
    //index of next
    vector<int> next(n);
    next = nextSmallerElement2(heights, n);

    //index of prev
    vector<int> prev(n);
    prev = prevSmallerElement2(heights, n);

    int area = INT_MIN;
    for (int i = 0; i < n; i++) {
        int l = heights[i];

        if (next[i] == -1) {
            next[i] = n;
        }
        int b = next[i] - prev[i] - 1; // n-p-1
        int newArea = l * b;
        area = max(area, newArea);
    }
    return area;
}

// celebrity kisko nahi jaanta; sab celebrity ko jaante hai
//TC O(n)
bool knows(vector<vector<int> > &M, int a, int b, int n) {
    if (M[a][b] == 1) { return true; }
    else { return false; }
}

int celebrity(vector<vector<int> > &M, int n) {
    stack<int> s;
    //ignore diagonal element
    //step1: push all element in stack
    for (int i = 0; i < n; i++) {
        s.push(i);
    }

    //step2: get 2 elements and compare them
    // stack size >1
    while (s.size() > 1) {
        int a = s.top();
        s.pop();

        int b = s.top();
        s.pop();

        if (knows(M, a, b, n)) { s.push(b); }
        else { s.push(a); }
    }
    //1 element left in stack
    int ans = s.top();
    //step3: single element in stack is potential celeb
    //verify it
    int zeroCount = 0;

    for (int i = 0; i < n; i++) {
        if (M[ans][i] == 0) { zeroCount++; }
    }

    //all zeroes
    if (zeroCount != n) { return -1; }

    //column check
    int oneCount = 0;

    for (int i = 0; i < n; i++) {
        if (M[i][ans] == 1) {
            oneCount++;
        }
    }

    if (oneCount != n - 1) { return -1; }

    return ans;
}

// max area of rectangle in binary matrix
class Solution {
    vector<int> nextSmallerElement(int *arr, int n) {
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);
        for (int i = n - 1; i >= 0; i--) {
            int curr = arr[i];
            while (s.top() != -1 && arr[s.top()] >= curr) {
                s.pop();
            }
            //ans is stack ka top
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }

    vector<int> prevSmallerElement(int *arr, int n) {
        stack<int> s;
        s.push(-1);
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            int curr = arr[i];
            while (s.top() != -1 && arr[s.top()] >= curr) {
                s.pop();
            }
            //ans is stack ka top
            ans[i] = s.top();
            s.push(i);
        }
        return ans;
    }


    int largestRectangleArea(int *heights, int n) {
        //int n= heights.size();
        vector<int> next(n);
        next = nextSmallerElement(heights, n);

        vector<int> prev(n);
        prev = prevSmallerElement(heights, n);

        int area = INT_MIN;
        for (int i = 0; i < n; i++) {
            int l = heights[i];
            if (next[i] == -1) {
                next[i] = n;
            }
            int b = next[i] - prev[i] - 1;
            int newArea = l * b;
            area = max(area, newArea);
        }
        return area;
    }

public:
    int maxArea(int M[100][100], int n, int m) {
        //compute area for first row
        int area = largestRectangleArea(M[0], m);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < m; j++) {
                //row update: by adding previous row's value
                if (M[i][j] != 0)
                    M[i][j] = M[i][j] + M[i - 1][j];
                else
                    M[i][j] = 0;
            }
            //entire row is updated now
            area = max(area, largestRectangleArea(M[i], m));
        }
        return area;
    }
};

//N stack in an array; TC: O(1), SC: O(s+n)
class NStack {
    int *arr;
    int *top;
    int *next;

    int n, s, freeSpot;
public:
    // Initialize your data structure.
    NStack(int N, int S) {
        n = N;
        s = S;
        arr = new int[s];
        top = new int[n];
        next = new int[s];

        //top initialize
        for (int i = 0; i < n; i++) {
            top[i] = -1;
        }
        // next initialise
        for (int i = 0; i < s; i++) {
            next[i] = i + 1;
        }
        //update last index vlaue to -1
        next[s - 1] = -1;
        freeSpot = 0;
    }

    // Pushes 'X' into the Mth stack. Returns true if it gets pushed into the stack, and false otherwise.
    bool push(int x, int m) {
        //check for overflow
        if (freeSpot == -1) { return false; }
        //find index
        int index = freeSpot;
        //update free spot
        freeSpot = next[index];
        //insert element into array
        arr[index] = x;
        //update next;
        next[index] = top[m - 1];
        //update top
        top[m - 1] = index;
        return true;
    }

    // Pops top element from Mth Stack. Returns -1 if the stack is empty, otherwise returns the popped element.
    int pop(int m) {
        //check empty/ underflow condition
        if (top[m - 1] == -1) { return -1; }
        //reverse way of push
        int index = top[m - 1];
        top[m - 1] = next[index];
        next[index] = freeSpot;
        freeSpot = index;
        return arr[index];
    }
};

//getMin()
//approach 1; TC: O(1); SC: O(N);
// approach 2; TC, SP: O(1)
class SpecialStack {
    stack<int> s;
    int mini;
public:

    void push(int data) {
        // 1st element
        if (s.empty()) {
            s.push(data);
            mini = data;
        } else {
            // new mini
            if (data < mini) {
                int val = 2 * data - mini;
                s.push(val);
                mini = data;
            } else {
                s.push(data);
            }
        }
    }

    int pop() {
        if (s.empty()) { return -1; }
        int curr = s.top();
        s.pop();
        if (curr > mini) {
            return curr;
        } else {
            int prevMini = mini;
            int val = 2 * mini - curr;
            mini = val;
            return prevMini;
        }
    }

    int top() {
        if (s.empty()) { return -1; }
        int curr = s.top();
        if (curr < mini) {
            return mini;
        } else {
            return curr;
        }
    }

    int getMin() {
        if (s.empty()) { return -1; }

        return mini;
    }
};

int main() {
//    Stack st(1);
//    st.push(10);
//    st.push(20);
//    cout << st.peek() << endl;
//    st.pop();
//    cout << st.peek() << endl;
//    st.pop();
//    cout << st.peek() << endl;
//    cout << st.isEmpty();
    cout << reverseString("vinayak");
    return 0;
}