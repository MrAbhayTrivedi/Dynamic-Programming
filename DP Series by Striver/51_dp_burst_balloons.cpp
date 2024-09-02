/*
Burst Balloons

Problem Statement: You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array. You are asked to burst all the balloons.

If you burst the ith balloon, you will get arr[i - 1] * arr[i] * arr[i + 1] coins. If i - 1 or i + 1 goes out of the array's bounds, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.

Pre-requisite: MCM & DP 50

Examples
Example 1:
Input:N = 4, array[] = {3, 1, 5, 8}
Output: 167
Explanation:
First, we will burst the second balloon with the value 1. Coins = 3*1*5 = 15.
Second, we will burst the balloon with the value 5. Coins = 3*5*8 = 120.
Third, we will burst the balloon with the value 3. Coins = 1*3*8 = 24.
Fourth, we will burst the balloon with the value 8. Coins = 1*8*1 = 8.
So, the total number of coins we can collect is 167. This is the maximum number of coins we can collect.

Example 2:
Input: N = 2, array[] = {1, 5}
Output: 10
Explanation:
First, we will burst the second balloon with the value 1. Coins = 1*1*5 = 5.
Second, we will burst the balloon with the value 5. Coins = 1*5*1 = 5.
So, the total number of coins we can collect is 10. This is the maximum number of coins we can collect.

Recursive Approach
Algorithm / Intuition
From the question, we can easily understand that we must burst the balloons in a particular order to collect the maximum number of coins. For example, in the first case, we followed the order: 1, 5, 3, 8 to collect the maximum number of coins i.e. 167. So, the order of bursting the balloons will change the number of coins we can collect. There may be several orders that we can follow.

So, in order to find a valid order, can figure out the first balloon we will burst. Apparently, the entire array(i.e. given) is the range of the elements(i.e. the balloons) and anyone among the elements can be the first.

First, we will try to solve the problem using the technique we have learned in MCM. In the MCM, we selected the matrices sequentially so that the number of scalar multiplication is minimized. Similarly, here we can maintain an order where we will first try to choose the first element, then we can try to find the second one, and so on. 

Now, let’s understand if we can really solve the problem using the above approach:

Let’s consider the following example:

We are given an array: {b1, b2, b3, b4, b5, b6}. Each element of the given array is representing a balloon. Now, if we burst the b4, we will get a total of (b3*b4*b5) coins. After bursting b4, we are left with the left sub-problem {b1, b2, b3} and the right sub-problem {b5, b6} to solve.

Now, the question is, if we can say that the final answer will be the summation of the current number of coins and the answers from the left and right subproblems. The answer is No.

Let’s understand the reason behind this. Imagine, at first we burst the balloon b4. Then, we are left with the array:  {b1, b2, b3, b5, b6}. Now, if we try to burst b3, it will be dependent on b5. Similarly, if we try to burst b5, it will be dependent on b3. Similarly, we can observe the same dependency in the case of other elements as well. So, we cannot solve the subproblems {b1, b2, b3} and {b4, b5} independently as they are dependent on each other.

Intuition:
Until now, we have clearly understood that we cannot solve this problem using this approach. So, we will just try to think in the opposite way. First, we tried to find out a balloon that we will burst first. But now, we will first try to find that balloon which we will burst last.

Note: The intuition is to first find the last balloon, then the second last, and so on. This is the sequence we need to follow to solve this problem.

Now, let’s understand how the subproblems are independent in this approach:

Let’s consider the following example:

We are given an array: {b1, b2, b3, b4, b5, b6}. Assume, b4 be the last balloon we will burst. Then we can surely say, the total no. of coins we can get by bursting the balloon b4 is (1*b4*1). Now, we get two subproblems as usual: {b1, b2, b3} and {b5, b6}, and while choosing the second last balloon, we can ensure that b4 exists while bursting the second last balloon. If the second last balloon belongs to the 1st sub-problem i.e. {b1, b2, b3}, it will be only dependent on the last balloon i.e. b4 as the rightmost element will be b4. Similarly,  if the second last balloon belongs to the 2nd sub-problem i.e. {b5, b6}, it will also be dependent only on the last balloon i.e. b4 as the leftmost element will be b4. The following illustration will clarify the concept:

             [b1, b2, b3]              [b5, b6]
Any element from         \            /Any element from
this subarray             \          / this subarray
Second last burst       [] [b4]  or [b4] []
                                ^
                                |
                        [b4]Last Burst

Now, we can clearly observe the subproblems are no anymore dependent on each other.

We have found the right approach until now. Now, let us quickly revise the rules to solve a problem on partition dp.

    -> Start with the entire block/array and mark it with i, j.
    -> Try all partitions.
    -> Return the best possible answer of the two partitions (the answer that comes after dividing the problem into two subproblems and solving them recursively).

Now let us go through these rules and apply them to this problem.

Marking the array with i, j:

We are given an array of balloons of size N. The entire array basically represents the range of the balloons. So, we will place i and j at both ends of the array.

    [b1, b2, b3, b4, b5, b6]
     i                    j

Try all partitions:

As we have figured out the logic for marking the i, and j pointers, we will move to the partitioning loop. We can simply write a for loop(say ind) starting from i to j, The problem is being broken in the following manner:

    [b1, b2, b3, b4, b5, b6]
left subarray   ind  right subarray
     i     /     |    \   j
     f(i,ind-1)  |   f(ind+1,j)
        cost=a[i-1]*a[ind]*a[j+1]

f(i,j){
    for(int ind=i;ind<=j;ind++){
        cost=a[i-1]*a[ind]*a[j+1]//cost
             +f(i,ind-1)//left subproblem
             +f(ind+1,j)//right subproblem;
        }
}

Note: Here f(i, ind-1) is the left sub-problem, and f(ind+1, j) is the right sub-problem. 

Base Case: We can say that when i > j this is not a valid partition and so we will return 0.

Return the best possible answer:

Here, in this problem, we are trying to achieve the maximum possible answer i.e. the maximum number of coins. So, among all the costs calculated, we will just store the maximum one. And finally, the maximum cost will be our answer.

f(i,j){
    if(i>j) return 0;
    int maxi=INT_MIN;//Some small value
    for(int ind=i;ind<=j;ind++){
        cost=a[i-1]*a[ind]*a[j+1]//cost
             +f(i,ind-1)//left subproblem
             +f(ind+1,j)//right subproblem;
        maxi=max(maxi,cost);
        }
}

Approach: 

The recursive algorithm steps are as follows:

    -> Append 1 to both ends of the given array.
    -> Convert the problem to a recursive function marked by two pointers i and j.
    -> Use a loop to check all possible combinations of balloons and get all possible total numbers of coins.
    -> Return the maximum number of coins we can get.
    -> Base case: If i > j, we will return 0.

Time Complexity: Exponential


Memoization Approach
Algorithm / Intuition
Steps to memoize the recursive solution:

    -> Create a dp array of size [n+1][n+1]. i and j can range from 1 to n so we take the size n+1 X n+1.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to particular parameters (say f(i,j)), we first check whether the answer is already calculated using the dp array(i.e dp[i][j]!= -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[i][j] to the solution we get.

Complexity Analysis
Time Complexity: O(N3), There are total N2 no. of states. And for each state, we are running a partitioning loop roughly for N times.

Space Complexity: O(N2) + Auxiliary stack space of O(N), N2 for the dp array we are using. 


Tabulation Approach
Algorithm / Intuition
Tabulation:

    -> First of all, we handle the base case. If (i > j) we return 0. To cover this case we can initialize the entire dp array with 0.
    -> Here, we need the dp of size n+2 X n+2 as the highest value of j can be n and in that case, it will search for the value a[j+1] i.e. a[n+1]. So, to handle this case, we need the size to be n+2.
    -> Next, memoization is a top-down approach, whereas tabulation is bottom-up. Our changing parameters i and j will change in opposite directions, i.e i will change from n→1 and j will change from 1→ n.
    -> Next, we copy down the recursive logic(recurrence) inside the nested loops.

Complexity Analysis
Time Complexity: O(N3), There are total N2 no. of states. And for each state, we are running a partitioning loop roughly for N times.

Space Complexity: O(N2), N2 for the dp array we are using.

*/
#include <bits/stdc++.h>
using namespace std;

