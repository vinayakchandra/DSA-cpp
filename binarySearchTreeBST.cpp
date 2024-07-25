#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *insertIntoBST(Node *root, int d) {
    if (root == NULL) {
        root = new Node(d);
        return root;
    }
    //d > root; right
    if (d > root->data) {
        root->right = insertIntoBST(root->right, d);
    }
    // d < root; left
    if (d < root->data) {
        root->left = insertIntoBST(root->left, d);
    }
    return root;
}

void takeInput(Node *&root) {
    int data;
    cin >> data;

    while (data != -1) {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

//Traversals
//lot
void levelOrderTraversal(Node *root) {
    queue<Node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();
        if (temp == NULL) {
            //purana level complete traverse ho chuka hai
            cout << endl;
            if (!q.empty()) {
                //queue still has child Nodes
                q.push(NULL);
            }
        } else {
            cout << temp->data << " ";
            if (temp->left != NULL) {
                q.push(temp->left);
            }
            if (temp->right != NULL) {
                q.push(temp->right);
            }
        }
    }
}

//LNR
void inorder(Node *root) {
    //base case
    if (root == NULL) {
        return;
    }
    inorder(root->left); // L
    cout << root->data << " "; // N
    inorder(root->right); // R
}

//NLR
void PreOrder(Node *root) {
    //base case
    if (root == NULL) {
        return;
    }
    cout << root->data << " "; // N
    PreOrder(root->left); // L
    PreOrder(root->right); // R
}

//LRN
void PostOrder(Node *root) {
    //base case
    if (root == NULL) {
        return;
    }
    PostOrder(root->left); // L
    PostOrder(root->right); // R
    cout << root->data << " "; // N
}

//search
//TC: O(nLogN);
bool searchInBST(Node *root, int x) {
    if (root == NULL) { return false; }
    //found
    if (x == root->data) {
        return true;
    }
    // X > data; right
    if (x > root->data) {
        return searchInBST(root->right, x);
    } else {
        return searchInBST(root->left, x);
    }
}

//SP:O(1)
bool searchInBST2(Node *root, int x) {
    Node *temp = root;
    while (temp != NULL) {
        if (temp->data == x) {
            return true;
        }
        if (x < temp->data) { temp = temp->left; }
        else { temp = temp->right; }
    }
    return false;
}

//min value
Node *minVal(Node *root) {
    Node *temp = root;
    while (temp->left != NULL) {
        temp = temp->left;
    }
    return temp;
}

//max value
Node *maxVal(Node *root) {
    Node *temp = root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

//deletion, TC,SP: O(N)
Node *deletefromBST(Node *root, int val) {
    //base case
    if (root == NULL) { return NULL; }
    //val found
    if (root->data == val) {
        // 0 child
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }

        // 1 child
        //left child
        if (root->left != NULL && root->right == NULL) {
            Node *temp = root->left; //next node pe point kara diya
            delete root;
            return temp;
        }
        //right child
        if (root->right != NULL && root->left == NULL) {
            Node *temp = root->right;
            delete root;
            return temp;
        }

        // 2 child
        if (root->left != NULL && root->right != NULL) {
            int mini = minVal(root->right)->data;
            root->data = mini;//changes data to mini
            root->right = deletefromBST(root->right, mini);//recursion
            return root;
        }
    }
    //left
    if (val < root->data) {
        root->left = deletefromBST(root->left, val);
        return root;
    } else {//right
        root->right = deletefromBST(root->right, val);
        return root;
    }
}

//is bst
bool isBST(Node *root, int min, int max) {
    if (root == NULL) { return true; }

    if (root->data >= min && root->data <= max) {
        bool left = isBST(root->left, min, root->data);// range = [min, data]
        bool right = isBST(root->left, root->data, max);//range = [data, max]
        return left && right;
    } else { return false; }
}

bool validateBST(Node *root) {
    return isBST(root, INT_MIN, INT_MAX);
}

// k smallest element
int kthSmallestSolve(Node *root, int &i, int k) {
    //base case
    if (root == NULL) { return -1; }
    // L
    int left = kthSmallestSolve(root->left, i, k);
    if (left != -1) {
        return left;
    }
    //N
    i++;
    if (i == k) { return root->data; }
    //R
    return kthSmallestSolve(root->right, i, k);
}

int kthSmallest(Node *root, int k) {
    int i = 0;
    int ans = kthSmallestSolve(root, i, k);
    return ans;
}

//SP: O(1)
pair<int, int> predecessorSuccessor(Node *root, int key) {
    //find key
    Node *temp = root;
    int pred = -1;
    int succ = -1;
    while (temp->data != key) {
        //left
        if (temp->data > key) {
            //left subtree me max element
            succ = temp->data;
            temp = temp->left;
        } else {//right
            //right subtree me min element
            pred = temp->data;
            temp = temp->right;
        }
    }
    //data = key
    //pred and succ
    //pred
    Node *leftTree = temp->left;
    while (leftTree != NULL) {
        pred = leftTree->data;
        leftTree = leftTree->right;
    }
    //succ
    Node *rightTree = temp->right;
    while (rightTree != NULL) {
        succ = rightTree->data;
        rightTree = rightTree->left;
    }
    pair<int, int> ans = make_pair(pred, succ);
    return ans;
}

//lowest common ancestor
Node *LCAinaBST(Node *root, Node *P, Node *Q) {
    while (root != NULL) {
        if (root->data < P->data && root->data < Q->data) {
            root = root->right;//data < Q,P; right ki taraf aao
        } else if (root->data > P->data && root->data > Q->data) {
            root = root->left;//data>Q,P; left ki taraf aao
        } else {//P<data<Q
            return root;
        }
    }
}

// two sum; O(N)g
void inorderVec(Node *root, vector<int> &in) {
    if (root == NULL) { return; }
    inorderVec(root->left, in);//L
    in.push_back(root->data);//N
    inorderVec(root->right, in);//R
}

bool twoSumInBST(Node *root, int target) {
    vector<int> inorderVal;
    inorderVec(root, inorderVal);
    //2 pointer
    int i = 0, j = inorderVal.size() - 1;
    while (i < j) {
        int sum = inorderVal[i] + inorderVal[j];
        if (sum == target) { return true; }
        else if (sum > target) { j--; }//j kam kardo
        else if (sum < target) { i++; }//i aage
    }
    return false;//not found
}

//making LL from BST
Node *flatten(Node *root) {
    vector<int> inorderVal;
    inorderVec(root, inorderVal);

    Node *newRoot = new Node(inorderVal[0]);
    Node *curr = newRoot;

    //step2
    for (int i = 1; i < inorderVal.size(); ++i) {
        Node *temp = new Node(inorderVal[i]);//new node
        curr->left = NULL;//left = null
        curr->right = temp;//right=next node
        curr = temp;//next
    }

    //step3
    curr->left = NULL;//last node left= null
    curr->right = NULL;//last node right = null

    return newRoot;
}

//BST, in which the height of two subtrees of every node differs no more than 1.
//[left-right]<=1
Node *inorderToBST(int s, int e, vector<int> &inorderVal) {
    //base
    if (s > e) return NULL;
    int mid = (s + e) / 2;
    Node *root = new Node(inorderVal[mid]);//new node for mid
    root->left = inorderToBST(s, mid - 1, inorderVal);
    root->right = inorderToBST(mid + 1, e, inorderVal);
    return root;
}

Node *balancedBst(Node *root) {
    vector<int> inorderVal;
    inorderVec(root, inorderVal);

    return inorderToBST(0, inorderVal.size() - 1, inorderVal);
}

//BST from preorder
Node *preorderToBSTSolve(vector<int> &preorder, int mini, int maxi, int &i) {
    if (i >= preorder.size()) return NULL;
    if (preorder[i] < mini || preorder[i] > maxi) return NULL;//out of range

    Node *root = new Node(preorder[i++]);
    root->left = preorderToBSTSolve(preorder, mini, root->data, i);//[min,data]
    root->right = preorderToBSTSolve(preorder, root->data, maxi, i);//[data,max]
    return root;
}

Node *preorderToBST(vector<int> &preorder) {
    int mini = INT_MIN;
    int maxi = INT_MAX;
    int i = 0;
    return preorderToBSTSolve(preorder, mini, maxi, i);
}

//approach 1
vector<int> mergeArrays(vector<int> &a, vector<int> &b) {
    vector<int> ans(a.size() + b.size());
    int i = 0, j = 0;
    int k = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            ans[k++] = a[i];
            i++;
        } else {
            ans[k++] = b[j];
            j++;
        }
    }

    while (i < a.size()) {
        ans[k++] = a[i];
        i++;
    }
    while (j < b.size()) {
        ans[k++] = b[j];
        j++;
    }

    return ans;
}

