#include<iostream>

using namespace std;

void sayNum(int n) {
    string arr[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    if (n == 0) {
        return;
    }
    int digit = n % 10;
    n = n / 10;
    sayNum(n);
    cout << arr[digit] << " ";
}

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

void reverseStr(string &str, int start, int end) {
    cout << str << endl;
    if (start > end) {
        return;
    }
    swap(str[start], str[end]);
    start++;
    end--;
    reverseStr(str, start, end);
}

bool checkPalindrome(string &str, int i, int j) {
    if (i > j) {
        return true;
    }
    if (str[i] != str[j]) {
        return false;
    } else {
        return checkPalindrome(str, i++, j--);
    }
}

int powerof(int base, int power) {
    if (power == 0) {
        return 1;
    }
    if (power == 1) {
        return base;
    }
    //Recursive call
    int ans = powerof(base, power / 2);
    //even
    if (power % 2 == 0) {
        return ans * ans;
    }
        //odd
    else {
        return base * ans * ans;
    }
}

void bubbleSort(int *arr[], int size) {
    // already sorted
    if (size == 0 || size == 1) {
        return;
    }
    // 1 case solved
    for (int i = 0; i < size; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(arr[i], arr[i + 1]);
        }
    }
    bubbleSort(arr, size-1);
}

int main() {
    string name = "vinayak";
    int arr[] = {23, 5, 2, 36, 6};
    bubbleSort(**arr, 5);
    return 0;
}