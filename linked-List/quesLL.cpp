#include <iostream>
#include <map>

using namespace std;

class Node {
public:
    int data;
    Node *next;
    Node *random;

    //constructor
    Node(int data) {
        this->data = data;
        this->next = nullptr;
    }

    //destructor
    ~Node() {
        int value = this->data;
        //freeing the memory
        if (this->next != nullptr) {
            delete next;
            this->next = nullptr;
        }
        cout << "memory is free for node with data: " << value << endl;
    }
};

void printNode(Node *&head) {
    Node *temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
};

Node *reverseLinkedList(Node *head) {
    // Write your code here
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node *prev = nullptr;
    Node *curr = head;
    Node *forward = nullptr;
    while (curr != nullptr) {
        forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}

void reverseLLRec(Node *&head, Node *curr, Node *prev) {
    //using recursion
    // base case
    if (curr == nullptr) {
        head = prev;
        return;
    }
    Node *forward = head;
    reverseLLRec(head, forward, curr);
    curr->next = prev;
}

Node *reverseLLRec2(Node *&head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    Node *chotaHead = reverseLLRec2(head->next);
    head->next->next = head;
    head->next = nullptr;
    return chotaHead;

}

int getLen(Node *&head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;

    }
    return count;
}

Node *findMiddle(Node *head) {
    // Write your code here
    int len = getLen(head);
    int mid = (len / 2);
    int count = 0;
    Node *temp = head;

    while (count < mid) {
        temp = temp->next;
        count++;
    }
    return temp;
}

Node *getMiddle(Node *head) {
    //fast, slow
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    //2 nodes
    if (head->next->next == nullptr) {
        return head->next;
    }

    Node *slow = head;
    Node *fast = head->next;
    while (fast != nullptr) {
        fast = fast->next;
        //fast 2 baar aage bad gaya
        if (fast != nullptr) {
            fast = fast->next;
        }
        // slow ek baar aage bada
        slow = slow->next;
    }
    return slow;
}

Node *kReverse(Node *head, int k) {
    //base case
    if (head == nullptr) {
        return nullptr;
    }
    //step 1: reverse first k nodes
    Node *next = nullptr;
    Node *curr = head;
    Node *prev = nullptr;
    int count = 0;
    while (curr != nullptr && count < k) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    //step 2: recursion dekh lega
    if (next != nullptr) {
        head->next = kReverse(next, k);
    }

    //step3:return head of reversed list
    return prev;
}

//loop is there or not, map
bool detectLoop(Node *head) {
    if (head == nullptr) {
        return false;
    }
    map<Node *, bool> visited;
    Node *temp = head;
    while (temp != nullptr) {
        //cycle is present
        if (visited[temp] == true) {
            cout << "cycle present on" << temp->data;
            return true;
        }
        visited[temp] = true;
        temp = temp->next;
    }
    return false;

}

//fast/slow
Node *floydDetectLoop(Node *head) {

    if (head == nullptr)
        return nullptr;

    Node *slow = head;
    Node *fast = head;

    while (slow != nullptr && fast != nullptr) {

        fast = fast->next;
        if (fast != nullptr) {
            fast = fast->next;
        }

        slow = slow->next;

        if (slow == fast) {
            return slow;
        }
    }
    return nullptr;
}

Node *getStartingNode(Node *head) {
    if (head == nullptr)
        return nullptr;

    Node *intersection = floydDetectLoop(head);
    if (intersection == nullptr)
        return nullptr;
    Node *slow = head;
    while (slow != intersection) {
        slow = slow->next;
        intersection = intersection->next;
    }
    return slow;
}

Node *removeLoop(Node *head) {
    if (head == nullptr)
        return nullptr;

    Node *startOfLoop = getStartingNode(head);

    if (startOfLoop == nullptr)
        return head;

    Node *temp = startOfLoop;

    while (temp->next != startOfLoop) {
        temp = temp->next;
    }

    temp->next = nullptr;
    return head;
}

//sorted LL
Node *removeDuplicateSorted(Node *head) {
    //empty
    if (head == nullptr) { return nullptr; }

    Node *curr = head;
    while (curr != nullptr) {
        if ((curr->next != nullptr) && curr->data == curr->next->data) {
            Node *next_next = curr->next->next;
            Node *nodeToDelete = curr->next;
            delete nodeToDelete;
            curr->next = next_next;
        } else { curr = curr->next; }
    }
    return head;
}

//unsorted LL
Node *removeDuplicateUnSorted(Node *head) {
    //empty
    if (head == nullptr) { return nullptr; }

    Node *curr = head;

    while (curr != nullptr) {
        Node *temp = curr->next;
        while (temp != nullptr) {
            if (curr->data == temp->data) {

                delete temp;
            }
        }
    }
}

