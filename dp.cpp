#include <iostream>
#include <vector>
#include <algorithm>

int solveMaxNonAdj(vector<int> &vector, int n);

int solveMaxNonAdjMem(vector<int> &nums, int n, vector<int> &dp);

using namespace std;

//TC: O(N), SP: O(N) + O(n) = O(N)
//top-down approach
int fibonacci(int n, vector<int> &dp) {
    //base case
    if (n <= 1) { return n; }

    //step3
    //if dp[n] has some value then return that value
    if (dp[n] != -1) { return dp[n]; }

    //step2
    dp[n] = fibonacci(n - 1, dp) + fibonacci(n - 2, dp);
    return dp[n];
}

//bottom-up approach
void fib_tabular() {
    int n;
    cin >> n;
    // step1
    //creating vector of n+1 size
    vector<int> dp(n + 1);
    //step 2
    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n] << endl;
}

//space optimisation
//TC: O(N), SP:O(1)
int fib_opt() {
    int n;
    cin >> n;

    int prev1 = 1;
    int prev2 = 0;
    if (n == 0) { return prev2; }
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        //shift logic
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

//n stairs with cost
//normal recursive
int solveRec(vector<int> &cost, int n) {
    //base case
    if (n == 0) {
        return cost[0];
    }
    if (n == 1) {
        return cost[1];
    }

    int ans = cost[n] + min(solveRec(cost, n - 1), solveRec(cost, n - 2));
    return ans;
}

//memoization TC, SC: O(n)
int solveMem(vector<int> &cost, int n, vector<int> &dp) {
    //base case
    if (n == 0) {
        return cost[0];
    }
    if (n == 1) {
        return cost[1];
    }
//    step3: koi value hai dp me to dedo
    if (dp[n] != -1) { return dp[n]; }


//    step2: memoization
    dp[n] = cost[n] + min(solveMem(cost, n - 1, dp), solveMem(cost, n - 2, dp));
    return dp[n];
}

//tabulation; TC, SC: O(N)
int solveTab(vector<int> &cost, int n) {
    //step1
    vector<int> dp(n + 1);
    //step2
    dp[0] = cost[0];
    dp[1] = cost[1];
    //step3
    for (int i = 2; i < n; i++) {
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
    }
    return min(dp[n - 1], dp[n - 2]);
}

//space optimisation; TC: O(N), SC: O(1)
int solveOpt(vector<int> &cost, int n) {
    int prev2 = cost[0];
    int prev1 = cost[1];
    //step3
    for (int i = 2; i < n; i++) {
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    return min(prev1, prev2);
}

int minCostClimbingStairs(vector<int> &cost) {
    int n = cost.size();
    //step1
//    vector<int> dp(n + 1, -1);
//    int ans = min(solve2(cost, n - 1, dp), solve2(cost, n - 2, dp));
//soln3
//    int ans = solve3(cost, n);
//soln4
    int ans = solveTab(cost, n);
    return ans;
}

//min no. of coins ⭐️
int solveCoin(vector<int> &num, int x) {
    //base case
    if (x == 0) { return 0; }
    if (x < 0) { return INT_MAX; }

    int mini = INT_MAX;
    for (int i = 0; i < num.size(); i++) {
        int ans = solveCoin(num, x - num[i]);
        if (ans != INT_MAX) { //valid ans
            // adding 1 because we are considering curr coin
            mini = min(mini, 1 + ans);
        }
    }
    return mini;
}

//TC:x*n, SP:O(x)
int solveCoin_mem(vector<int> &num, int x, vector<int> &dp) {
    //base case
    if (x == 0) { return 0; }
    if (x < 0) { return INT_MAX; }

    if (dp[x] != -1) { return dp[x]; }

    int mini = INT_MAX;
    for (int i = 0; i < num.size(); i++) {
        int ans = solveCoin_mem(num, x - num[i], dp);
        if (ans != INT_MAX) { //valid ans
            // adding 1 because we are considering curr coin
            mini = min(mini, 1 + ans);
        }
    }
    dp[x] = mini;
    return dp[x];
}

//TC:x*n, SP:O(x)
int solveCoin_tab(vector<int> &num, int x) {
    vector<int> dp(x + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= x; i++) {
        //solve for every amount figure from 1 to x
        for (int j = 0; j < num.size(); j++) {
            //checking if i - num(j) is valid or not and checking for int overflow
            if (i - num[j] >= 0 && dp[i - num[j]] != INT_MAX) {
                dp[i] = min(dp[i], 1 + dp[i - (num[j])]);
            }
        }
    }
    if (dp[x] == INT_MAX) { return -1; }
    return dp[x];
}

int minimumElements(vector<int> &num, int x) {
    //soln1
//    int ans = solveCoin(num, x);
//    if (ans == INT_MAX) { return -1; }
//    return ans;
    //soln2
//    vector<int> dp(x + 1, -1);
//    int ans = solveCoin_mem(num, x, dp);
//    if (ans == INT_MAX) { return -1; }
//    else { return ans; }
    return solveCoin_tab(num, x);
}

//105
int solveMaxNonAdj(vector<int> &nums, int n) {
    //base case
    if (n < 0) return 0;
    if (n == 0) return nums[0];

    int include = solveMaxNonAdj(nums, n - 2) + nums[n];//n-2 + current element
    int exclude = solveMaxNonAdj(nums, n - 1) + 0;

    return max(include, exclude);
}

int solveMaxNonAdjMem(vector<int> &nums, int n, vector<int> &dp) {
    //base case
    if (n < 0) return 0;
    if (n == 0) return nums[0];

    if (dp[n] != -1)return dp[n];

    int include = solveMaxNonAdj(nums, n - 2) + nums[n];//n-2 + current element
    int exclude = solveMaxNonAdj(nums, n - 1) + 0;

    dp[n] = max(include, exclude);
    return dp[n];
}

int solveMaxNonAdjTab(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 0);

    dp[0] = nums[0];
    for (int i = 1; i < n; i++) {
        int include = dp[i - 2] + nums[i];
        int exclude = dp[i - 1] + 0;
        dp[i] = max(include, exclude);
    }
    return dp[n - 1];
}

//SP: O(1)
int solveMaxNonAdjSP(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 0);

    int prev2 = 0;
    int prev1 = nums[0];

    for (int i = 1; i < n; i++) {
        int include = prev2 + nums[i];
        int exclude = prev1 + 0;
        int ans = max(include, exclude);
        prev2 = prev1;
        prev1 = ans;
    }
    return prev1;
}

int maximumNonAdjacentSum(vector<int> &nums) {
//    int n = nums.size();
//    int ans = solveMaxNonAdj(nums, n - 1);
//    return ans;

//    int n = nums.size();
//    vector<int> dp(n, -1);
//    return solveMaxNonAdjMem(nums, n - 1, dp);

//    return solveMaxNonAdjTab(nums);

    return solveMaxNonAdjSP(nums);
}

//106
long long int houseRobber(vector<int> &valueInHouse) {
    int n = valueInHouse.size();

    if (n == 1) return valueInHouse[0];

    vector<int> first, second;
    for (int i = 0; i < n; i++) {
        if (i != n - 1) {
            first.push_back(valueInHouse[i]);
        } else if (i != 0) {
            second.push_back(valueInHouse[i]);
        }
    }
    return max(solveMaxNonAdjTab(first),solveMaxNonAdjTab(second));
}

int main() {
    return 0;
}