//🔴🔴🔴🔴🔴 approach 2 🔴🔴🔴🔴🔴
void convertIntoSortedDLL(Node *root, Node *head) {
    //base case
    if (root == NULL) return;

    convertIntoSortedDLL(root->right, head);//convert right

    root->right = head;//right = head
    if (head != NULL)
        head->left = root;//headL = root
    head = root;//head =root

    convertIntoSortedDLL(root->left, head);//convert left
}

void *mergeLL(Node *&head1, Node *&head2) {
    Node *head = NULL;
    Node *tail = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {//1<2
            if (head == NULL) {//insert at head
                head = head1;
                tail = head1;
                head1 = head1->right;//next
            } else {//insert at end
                tail->right = head1;
                head1->left = tail;
                tail = head1;
                head1 = head1->right;
            }
        } else {//2>1
            if (head == NULL) {//insert at head
                head = head2;
                tail = head2;
                head2 = head2->right;
            } else {//insert at tail
                tail->right = head2;
                head2->left = tail;
                tail = head2;
                head2 = head2->right;
            }
        }
    }
    while (head1 != NULL) {
        tail->right = head1;
        head1->left = tail;
        tail = head1;
        head1 = head1->right;
    }
    while (head2 != NULL) {
        tail->right = head2;
        head2->left = tail;
        tail = head2;
        head2 = head2->right;
    }
}

