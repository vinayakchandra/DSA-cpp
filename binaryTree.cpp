#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;

class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int d) {
        this->data = d;
        this->right = NULL;
        this->left = NULL;
    }
};

//making BT; using recursion
Node *buildTree(Node *root) {
    cout << "Enter data: " << endl;
    int data;
    cin >> data;
    root = new Node(data);

    if (data == -1) {
        return NULL;
    }
    cout << "Enter data for inserting in left: " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter data for inserting in right: " << data << endl;
    root->right = buildTree(root->right);
    return root;
}

//making BT; not using recursion
void buildFromLevelOrder(Node *&root) {
    queue<Node *> q;
    cout << "Enter data for root" << endl;
    int data;
    cin >> data;
    root = new Node(data);
    q.push(root);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();

        //left
        cout << "Enter left Node for: " << temp->data << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1) {
            temp->left = new Node(leftData);
        }
        //right
        cout << "Enter right Node for: " << temp->data << endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1) {
            temp->right = new Node(rightData);
        }
    }
}

//Traversals
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

//LNR; TC: O(N); SP: O(1)
void MorrisTraversal(Node *root) {
    Node *current, *pre;
    if (root == NULL)
        return;
    current = root;//set cursor to root
    while (current != NULL) {
        if (current->left == NULL) {//left=empty
            //print N
            cout << current->data << " ";
            current = current->right;//go right
        } else {//right==null
            /* Find the inorder predecessor of current */
            //ek baar left jao, then right jaate jao
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }
            /* Make current as the right child of its
               inorder predecessor */
            if (pre->right == NULL) {
                pre->right = current;//temporary link
                current = current->left;//change curr
            }
                /* Revert the changes made in the 'if' part to
                   restore the original tree i.e., fix the right
                   child of predecessor */
            else {
                pre->right = NULL;//temporary link ko hatake, null kar diya
                cout << current->data << " ";//print
                current = current->right;//curr to right
            } /* End of if condition pre->right == NULL */
        }
    }
}

int height(Node *root) {
    if (root == NULL) {
        return 0;
    }
    int left = height(root->left);
    int right = height(root->right);
    int ans = max(left, right) + 1;
    return ans;
}

pair<int, int> diameterFast(Node *root) {
    // pair(diameter, height)
    if (root == NULL) {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = diameterFast(root->left);
    pair<int, int> right = diameterFast(root->right);

    int op1 = left.first;//d1
    int op2 = right.first;//d2
    int op3 = left.second + right.second + 1;//h1 + h2 + 1

    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3));
    ans.second = max(left.second, right.second) + 1;

    return ans;
}

int diameter(Node *root) {
    return diameterFast(root).first;
}

//TC: O(n2)
bool isBalanced(Node *root) {
    //base
    if (root == NULL) {
        return true;
    }
    bool left = isBalanced(root);
    bool right = isBalanced(root);
    bool diff = abs(height(root->left) - height(root->right)) <= 1;

    if (left && right && diff) {
        return true;
    } else {
        return false;
    }
}

pair<bool, int> isBalancedFast(Node *root) {
    //base
    if (root == NULL) {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }
    pair<int, int> left = isBalancedFast(root->left);
    pair<int, int> right = isBalancedFast(root->right);
    bool leftAns = left.first;
    bool rightAns = right.first;
    bool diff = abs(left.second - right.second) <= 1;

    pair<bool, int> ans;
    ans.second = max(left.second, right.second) + 1;
    if (leftAns && rightAns && diff) {
        ans.first = true;
    } else {
        ans.first = false;
    }
    return ans;
}

//TC: O(n)
bool isBalanced2(Node *root) {
    return isBalancedFast(root).first;
}

bool isIdentical(Node *r1, Node *r2) {
    //base
    if (r1 == NULL && r2 == NULL) { return true; }
    if (r1 == NULL && r2 != NULL) { return false; }
    if (r1 != NULL && r2 == NULL) { return false; }

    bool left = isIdentical(r1->left, r2->left);
    bool right = isIdentical(r1->right, r2->right);
    bool value = r1->data == r2->data;
    if (left && right && value) { return true; }
    else { return false; }
}

