#include <iostream>
#include <vector>

using namespace std;

//lec79
class TrieNode {
public:
    char data; //contains only 1 char
    TrieNode *children[26];
    bool isTerminal;

    int childCount;

    TrieNode(char ch) {
        data = ch;
        // starting me all indexes of children is null, terminal = false
        for (int i = 0; i < 26; i++) {
            children[i] = NULL;
        }
        isTerminal = false;
        childCount = 0;
    }
};

class Trie {
public:
    TrieNode *root;
    // root node

    Trie() {
        root = new TrieNode('\0');//starting from null char
    }

    void insertUtil(TrieNode *root, string word) {
        //base case
        if (word.length() == 0) {
            //last node
            root->isTerminal = true;
            return;
        }
        //assumption: word will be in SMALL
        //get index
        int index = word[0] - 'a'; // 'A' = 65
        TrieNode *child;

        //present->node ko index me le jao
        if (root->children[index] != NULL) {
            child = root->children[index];
        } else {
            //absent -> create node
            child = new TrieNode(word[0]);
            root->children[index] = child;
            root->childCount++;//increasing the child count of a node
        }
        //recursion call
        insertUtil(child, word.substr(1));
    }

    // TC: O(N), n=length of word
    void insertWord(string word) {
        insertUtil(root, word);
    }

    bool searchUtil(TrieNode *root, string word) {
        //base case
        if (word.length() == 0) {
            //if found->true
            return root->isTerminal;
        }
        int index = word[0] - 'a';
        TrieNode *child;

        //present
        if (root->children[index] != NULL) {
            child = root->children[index];
        } else {
//            absent
            return false;
        }
        //recursion
        return searchUtil(child, word.substr(1));
    }

    //TC: O(N)
    bool searchWord(string word) {
        return searchUtil(root, word);
    }

    void lcp(string str, string &ans) {
        for (int i = 0; i < str.length(); i++) {
            char ch = str[i];

            if (root->childCount == 1) {
                ans.push_back(ch);
                int index = ch - 'a';
                //aage badh jao
                root = root->children[index];
            } else {
                break;
            }
            //terminal char
            if (root->isTerminal) break;
        }
    }

    void printSuggestions(TrieNode *curr, vector<string> &temp, string prefix) {
        //if curr terminal pe hai->temp me prefix store karlo
        if (curr->isTerminal) {
            temp.push_back(prefix);
        }
        for (char ch = 'a'; ch <= 'z'; ch++) {
            TrieNode *next = curr->children[ch - 'a'];
            //child exist karta hai -> prefix ke andar daaldo
            if (next != NULL) {
                prefix.push_back(ch);
                printSuggestions(next, temp, prefix);
                prefix.pop_back();
            }
        }
    }

    vector<vector<string> > getSuggestions(string str) {
        TrieNode *prev = root;
        vector<vector<string> > output;
        string prefix = "";

        for (int i = 0; i < str.length(); i++) {
            char lastch = str[i];
            prefix.push_back(lastch);
            //check for last char
            TrieNode *curr = prev->children[lastch - 'a'];//curr ko last char pe le jao

            //if not found
            if (curr == NULL) break;
            //if found
            vector<string> temp;
            printSuggestions(curr, temp, prefix);
            output.push_back(temp);
            temp.clear();
            prev = curr; //prev to curr
        }
        return output;
    }
};

//lec80
// longest common prefix
//string length=M, no. of string=n; TC: O(M*N); SP: O(N)
string longestCommonPrefix(vector<string> &arr, int n) {
    string ans = "";
    //for traversing all characters of first string
    for (int i = 0; i < arr[0].length(); i++) {
        char ch = arr[0][i];//taking char of each index of first string
        bool match = true;

        // for comparing ch with rest os the string
        for (int j = 1; j < n; j++) {
            //not match
            // char does not match or checking if ith char even exists or not
            if (arr[j].size() < i || ch != arr[j][i]) {
                match = false;
                break;
            }
        }
        if (match == false) break;
        else {
            ans.push_back(ch);
        }
    }
    return ans;
}

//using trie
// trie banao, if node ka child >1, ans = chars from root this that node
//TC: O(m*N); SP: O(m*n)
string longestCommonPrefixTrie(vector<string> &arr, int n) {
    Trie *t = new Trie();
    //making trie
    for (int i = 0; i < n; i++) {
        t->insertWord(arr[i]);
    }

    string ans = "";
    string first = arr[0];

    t->lcp(first, ans);
    return ans;
}

//lec81
//google search
//SP: O(m*n), TC: O(n*m2)
vector<vector<string> > phoneDirectory(vector<string> &contactList, string &queryStr) {
    // create trie
    Trie *t = new Trie;
    //insert
    for (int i = 0; i < contactList.size(); i++) {
        string str = contactList[i];//each string from vector
        t->insertWord(str);//insert to trie
    }
    //return ans;
    return t->getSuggestions(queryStr);
}

int main() {
    Trie *t = new Trie();
    t->insertWord("ARM");
    t->insertWord("DO");
    t->insertWord("TIME");
//    cout << t->searchWord("TIME") << endl;

    vector<string> arr;
    arr.push_back("he");
    arr.push_back("hes");
    arr.push_back("hsse");
    cout << arr[1].size();
    return 0;
}