// Recursive function to calculate the maximum coins obtained
int maxCoinsHelper(int i, int j, vector<int> &nums) {
    if (i > j) return 0;
    int maxCoins = INT_MIN;
    
    // Iterate through each possible balloon to burst last
    for (int k = i; k <= j; k++) {
        // Calculate the coins obtained by bursting the k-th balloon last
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        
        // Recursively calculate the maximum coins for the remaining balloons
        int remainingCoins = maxCoinsHelper(i, k - 1, nums) + maxCoinsHelper(k + 1, j, nums);
        
        // Update the maximum coins
        maxCoins = max(maxCoins, coins + remainingCoins);
    }
    
    return maxCoins;
}

//Using Recursion
// Function to calculate the maximum coins obtained
int maxCoins(vector<int> &nums) {
    int n = nums.size();
    
    // Add 1 to the beginning and end of the nums array
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    
    // Call the helper function to compute the maximum coins
    return maxCoinsHelper(1, n, nums);
}

// Recursive function to calculate the maximum coins obtained
int maxCoinsHelper(int i, int j, vector<int> &nums, vector<vector<int>> &dp) {
    if (i > j) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int maxCoins = INT_MIN;
    
    // Iterate through each possible balloon to burst last
    for (int k = i; k <= j; k++) {
        // Calculate the coins obtained by bursting the k-th balloon last
        int coins = nums[i - 1] * nums[k] * nums[j + 1];
        
        // Recursively calculate the maximum coins for the remaining balloons
        int remainingCoins = maxCoinsHelper(i, k - 1, nums, dp) + maxCoinsHelper(k + 1, j, nums, dp);
        
        // Update the maximum coins
        maxCoins = max(maxCoins, coins + remainingCoins);
    }
    
    return dp[i][j] = maxCoins;
}