// top + left + right/
pair<bool, int> isSumTreeFast(Node *root) {
    //base
    if (root == NULL) {
        pair<bool, int> p = make_pair(true, 0);
        return p;
    }

    if (root->left == NULL && root->right == NULL) {
        pair<bool, int> p = make_pair(true, root->data);
        return p;
    }

    pair<bool, int> leftAns = isSumTreeFast(root->left);
    pair<bool, int> rightAns = isSumTreeFast(root->right);

    bool left = leftAns.first;//t/f
    bool right = rightAns.first; // t/f
    //data = left + right
    bool condition = root->data == leftAns.second + rightAns.second;

    pair<bool, int> ans;
    if (left && right && condition) {
        ans.first = true;
        // top + left + right
        ans.second = root->data + leftAns.second + rightAns.second;
    } else {
        ans.first = false;
    }
    return ans;
}

bool isSumTree(Node *root) {
    return isSumTreeFast(root).first;
}

//TC: O(N), SP: O(N)
vector<int> zigZagTraversal(Node *root) {
    vector<int> result;
    if (root == NULL) {
        return result;
    }
    queue<Node *> q;
    q.push(root);
    bool leftToRight = true;//checking dir

    while (!q.empty()) {
        int size = q.size();
        vector<int> temp(size);

        for (int i = 0; i < size; ++i) {
            Node *frontNode = q.front();
            q.pop();
            //normal insert or reverse insert
            int index = leftToRight ? i : size - 1 - i;
            temp[index] = frontNode->data;

            if (frontNode->left != NULL) {
                q.push(frontNode->left);
            }
            if (frontNode->right != NULL) {
                q.push(frontNode->right);
            }
        }
        //dir change
        leftToRight = !leftToRight;
        for (int i: temp) {
            result.push_back(i);
        }
    }
    return result;
}

//outer nodes
void traverseLeft(Node *root, vector<int> &ans) {
    //exclusive of leaf node
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return;
    }
    ans.push_back(root->data);

    if (root->left != NULL) {
        traverseLeft(root->left, ans);
    } else {
        traverseLeft(root->right, ans);
    }
}

void traverseRight(Node *root, vector<int> &ans) {
    //base case, leaf
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return;
    }
    if (root->right) { traverseRight(root->right, ans); }
    else { traverseRight(root->left, ans); }
    //wapis aa gaye
    ans.push_back(root->data);
}

void traverseLeaf(Node *root, vector<int> &ans) {
    if (root == NULL) { return; }
    if (root->left == NULL && root->right == NULL) {
        ans.push_back(root->data);
    }
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
}

vector<int> boundary(Node *root) {
    vector<int> ans;
    if (root == NULL) { return ans; }
    ans.push_back(root->data);//1st node
    //left part
    traverseLeft(root->left, ans);

    //leaf part
    //left subtree
    traverseLeaf(root->left, ans);
    //right subtree
    traverseLeaf(root->right, ans);

    //right part
    traverseRight(root->right, ans);
    return ans;
}

//vertical order traversal
vector<int> verticalOrder(Node *root) {
    //horizontal dist; level, list of nodes
    map<int, map<int, vector<int> > > nodes;
    queue<pair<Node *, pair<int, int> > > q;
    vector<int> ans;
    // <0> -> 1,5,6
    // <-1> -> 2
    // <1> -> 4

    //empty
    if (root == NULL) {
        return ans;
    }
    // node; dist, level
    q.push(make_pair(root, make_pair(0, 0)));//0dist, 0level

    while (!q.empty()) {
        pair<Node *, pair<int, int> > temp = q.front();
        q.pop();

        Node *frontNode = temp.first;//pop
        int hd = temp.second.first; // horizontal D
        int level = temp.second.second; // level
        nodes[hd][level].push_back(frontNode->data); //storing in vector
        //left
        if (frontNode->left != NULL) {
            q.push(make_pair(frontNode->left, make_pair(hd - 1, level + 1)));
        }
        //right
        if (frontNode->right) {
            q.push(make_pair(frontNode->right, make_pair(hd + 1, level + 1)));
        }
    }
    //printing/ putting in vector
    for (auto i: nodes) {
        //i = pair<int, map>; map<int, vector<int> >
        // we want vector
        for (auto j: i.second) {
            for (auto k: j.second) {
                ans.push_back(k);
            }
        }
    }
    return ans;
}