int countNodes(Node *head) {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->right;
    }
    return count;
}

Node *sortedLLToBST(Node *&head, int n) {
    //base case
    if (n <= 0 || head == NULL) return NULL;
    //left subtree
    Node *left = sortedLLToBST(head, n / 2);
    Node *root = head;
    root->left = left;
    head = head->right;
    root->right = sortedLLToBST(head, n - n / 2 - 1);
    return root;
}

//🔴🔴🔴🔴
vector<int> mergeBST(Node *root1, Node *root2) {
    /*
    //step1: sore inorder
    vector<int> bst1, bst2;
    inorderVec(root1, bst1);
    inorderVec(root2, bst2);
    //step2: merge both arrays
    vector<int> mergeArray = mergeArrays(bst1, bst2);
    //step3: use merged inorder array to build BST
    int s = 0, e = mergeArray.size() - 1;

    inorderToBST(s, e, mergeArray);
    return mergeArray;
     */

    //SP: O(H)
    //step1: convert to sorted DLL
    //1
    Node *head1 = NULL;
    convertIntoSortedDLL(root1, head1);
    head1->left = NULL;
    //2
    Node *head2 = NULL;
    convertIntoSortedDLL(root2, head2);
    head2->left = NULL;

    //step2: merge sorted LL
    mergeLL(head1, head2);

    //step3: convert sorted LL into bst🔴🔴🔴🔴🔴🔴
    return sortedLLToBST(head1, countNodes(head1));
}

//largest bst; O(N)
// {max, min, isBST, size}
class Info {
public:
    int maxi;
    int mini;
    bool isBST;
    int size;
};

Info largestBSTSolve(Node *root, int &ans) {
    //base
    if (root == NULL) {
        return {INT_MIN, INT_MAX, true, 0};
    }

    Info left = largestBSTSolve(root->left, ans);//left
    Info right = largestBSTSolve(root->right, ans);//right

    Info currNode;
    currNode.size = left.size + right.size + 1;//size=left + right + 1
    currNode.maxi = max(root->data, right.maxi);//max
    currNode.mini = min(root->data, left.mini);//min

    if (left.isBST && right.isBST && (root->data > left.maxi && root->data < right.mini)) {
        currNode.isBST = true;
    } else {
        currNode.isBST = false;
    }
    //answer update
    if (currNode.isBST) {
        ans = max(ans, currNode.size);//max(before, new)
    }
    return currNode;
}

int largestBST(Node *root) {
    int maxSize = 0;
    Info temp = largestBSTSolve(root, maxSize);
    return maxSize;
}

int main() {
    Node *root = NULL;
    cout << "enter Data to create BST" << endl;
    takeInput(root);
    cout << "printing" << endl;
    levelOrderTraversal(root);
//    cout << minVal(root)->data << endl;
//    cout << maxVal(root)->data << endl;
    cout << "after" << endl;
//    root = deletefromBST(root, 50);
//    levelOrderTraversal(root);
    cout << predecessorSuccessor(root, 15).first << endl;
    cout << predecessorSuccessor(root, 15).second << endl;
    //50 20 30 70 110 55 -1
    return 0;
}