#include<iostream>
#include <vector>

using namespace std;


void reverseArray(int arr[], int size) {
    int start = 0;
    int end = size;
    // swapping right to left
    while (start <= end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
    //printing the arr
    for (int i = 0; i < size; i++) {
        cout << arr[i];
    }
}

void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    int arr[m + n];
    nums1.empty();
}

int getArrLength(char arr[]) {
    int count = 0;
    for (int i = 0; arr[i] != '\0'; i++) {
        count++;
    }
    return count;
}

char toLowerCase(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch;
    } else {
        char temp = ch - 'A' + 'a';
        return temp;
    }
}

bool checkPalindrome(string s) {
    // Write your code here.
    int start = 0;
    int end = s.size() - 1;
    int c;
    while (start <= end) {
        if (toLowerCase(s[start]) != toLowerCase(s[end])) {
            return 0;
        } else {
            start++;
            end--;
        }
    }
    return 1;
}

char getMaxOccChar(string s) {
    int arr[26] = {0};
    //letter wali position me +1 ho jayega
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        int number = 0;
        number = ch - 'a';
        arr[number]++;
    }

    // find maximum occ
    int maxi = -1, ans = 0;
    for (int i = 0; i < 26; i++) {
        if (maxi < arr[i]) {
            ans = i;
            maxi = arr[i];
        }
    }
    char finalAns = 'a' + ans;
    return finalAns;
}

string removeOccurrences(string s, string part) {
    while (s.length() != 0 && s.find(part) < s.length()) {
        s.erase(s.find(part), part.length());
    }
    return s;
}

vector<int> wavePrint(vector<vector<int> > arr, int nRows, int mCols) {
    //Write your code here
    vector<int> ans;

    for (int col = 0; col < mCols; col++) {

        if (col & 1) {
            // odd index -> bottom to top

            for (int row = nRows - 1; row >= 0; row--) {
                ans.push_back(arr[row][col]);
            }
        } else {
            // even index -> top to bottom
            for (int row = 0; row < nRows; row++) {
                ans.push_back(arr[row][col]);

            }
        }
    }
    return ans;

}

bool isPrime(int n) {
    if (n == 0 || n == 1) {
        return false;
    }
    if (n == 2) { return true; }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int countPrimes(int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (isPrime(i)) {
            count++;
        }
    }
    return count;
}

//Sieve of Eratothenes’s
int countPrimesOpt(int n) {
    int count = 0;
    vector<bool> prime(n + 1, true); // assuming all are primes
    prime[0] = prime[1] = false; // 0, 1 are not primes

    for (int i = 2; i < n; i++) {
        if (prime[i]) { //if prime is true
            count++;
            //prime ke multiples are not prime
            for (int j = 2 * i; j < n; j = j + i) {
                prime[j] = false;
            }
        }
    }
    return count;//no. of primes before n
}


void updateV(int n) {
    n++;
    cout << n << endl;
}

void updateR(int &n) {
    n++;
    cout << n << endl;
}

// referenceVariable
void referenceVariable() {
    int i = 5;
    int &j = i; // reference Variable
    j++;
    i++;
    cout << j << endl;
    int n = 5;
    updateV(n);
    cout << n << endl;
    updateR(n);
    cout << n << endl;
}

void size() {
    char q = 'q';
    cout << sizeof(q) << endl; // 1
    char *c = &q;
    cout << sizeof(c) << endl;// 8 => size of a pointer
}

//HEAP (dynamic Memory Allocation)
// THIS PROGRAM WILL CRASH THE SYSTEM
void dynamicM() {
    while (true) {
        int *p = new int[10000]; // continuously adding new 4 bytes of memory into heap
        cout << p << endl;
        cout << *p << endl;
//        delete p;  // manually delete
//        delete []p;
    }
}

// 2D array in heap
void dy2d() {

    int row = 3;
    int col = 3;
    // creation of 2d array
    int **arr = new int *[row]; // each element stores a pointer array
    for (int i = 0; i < row; i++) {
        arr[i] = new int[col];
    }

    // taking input of each element
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> arr[i][j];
        }
    }
    //output
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    // RELEASING MEMORY
    for (int i = 0; i < row; i++) {
        delete[] arr[i];
    }
    delete[] arr;
}

// Recursion
void sayNo(int n) {
    string arr[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    if (n == 0) {
        return;
    }
    int digit = n % 10;
    n = n / 10;
    sayNo(n);
    cout << arr[digit] << " ";

}

//recursion
bool isSorted(int arr[], int n) {

    if (n == 0 || n == 1) {
        return true;
    }
    if (arr[0] > arr[1]) {
        return false;
    } else {
        bool ans = isSorted(arr + 1, n - 1);
        return ans;
    }
}

//linear search using rec
bool linearSearchRec(int arr[], int size, int key) {
    if (size == 0) {
        return false;
    }
    if (arr[0] == key) {
        return true;
    }

    linearSearchRec(arr + 1, size - 1, key);
}

// binary search using recursion
bool binarySearchRec(int arr[], int start, int end, int key) {
    if (start >= end) {
        return false;
    }
    int mid = start + (end - start) / 2;

    if (arr[mid] == key) {
        return true;
    }
    if (arr[mid] < key) {
        start = mid + 1;
        binarySearchRec(arr, start, end, key);
    }
    if (arr[mid] > key) {
        end = mid - 1;
        binarySearchRec(arr, start, end, key);
    }
}


int main() {
//    int arr[] = {4, 6, 3, 2, 5, 1, 9, 8, 7};
//    cout << countPrimes(4);
    int arr[] = {1,2,3,4,5};

    cout << binarySearchRec(arr, 0, 4, 3);
}