//top view ot BT; map
vector<int> topView(Node *root) {
    vector<int> ans;
    if (root == NULL) { return ans; }
    //HD, topNode
    map<int, int> topNode;
    queue<pair<Node *, int> > q;
    q.push(make_pair(root, 0));

    while (!q.empty()) {
        pair<Node *, int> temp = q.front();
        q.pop();

        Node *frontNode = temp.first;//node
        int hd = temp.second; // horizontal D

        //if one value exist-> do nothing
        if (topNode.find(hd) == topNode.end()) {
            //entry nahi milegi/ no map = topNode.end()
            topNode[hd] = frontNode->data;
        }

        if (frontNode->left) {
            q.push(make_pair(frontNode->left, hd - 1));
        }
        if (frontNode->right) {
            q.push(make_pair(frontNode->right, hd + 1));
        }
    }
    //printing
    for (auto i: topNode) {
        ans.push_back(i.second);//node data
    }
    return ans;
}

vector<int> bottomView(Node *root) {
    vector<int> ans;
    if (root == NULL) { return ans; }
    //HD, topNode
    map<int, int> topNode;
    queue<pair<Node *, int> > q;
    q.push(make_pair(root, 0));
    while (!q.empty()) {
        pair<Node *, int> temp = q.front();
        q.pop();

        Node *frontNode = temp.first;//node
        int hd = temp.second; // horizontal D

        topNode[hd] = frontNode->data; // seedha daal do/ replace

        if (frontNode->left) {
            q.push(make_pair(frontNode->left, hd - 1));
        }
        if (frontNode->right) {
            q.push(make_pair(frontNode->right, hd + 1));
        }
    }
    for (auto i: topNode) {
        ans.push_back(i.second);//node data
    }
    return ans;
}

//L->R
void rightViewSolve(Node *root, vector<int> &ans, int level) {
    if (root == NULL) { return; }
    //we entered into new level
    if (level == ans.size()) {
        ans.push_back(root->data);
    }
    //right
    rightViewSolve(root->right, ans, level + 1);
    //left
    rightViewSolve(root->left, ans, level + 1);
}

vector<int> rightView(Node *root) {
    vector<int> ans;
    rightViewSolve(root, ans, 0);
    return ans;
}

//R->L
void leftViewSolve(Node *root, vector<int> &ans, int level) {
    if (root == NULL) { return; }
    //we entered into new level
    if (level == ans.size()) {
        ans.push_back(root->data);
    }
    //left
    rightViewSolve(root->left, ans, level + 1);
    //right
    rightViewSolve(root->right, ans, level + 1);

}

vector<int> leftView(Node *root) {
    vector<int> ans;
    rightViewSolve(root, ans, 0);
    return ans;
}

void sumOfLongRootToLeafPathSolve(Node *root, int sum, int &maxSum, int len, int &maxLen) {
    if (root == NULL) {
        if (len > maxLen) {//new max len
            maxLen = len;
            maxSum = sum;
        } else if (len == maxLen) {//same len
            maxSum = max(sum, maxSum);//new max sum
        }
        return;
    }
    sum = sum + root->data;
    //left
    sumOfLongRootToLeafPathSolve(root->left, sum, maxSum, len + 1, maxLen);
    //right
    sumOfLongRootToLeafPathSolve(root->right, sum, maxSum, len + 1, maxLen);
}

int sumOfLongRootToLeafPath(Node *root) {
    if (root == NULL) { return 0; }
    int len = 0;
    int maxLen = 0;
    int sum = 0;
    int maxSum = INT_MIN;
    sumOfLongRootToLeafPathSolve(root, sum, maxSum, len, maxLen);
    return maxSum;
}

//lowest common ancestor; TC,SP: O(N)
Node *lca(Node *root, int n1, int n2) {
    if (root == NULL) {
        return NULL;
    }
    //node has left & right
    if (root->data == n1 || root->data == n2) {
        return root;
    }
    Node *leftAns = lca(root->left, n1, n2);
    Node *rightAns = lca(root->right, n1, n2);
    //both
    if (leftAns != NULL && rightAns != NULL) {
        return root;
    } else if (leftAns != NULL && rightAns == NULL) {
        //single left
        return leftAns;
    } else if (leftAns == NULL && rightAns != NULL) {
        //single right
        return rightAns;
    } else {
        //null
        return NULL;
    }
}

