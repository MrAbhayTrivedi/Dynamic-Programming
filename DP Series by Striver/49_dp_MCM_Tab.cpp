/*
Matrix Chain Multiplication | Tabulation Method

Understanding the dp array

In the memoization approach, we have taken a dp[N][N]. Let us revise it and understand what dp[i][j] means.

            i            j
arr[5]:[10, 20, 30, 40, 50]        dp[n][n]
            A1  A2  A3  A4
    n=5
Dimensions of:
A1=10*20
A2=20*30                      dp[i][j] means minimum operations to 
A3=30*40                      get product of matrices Ai.Ai+1.Ai+2...Aj
A4=40*50

As we have to find A1.A2.A3.A4, we will return dp[1][4] as our final answer.

Rules to write tabulation solution from the memoization solution

    -> Write the base case.
    -> Write down the changing parameters in terms of loops.
    -> Write the recursive logic inside the loops.

Base Case

Let us discuss the base case first, in the memoization approach the base case was:

if (i==j) return 0
Now dp[i][i] means minimum operations to get the multiplication of Ai which means a single array which doesn’t mean anything in the context of this problem so we return 0. Therefore we write a loop to set the base case in our dp array as follows:

for(int i=0; i<n; i++) dp[i][i] = 0;

Changing Parameters

In tabulation, we follow a bottom-up approach that is we start from a smaller problem to the bigger problem, so here we start from (n-1)th matrix and move towards the first matrix i.e

A4_ -> A3_ -> A2_ -> A1_ . 

These dashes are the matrix represented by the j pointer.

As j>i, we will start j from i+1 to N-1, thus the pattern of problem-solving becomes:

A4 -> A3.A4 -> A2.A3.A4 -> A1.A2.A3.A4.

This pattern can be achieved by writing the loops in the following way:

for(int i=n-1;i>=1;i--){
    for(int j=i+1;j<=n-1;j++){
        // recursive logic
    }
}

Recursive Logic:

Next, we just copy down the recursive logic and modify it as required.

Time Complexity: O(N*N*N)

Reason: There are N*N states and we explicitly run a loop inside the function which will run for N times, therefore at max ‘N*N*N’ new problems will be solved.

Space Complexity: O(N*N)

Reason: We are using a 2D array ( O(N*N)) space.
*/
#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum number of operations for matrix multiplication
int matrixMultiplication(vector<int>& arr, int N) {
    // Create a DP table to store the minimum number of operations
    vector<vector<int>> dp(N, vector<int>(N, -1));

    // Initialize the diagonal elements of the DP table to 0
    for (int i = 0; i < N; i++) {
        dp[i][i] = 0;
    }

    // Loop for the length of the chain
    for (int len = 2; len < N; len++) {
        for (int i = 1; i < N - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;

            // Try different partition points to find the minimum
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k + 1][j] + arr[i - 1] * arr[k] * arr[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    // The result is stored in dp[1][N-1]
    return dp[1][N - 1];
}

int main() {
    vector<int> arr = {10, 20, 30, 40, 50};
    int n = arr.size();

    cout << "The minimum number of operations for matrix multiplication is " << matrixMultiplication(arr, n) << endl;

    return 0;
}