//sort LL of 0,1,2s, data replacement
Node *sortLL(Node *head) {
    int zeroCount = 0;
    int oneCount = 0;
    int twoCount = 0;
    Node *temp = head;
    while (temp != nullptr) {
        if (temp->data == 0) { zeroCount++; }
        else if (temp->data == 1) { oneCount++; }
        else if (temp->data == 2) { twoCount++; }
        temp = temp->next;
    }
    temp = head;
    while (temp != nullptr) {
        if (zeroCount != 0) {
            temp->data = 0;//temp ke data me 0 daaldo
            zeroCount--;
        } else if (oneCount != 0) {
            temp->data = 1;
            oneCount--;
        } else if (twoCount != 0) {
            temp->data = 2;
            twoCount--;
        }
        temp = temp->next;
    }
    return head;
}

//data replacement is not allowed
Node *insertAtTail(Node *&tail, Node *curr) {
    tail->next = curr;
    tail = curr;
}

Node *sortLL2(Node *head) {
    //empty nodes
    Node *zeroHead = new Node(-1);
    Node *zeroTail = zeroHead;
    Node *oneHead = new Node(-1);
    Node *oneTail = oneHead;
    Node *twoHead = new Node(-1);
    Node *twoTail = twoHead;

    Node *curr = head;
    //create individual LL for 0,1,2;
    while (curr != nullptr) {
        int value = curr->data;
        if (value == 0) {
            insertAtTail(zeroTail, curr);
        } else if (value == 1) {
            insertAtTail(oneTail, curr);
        } else if (value == 2) {
            insertAtTail(twoTail, curr);
        }
        curr = curr->next;
    }
    //merge 3 LL
    //1->2
    //1 list not empty
    if (oneHead->next != nullptr) {
        zeroTail->next = oneHead->next;
    }
        // 1 is empty
    else {
        oneTail->next = twoHead->next;
    }
    oneTail->next = twoHead->next; //1->2
    twoTail->next = nullptr;//2->null

    //setup head
    head = zeroHead->next;

    //delete dummy nodes
    delete zeroHead;
    delete oneHead;
    delete twoHead;

    return head;
}

//merge LL
Node *solve(Node *first, Node *second) {
    // only 1 element is present in 1st list
    if (first->next == nullptr) {
        first->next = second;
        return first;
    }

    Node *curr1 = first;
    Node *next1 = curr1->next;
    Node *curr2 = second;
    Node *next2 = curr2->next;
    while (next1 != nullptr && curr2 != nullptr) {
        if (curr1->data <= curr2->data && curr2->data <= next1->data) {
            //add node in b/w the first list
            curr1->next = curr2;
            next2 = curr2->next;
            curr2->next = next1;

            //update pointers
            curr1 = curr2;
            curr2 = next2;
        } else {
            // curr1 and next1 ko agge badhana padega
            // go one step ahead in first list
            curr1 = next1;
            next1 = next1->next;
            // next1 is nullptr
            if (next1 == nullptr) {
                curr1->next = curr2;
                return first;
            }
        }
    }
    return first;
}

Node *mergeLL(Node *first, Node *second) {
    if (first == nullptr) { return second; }
    if (second == nullptr) { return first; }
    if (first->data <= second->data) { return solve(first, second); }
    else { return solve(second, first); }
}

//check palindrome
bool checkPalindrome(vector<int> arr) {
    int start = 0;
    int n = arr.size();
    int end = n - 1;
    while (start <= end) {
        if (arr[start] != arr[end]) { return false; }
        start++;
        end--;
    }
    return true;
}

//space comp=O(n), time comp=O(n)
bool isLLPalindrome(Node *head) {
    //copy data of node to an array
    vector<int> arr;
    Node *temp = head;
    while (temp != nullptr) {
        arr.push_back(temp->data);
        temp = temp->next;
    }
    return checkPalindrome(arr);
}

//space comp=O(1), TC=O(n)
Node *getMid(Node *head) {
    //slow/fast
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow; //middle node
}