//sum equal to k
void sumKSolve(Node *root, int k, int &count, vector<int> path) {
    if (root == NULL) {
        return;
    }
    path.push_back(root->data);
    //left
    sumKSolve(root->left, k, count, path);
    //right
    sumKSolve(root->right, k, count, path);
    //check for k sum
    int sum = 0;
    for (int i = path.size() - 1; i >= 0; i--) {
        sum += path[i];
        if (sum == k) {
            count++;
        }
        path.pop_back();
    }
}

int sumK(Node *root, int k) {
    vector<int> path;
    int count = 0;
    sumKSolve(root, k, count, path);
    return count;
}

//kth ancestor; TC,SP: O(N)
Node *kthAncestorSolve(Node *root, int &k, int node) {
    //base case
    if (root == NULL) { return NULL; }
    if (root->data == node) { return root; }

    Node *leftAns = kthAncestorSolve(root->left, k, node);
    Node *rightAns = kthAncestorSolve(root->right, k, node);
    //wapis
    if (leftAns != NULL && rightAns == NULL) {
        k--;
        if (k <= 0) {
            k = INT_MAX;//answer lock
            return root;
        }
        return leftAns;
    }
    if (leftAns == NULL && rightAns != NULL) {
        k--;
        if (k <= 0) {
            k = INT_MAX;//answer lock
            return root;
        }
        return rightAns;
    }
    return NULL; // else
}


int kthAncestor(Node *root, int k, int node) {
    Node *ans = kthAncestorSolve(root, k, node);
    //1st node = node->data
    if (ans == NULL || ans->data == node) { return -1; }
    else { return ans->data; }
}

//max sum of none adjacent nodes;
pair<int, int> getMaxSumSolve(Node *root) {
    //base case
    if (root == NULL) {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }
    pair<int, int> left = getMaxSumSolve(root->left);
    pair<int, int> right = getMaxSumSolve(root->right);
    pair<int, int> res;

    //include
    res.first = root->data + left.second + right.second;
    //exclude
    res.second = max(left.first, left.second) + max(right.first, right.second);;
    return res;
}

int getMaxSum(Node *root) {
    pair<int, int> ans = getMaxSumSolve(root);
    return max(ans.first, ans.second);
}

//build a BT from inorder(LNR) & preorder(NLR); output->postorder(LRN)
//TC: O(n)
//🔴🔴🔴🔴🔴SUM PROBLEM IN BUILDING🔴🔴🔴🔴🔴🔴🔴🔴
int findPosition(int in[], int element, int n) {
    for (int i = 0; i < n; i++) {
        if (in[i] == element) {
            return i;//index
        }
    }
    return -1;
}

//TP: O(nLogN)
void createMapping(int in[], map<int, int> &nodeToIndex, int n) {
    for (int i = 0; i < n; i++) {
        nodeToIndex[in[i]] = i;
    }
}

Node *buildTreeSolve(int in[], int pre[], int &index, int inorderStart, int inorderEnd, int n,
                     map<int, int> &nodeToIndex) {
    //base
    if (index >= n || inorderStart > inorderEnd) {
        return NULL;
    }
    //creat nodes
    int element = pre[index++];//preOrder gives nodes
    Node *root = new Node(element);
    //inorder ke andar position dudh ke lao
//    int position = findPosition(in, element, n);
    int position = nodeToIndex[element];

    //recursive call
    root->left = buildTreeSolve(in, pre, index, inorderStart, position - 1, n, nodeToIndex);
    root->right = buildTreeSolve(in, pre, index, position + 1, inorderEnd, n, nodeToIndex);

    return root;
}

Node *buildTree(int in[], int pre[], int n) {
    int preOrderIndex = 0;
    map<int, int> nodeToIndex;
    //create nodes to index mapping
    createMapping(in, nodeToIndex, n);
    Node *ans = buildTreeSolve(in, pre, preOrderIndex, 0, n - 1, n, nodeToIndex);
    return ans;
}

