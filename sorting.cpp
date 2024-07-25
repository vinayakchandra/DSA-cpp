#include<iostream>

using namespace std;

void selectionSort(int arr[], int n) {
    // n = size of the array
    // small element ko left me le jao
    for (int i = 0; i < n - 1; i++) {
        // i is minIndex
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                //swap
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                // another method of swap
//                 swap(arr[i], arr[j]);
            }
        }
    }
    // printing in array
    for (int i = 0; i < n; i++) {
        cout << arr[i];
    }
}

void bubbleSort(int arr[], int n) {
    // large no. ko right me le jao
    //
    int sum = 0;
    bool swapped = false; // optimising for sorted
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                swap(arr[i], arr[j]); // swap
                swapped = true;
                // printing in each iteration
                for (int i = 0; i < n; i++) {
                    cout << arr[i];
                }
                cout << endl;
                sum++;
            }
        }
        if (swapped == false) {
            break;
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << arr[i];
//    }
    cout << "total no. of iterations: " << sum;
}

void insertionSort(int arr[], int n) {
    // assume karo 0 index wala sorted hai
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        for (; j >= 0; j--) {
            if (arr[j] > temp) {
                //shift
                arr[j + 1] = arr[j];
            } else { break; }
        }
        //copy temp value
        arr[j + 1] = temp;
    }
}

void mergeArrays(int arr1[], int arr2[], int n, int m) {
    int merged[n + m];
    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {
        if (arr1[i] <= arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }

    while (i < n) {
        merged[k++] = arr1[i++];
    }

    while (j < m) {
        merged[k++] = arr2[j++];
    }

    // Copy the merged elements back to arr1
    for (int i = 0; i < n + m; i++) {
        arr1[i] = merged[i];
        cout << arr1[i];
    }
}

int main() {
    int arr1[] = {4, 6, 3, 2, 5, 1, 9, 8, 7};
    int arr2[] = {0, 2};
//    insertionSort(arr1, 9);
    mergeArrays(arr1, arr2, 9, 2);
}

