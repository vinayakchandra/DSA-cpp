//
// Created by Vinayak Chandra Suryavanshi on 05/01/24.
//
#include<iostream>
using namespace std;

class Patterns {
public:

    static void trianglePattern(int rows) {
        /*
        #
        ##
        ###
        ####
        #####
        */
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < i + 1; ++j) {
                cout << "#";
            }
            cout << endl;
        }
    }

    static void rectanglePattern(int rows, int cols) {
        /*
        #####
        #####
        #####
        #####
        #####
        */
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                cout << "#";
                if (j == cols - 1) { break; }
            }
            cout << endl;
        }
    }

    static void practice() {
        int a = 11;
        float b = 11.1;
        double c = 11.1;
        string d = "Hello, world";
        bool e = true;
        char f = 'A';
        int i = 1;
//    do {
//        cout << i << "\n";
//        i++;
//    } while
//            (i < 6);
//    return 0;
        int arr[5];
        arr[0] = 5;
        arr[2] = -10;

        // this is same as arr[1] = 2
        arr[3 / 2] = 2;
        arr[3] = arr[0];

        cout << arr[0] << " " << arr[1] << " " << arr[2] << " "
             << arr[3];
    }

    static void numberPattern(int rows, int cols) {
        /*
        123
        456
        789
         */
        int num = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 1; j <= cols; j++) {
                num += 1;
                cout << num;
            }
            cout << endl;
        }
    }

/*
1
121
12321
1234321
123454321
*/
    static void numberPattern2(int num) {
        for (int i = 1; i <= num; i++) {
            int num = 0;
            for (int j = 1; j <= i + (i - 1); j++) {
                if (j > i) {
                    num -= 1;
                    cout << num;
                } else {
                    cout << j;
                    num = j;
                }
            }
            cout << endl;
        }
    }

/*
    1
   121
  12321
 1234321
123454321
 */
    static void numberSpacePattern(int num) {
        int row = 1;
        while (row <= num) {
            // print space
            int space = num - row;
            while (space) {
                cout << " ";
                space -= 1;
            }
            //triangle
            int j = 1;
            while (j <= row) {
                cout << j;
                j += 1;
            }

            //2nd triangle
            int start = row - 1;
            while (start) {
                cout << start;
                start -= 1;
            }
            cout << endl;
            row += 1;
        }
    }
};

int main() {
    int rows, cols;
    cin >> rows;
//    Patterns::numberPattern(rows, cols);
    Patterns::numberSpacePattern(rows);
}