//inorder(LNR); postorder(LRN)
//🔴🔴🔴🔴🔴SUM PROBLEM IN BUILDING🔴🔴🔴🔴🔴🔴🔴🔴
void createMapping2(int in[], map<int, int> &nodeToindex, int n) {
    for (int i = 0; i < n; i++) {
        nodeToindex[in[i]] = i;
    }
}

Node *solve2(int in[], int post[], int &index, int inorderStart, int inorderEnd, int n, map<int, int> &nodeToIndex) {
    // base
    if (index < 0 || inorderStart > inorderEnd) {
        return NULL;
    }
    //create node
    int element = post[index--];
    Node *root = new Node(element);

    //find
    int position = nodeToIndex[element];
    //recursive call
    //right subtree first
    root->right = solve2(in, post, index, position + 1, inorderEnd, n, nodeToIndex);
    root->left = solve2(in, post, index, inorderStart, position - 1, n, nodeToIndex);
    return root;
}

Node *buildTree2(int in[], int post[], int n) {
    int postOrderIndex = n - 1;
    map<int, int> nodeToIndex;
    //create nodes to index mapping
    createMapping2(in, nodeToIndex, n);
    Node *ans = solve2(in, post, postOrderIndex, 0, n - 1, n, nodeToIndex);
    return ans;
}

//min time to burn out a tree; TC,SP:O(N)
Node *createParentMapping(Node *root, int target, map<Node *, Node *> &nodeToParent) {
    Node *res = NULL;
    queue<Node *> q;
    q.push(root);
    nodeToParent[root] = NULL;//root node has no parent

    //level order traversal
    while (!q.empty()) {
        Node *front = q.front();
        q.pop();
        if (front->data == target) {
            //target node found
            res = front;
        }
        if (front->left) {//not null
            nodeToParent[front->left] = front;//child, parent
            q.push(front->left);
        }
        if (front->right) {//not null
            nodeToParent[front->right] = front;//child, parent
            q.push(front->right);
        }
    }
    return res;//target node
}

int burnTree(Node *root, map<Node *, Node *> &nodeToParent) {
    map<Node *, bool> visited;//check visited
    queue<Node *> q;
    q.push(root);
    visited[root] = true;//visited root node
    int ans = 0;

    while (!q.empty()) {
        int size = q.size();
        bool flag = 0;//to increase time

        for (int i = 0; i < size; i++) {
            //process neighboring nodes
            Node *front = q.front();
            q.pop();
            //left is not null and not visited
            if (front->left && !visited[front->left]) {
                flag = 1;
                q.push(front->left);
                visited[front->left] = true;//visited the node
            }
            //right is not null and not visited
            if (front->right && !visited[front->right]) {
                flag = 1;
                q.push(front->right);
                visited[front->right] = true;
            }
            //parent is not null and parent is not visited
            if (nodeToParent[front] && !visited[nodeToParent[front]]) {
                flag = 1;
                q.push(nodeToParent[front]);
                visited[nodeToParent[front]] = true;
            }
        }
        if (flag == 1) { ans++; }
    }
    return ans;
}

int minTime(Node *root, int target) {
    //step1: create nodeToParent mapping
    map<Node *, Node *> nodeToParent;//current node, parent
    //step2: find target node
    Node *targetNode = createParentMapping(root, target, nodeToParent);
    //step3: burn the tree in min time
    int ans = burnTree(targetNode, nodeToParent);
    return ans;
}

//preorder-NLR; TC: O(N) SP:O(1)-> Morris Traversal
void flatten(Node *root) {
    Node *current = root;
    while (current != NULL) {
        if (current->left != NULL) {
            //predecessor
            //ek baar left jao, then right jaate jao
            Node *pred = current->left;//point karado
            while (pred->right != NULL) {
                pred = pred->right;//right jaate jao
            }
            pred->right = current->right;
            current->right = current->left;
            //left part NULL
            current->left = NULL;
        }
        current = current->right;
    }
}

int main() {
    Node *root = nullptr;
    //1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    //creating a tree
    root = buildTree(root);
    levelOrderTraversal(root);
    cout << "order traversal" << endl;
    inorder(root);
    return 0;
}