Node *reverse(Node *head) {
    Node *curr = head;
    Node *prev = nullptr;
    Node *next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool isLLPalindrome2(Node *head) {
    //single
    if (head->next == nullptr) { return true; }

    //step1-find middle
    Node *middle = getMid(head);
    //step2-reverse list after mid
    Node *temp = middle->next;
    middle->next = reverse(temp);
    //step3-compare
    Node *head1 = head;
    Node *head2 = middle->next;

    while (head2 != nullptr) {
        if (head->data != head2->data) {
            return false;
        }
        head1 = head1->next;
        head2 = head2->next;
    }
    //step4-repeat step 2: jaise aayi thi waise hi bhejdi
    //optional
    temp = middle->next;
    middle->next = reverse(temp);
    return true;
}

//add 2 numbers
void insertAtTail(Node *&head, Node *&tail, int val) {
    Node *temp = new Node(val);
    if (head == nullptr) {
        head = temp;
        tail = temp;
        return;
    } else {
        tail->next = temp;
        tail = temp;
        return;
    }
}

Node *addLL(Node *first, Node *second) {
    int carry = 0;
    Node *ansHead = nullptr;
    Node *ansTail = nullptr;
    while (first != nullptr || second != nullptr || carry != 0) {
        int val1;
        if (first != nullptr) {
            val1 = first->data;
        }
        int val2 = 0;
        if (second != nullptr) {
            val2 = second->data;
        }

        int sum = carry + val1 + val2;
        int digit = sum % 10;
        Node *temp = new Node(digit);
        //create node and add in answer linked list
        insertAtTail(ansHead, ansTail, digit);
        carry = sum / 10;
        if (first != nullptr)
            first = first->next;
        if (second != nullptr)
            second = second->next;
    }
    return ansHead;
}

Node *addTwoLL(Node *first, Node *second) {
    //step1-reverse both LL
    first = reverse(first);
    second = reverse(second);
    //step2-add 2LL
    Node *ans = addLL(first, second);
    //step3-reverse ans
    ans = reverse(ans);
    return ans;
}

//SP: O(n)
Node *randomList(Node *head) {
    //step1: create a clone list
    Node *cloneHead = nullptr;
    Node *cloneTail = nullptr;
    Node *temp = head;

    while (temp != nullptr) {
        insertAtTail(cloneHead, cloneTail, temp->data);
        temp = temp->next;
    }
    //step2: create a map
    unordered_map<Node *, Node *> oldToNewNode;
    Node *originalNode = head;
    Node *cloneNode = cloneHead;
    while (originalNode != nullptr && cloneNode != nullptr) {
        oldToNewNode[originalNode] = originalNode->next;
        cloneNode = cloneNode->next;
    }
    originalNode = head;
    cloneNode = cloneHead;
    while (originalNode != nullptr) {
        cloneNode->random = oldToNewNode[originalNode->random];
        originalNode = originalNode->next;
        cloneNode = cloneHead->next;
    }
    return cloneHead;
}

//SP: O(1)
Node *randomList2(Node *head) {
    //step1: create a clone list
    Node *cloneHead = nullptr;
    Node *cloneTail = nullptr;
    Node *temp = head;
    while (temp != nullptr) {
        insertAtTail(cloneHead, cloneTail, temp->data);
        temp = temp->next;
    }
    //step2: cloneNodes add in b/w original list
    Node *originalNode = head;
    Node *cloneNode = cloneHead;

    while (cloneHead != nullptr && originalNode != nullptr) {
        //original
        Node *next = originalNode->next;
        originalNode->next = cloneNode;
        originalNode->next = cloneNode;
        originalNode = next;
        //clone node
        next = cloneNode->next;
        cloneNode->next = originalNode;
        cloneNode = next;
    }

    //step3: random pointer copy
    temp = head;
    while (temp != nullptr) {
        if (temp->next != nullptr) {
            temp->next->random = temp->random ? temp->random->next : temp->next = temp->random;
        }
        temp = temp->next->next;
    }
    //step4: revert changes done in step2
    originalNode = head;
    cloneNode = cloneHead;
    while (cloneHead != nullptr && originalNode != nullptr) {
        originalNode->next = cloneNode->next;
        originalNode = originalNode->next;

        if (originalNode != nullptr) {
            cloneNode->next = originalNode->next;
        }
        cloneNode = cloneHead->next;
    }
    //step5: return ans
    return cloneHead;
}

//merge sort; TC: O(nLog n)
Node *mergeSort(Node *head) {
    //empty or 1
    if (head == nullptr || head->next == nullptr) {
        return head;//already sorted
    }
    //break LL into 2 halves after finding mid
    Node *mid = findMiddle(head);
    Node *left = head;
    Node *right = mid->next;
    mid->next = nullptr;

    //recursive call
    left = mergeSort(left);
    left = mergeSort(right);
    //merger both left, right
    Node *result = mergeLL(left, right);

    return result;
}

//flatten LL
Node* flattenLinkedList(Node* head)
{
    // Write your code here
}

int main() {
    cout << "hello";
    return 0;
}