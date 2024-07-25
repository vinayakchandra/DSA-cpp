#include<iostream>
#include<vector>

using namespace std;

bool isPossibleSol2(std::vector<int> &vector, int cows, int mid);


int binarySearch(int arr[], int size, int key) {
    // gives the index of the key in the given array
    int start = 0; // 0
    int end = size - 1; //size - 1
    int mid = (start + end) / 2;
    // agar hum start aur end dono 2^31-1 dede to unka sum integer ki range se bahar ho jayega
    mid = start + (end - start) / 2;

    while (start <= end) {
        if (arr[mid] == key) {
            return mid;
        }
        if (key > arr[mid]) {
            // go to right wala part
            start = mid + 1;
        } else {
            // left wala part
            end = mid - 1;
        }
        mid = start + (end - start) / 2;
    }
    return -1;
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

int firstOcc(int arr[], int n, int key) {

    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    int ans = -1;
    while (s <= e) {

        if (arr[mid] == key) {
            ans = mid;
            e = mid - 1;
        } else if (key > arr[mid]) {//Right me jao
            s = mid + 1;
        } else if (key < arr[mid]) {//left me jao
            e = mid - 1;
        }

        mid = s + (e - s) / 2;
    }
    return ans;
}

int lastOcc(int arr[], int n, int key) {

    int s = 0, e = n - 1;
    int mid = s + (e - s) / 2;
    int ans = -1;
    while (s <= e) {

        if (arr[mid] == key) {
            ans = mid;
            s = mid + 1;
        } else if (key > arr[mid]) {//Right me jao
            s = mid + 1;
        } else if (key < arr[mid]) {//left me jao
            e = mid - 1;
        }

        mid = s + (e - s) / 2;
    }
    return ans;
}

void firstAndLastPosition(int arr[], int n, int k) {
//    pair<int, int> p;
//    p.first = firstOcc(arr, n, k);
//    p.second = lastOcc(arr, n, k);
    int f = firstOcc(arr, n, k);
    int l = lastOcc(arr, n, k);
    cout << "first: " << f;
    cout << "\nlast: " << l;
}

int noOfOcc(int arr[], int size, int key) {
    int f = firstOcc(arr, size, key);
    int l = lastOcc(arr, size, key);
    return l - f + 1;
}

int peakIndexInMountainArray(vector<int> &arr) {
    int start = 0;
    int end = arr.size() - 1;
    int mid = start + (end - start) / 2;
    while (start < end) {
        if (arr[mid] < arr[mid + 1]) {
            start = mid + 1;
        } else {
            end = mid;
        }
        mid = start + (end - start) / 2;
    }
    return start;
}

int getPivot(int arr[], int n) {
    int start = 0;
    int end = n - 1;
    int mid = start + (end - start) / 2;
    while (start < end) {
        if (arr[mid] > arr[0]) {
            start = mid + 1;
        } else {
            end = mid;
        }
        mid = start + (end - start) / 2;
    }
    return start;
}

int binarySearch2(int arr[], int s, int e, int key) {

    int start = s;
    int end = e;

    int mid = start + (end - start) / 2;

    while (start <= end) {

        if (arr[mid] == key) {
            return mid;
        }

        //go to right wala part
        if (key > arr[mid]) {
            start = mid + 1;
        } else { //key < arr[mid]
            end = mid - 1;
        }

        mid = start + (end - start) / 2;
    }

    return -1;
}

int searchInRotatedArr(int arr[], int n, int k) {
    int start = 0;
    int end = n - 1;
    int mid = start + (end - start) / 2;
    // find the pivot point
    int pivotP = getPivot(arr, 6);
    //conditions
    if (k >= arr[pivotP] && k <= arr[end]) {
        return binarySearch2(arr, pivotP, end, k);
    } else {
        return binarySearch2(arr, start, pivotP - 1, k);
    }
}

long long int squareRootInt(int n) {
    int start = 0;
    int end = n - 1;
    long long int mid = start + (end - start) / 2; // for out of range
    long long int ans = -1;
    while (start <= end) {
        long long int square = mid * mid;// if it goes out of range

        if (square == n) {
            return mid;
        }
        if (square < n) {
            ans = mid;
            start = mid + 1;
        } else {
            end = mid - 1;

        }
        mid = start + (end - start) / 2;
    }
    return ans;
}

double squareRootDouble(int n, int precision, int tempSol) {
    double factor = 1;
    double ans = tempSol;
    for (int i = 0; i < precision; i++) {
        factor = factor / 10;
        for (double j = ans; j * j < n; j = j + factor) {
            ans = j;
        }
    }
    return ans;
}

bool isPossibleSol(int arr[], int n, int m, int mid) {
    int stuCount = 1;
    int pgSum = 0;

    for (int i = 0; i < n; i++) {
        if (pgSum + arr[i] <= mid) {
            pgSum += arr[i];
        } else {
            stuCount++;
            if (stuCount > m || arr[i] > mid) {
                // agar studentC given no. of students se zyada ho jaye
                // or agar index value mid se badi ho jaye
                return false;
            }
            pgSum = 0;
            pgSum = arr[i];
        }
    }
    return true;
}

int bookAllocation(int arr[], int n, int m) {
    // n = size
    // m = no. of students
    int start = 0;
    int sum = 0;
    int ans = -1;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    int end = sum;
    int mid = start + (end - start) / 2;

    while (start <= end) {
        if (isPossibleSol(arr, n, m, mid)) {
            ans = mid;
            end = mid - 1;
        } else {
            start = mid + 1;
        }
        mid = start + (end - start) / 2;
    }
    return ans;
}

int painterPartition(int arr[], int n, int m) {}

int aggressiveCows(vector<int> &arr, int cows) {
    //minimum distance b/w 2 cows should be maximum
    sort(arr.begin(), arr.end());
    int start = 0;
    int maxi = -1;//maximum value in the array
    for (int i = 0; i < arr.size(); i++) {
        maxi = max(maxi, arr[i]);
    }
    int end = maxi;
    int mid = start + (end - start) / 2;
    int ans;
    while (start <= end) {
        if (isPossibleSol2(arr, cows, mid)) {
            ans = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
        mid = start + (end - start) / 2;
    }
    return ans;
}

bool isPossibleSol2(vector<int> &arr, int cows, int mid) {
    int cowCount = 1;
    int lastPos = arr[0];
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] - lastPos >= mid) {
            cowCount++;
            if (cowCount == cows) { return true; }
            lastPos = arr[i];
        }
    }

    return false;
}

int main() {
    int arr[6] = {5, 6, 1, 2, 3, 4}; // sorted rotated array
    int p = getPivot(arr, 6);
    p = searchInRotatedArr(arr, 6, 2);
    int temp = squareRootInt(37);
    cout << squareRootDouble(39, 3, temp);

    return 0;
}