//Using Memoization
// Function to calculate the maximum coins obtained
int maxCoins_Memo(vector<int> &nums) {
    int n = nums.size();
    
    // Add 1 to the beginning and end of the nums array
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    
    // Create a DP array for memoization
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, -1));
    
    // Call the helper function to compute the maximum coins
    return maxCoinsHelper(1, n, nums, dp);
}

//Using Tabulation
// Function to calculate the maximum coins obtained
int maxCoins_Tab(vector<int> &nums) {
    int n = nums.size();
    
    // Add 1 to the beginning and end of the nums array
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    
    // Create a DP array for memoization
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            if (i > j) continue;
            int maxi = INT_MIN;
            
            // Iterate through each possible balloon to burst last
            for (int ind = i; ind <= j; ind++) {
                // Calculate the coins obtained by bursting the ind-th balloon last
                int coins = nums[i - 1] * nums[ind] * nums[j + 1];
                
                // Calculate the maximum coins for the remaining balloons
                int remainingCoins = dp[i][ind - 1] + dp[ind + 1][j];
                
                // Update the maximum coins
                maxi = max(maxi, coins + remainingCoins);
            }
            
            dp[i][j] = maxi;
        }
    }
    
    return dp[1][n];
}


int main() {
    vector<int> nums = {3, 1, 5, 8};
    // int maxCoinsResult = maxCoins(nums);
    // cout << "Maximum coins obtained: " << maxCoinsResult << "\n"<< endl;//Using Recursion
    // int maxCoinsMemoResult = maxCoins_Memo(nums);
    // cout << "Maximum coins obtained (Memoization): " << maxCoinsMemoResult << "\n"<< endl;//Using Memoization
    int maxCoinsTabResult = maxCoins_Tab(nums);
    cout << "Maximum coins obtained (Tabulation): " << maxCoinsTabResult << "\n"<< endl;//Using Tabulation
    
    return 0;
}