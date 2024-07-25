#include <iostream>
#include <vector>

using namespace std;

//rat maze; TC: 4^n^2, SP:O(NxM)
bool isSafe(int newx, int newy, vector<vector<bool> > &visited, vector<vector<int> > &arr, int n) {
    if ((newx >= 0 && newx < n) && (newy >= 0 && newy < n)
        && visited[newx][newy] != 1 && arr[newx][newy] == 1) {
        return true;
    } else { return false; }
}

void searchMazeSolve(int x, int y, vector<vector<int> > &arr, int n, vector<string> &ans,
                     vector<vector<bool> > &visited, string path) {
    //base case
    //last box
    if (x == n - 1 && y == n - 1) {
        ans.push_back(path);
        return;
    }
    //4 movement-> D L R U
    visited[x][y] = true;
    //D
    if (isSafe(x + 1, y, visited, arr, n)) {
        searchMazeSolve(x + 1, y, arr, n, ans, visited, path + 'D');
    }
    //L
    if (isSafe(x, y - 1, visited, arr, n)) {
        searchMazeSolve(x, y - 1, arr, n, ans, visited, path + 'L');
    }
    //R
    if (isSafe(x, y + 1, visited, arr, n)) {
        searchMazeSolve(x, y + 1, arr, n, ans, visited, path + 'R');
    }
    //U
    if (isSafe(x - 1, y, visited, arr, n)) {
        searchMazeSolve(x - 1, y, arr, n, ans, visited, path + 'U');
    }
    visited[x][y] = false;//🔴🔴backtrack🔴
}

vector<string> searchMaze(vector<vector<int> > &arr, int n) {
    // arr has 0,1; for 1 only we can go
    vector<string> ans;
    vector<vector<bool> > visited(n, vector<bool>(n, 0));//checking if visited or not
    string path = "";
    if (arr[0][0] == 0) {//if 1st box is 0
        return ans;
    }
    searchMazeSolve(0, 0, arr, n, ans, visited, path);
    return ans;
}

//no queens attack each other; TC: N!, SP: N*N
void addSoln(vector<vector<int> > &ans, vector<vector<int> > &board, int size) {
    vector<int> temp;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            temp.push_back(board[i][j]);
        }
    }
    ans.push_back(temp);
}

bool isSafe(int row, int col, vector<vector<int> > &board, int n) {
    int x = row;
    int y = col;
    //check for same row
    while (y >= 0) {
        if (board[x][y] == 1) {
            return false;
        }
        y--;
    }
    x = row;
    y = col;
    //diagonal
    while (x >= 0 && y >= 0) {
        if (board[x][y] == 1) {
            return false;
        }
        y--;
        x--;
    }
    x = row;
    y = col;
    while (x < n && y >= 0) {
        if (board[x][y] == 1) {
            return false;
        }
        y--;
        x++;
    }
    return true;
}

void nQueensSolve(int col, vector<vector<int> > &ans, vector<vector<int> > &board, int n) {
    //base case
    if (col == n) {//sab bhar gaye
        addSoln(ans, board, n);
        return;
    }
    //solve 1 case
    for (int row = 0; row < n; row++) {
        if (isSafe(row, col, board, n)) {
            board[row][col] = 1;
            nQueensSolve(col + 1, ans, board, n);
            //backtrack
            board[row][col] = 0;
        }
    }
}

vector<vector<int> > nQueens(int n) {
    vector<vector<int> > board(n, vector<int>(n, 0));
    vector<vector<int> > ans;
    nQueensSolve(0, ans, board, n);
    return ans;
}

//sudoku solver; TC: 9^m (m=no. of empty cell), SP:O(1)
bool isSafeSudoku(int row, int col, vector<vector<int> > &board, int value) {
    for (int i = 0; i < board.size(); i++) {
        //check row
        if (board[row][i] == value) {
            return false;
        }
        //col check
        if (board[i][col] == value) {
            return false;
        }
        //3x3 box(matrix)⭐️
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == value) {
            return false;
        }
    }
    return true;
}

bool sudokuSolve(vector<vector<int> > &board) {
    int n = board[0].size();
    //traverse
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            //empty cell
            if (board[row][col] == 0) {
                for (int val = 1; val <= 9; val++) {//1-9
                    if (isSafeSudoku(row, col, board, val)) {
                        board[row][col] = val;
                        //recursive call
                        bool aageSolnPoss = sudokuSolve(board);
                        if (aageSolnPoss) {
                            return true;
                        } else {
                            //backtrack
                            board[row][col] = 0;
                        }
                    }
                }

                return false;
            }
        }
    }

    return true;
}

void solveSudoku(vector<vector<int> > &sudoku) {
    sudokuSolve(sudoku);
}


int main() {
    return 0;
}