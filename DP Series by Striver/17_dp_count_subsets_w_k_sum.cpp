/*
Count Subsets with Sum K

Problem Statement: Count Subsets with Sum K

Pre-req: Subset Sum equal to target, Recursion on Subsequences

We are given an array ‘ARR’ with N positive integers and an integer K. We need to find the number of subsets whose sum is equal to K.

Example:
arr=[1,2,2,3] k=3
We can have 3 subsets with sum =3 i.e., {3}, {1,2}, and {2,3}.
Memorization Approach
Algorithm / Intuition
A Greedy Solution doesn’t make sense because we are not looking to optimize anything. We can rather try to generate all subsequences using recursion and whenever we get a single subsequence whose sum is equal to the given target, we can count it.

Note: Readers are highly advised to watch this video “Recursion on Subsequences” to understand how we generate subsequences using recursion.

Steps to form the recursive solution:
We will first form the recursive solution by the three points mentioned in Dynamic Programming Introduction.

Step 1: Express the problem in terms of indexes.

The array will have an index but there is one more parameter “target”. We are given the initial problem to find whether there exists in the whole array a subsequence whose sum is equal to the target.

So, we can say that initially, we need to find(n-1, target) which means that we are counting the number of subsequences in the array from index 0 to n-1, whose sum is equal to the target. Similarly, we can generalize it for any index ind as follows:

f(ind,target)-> Count number of subsequences that exists in the Array from index 0 to ind, whose sum is equal to target.

Base Cases:
    If target == 0, it means that we have already found the subsequence from the previous steps, so we can return 1.
    If ind==0, it means we are at the first element, so we need to return arr[ind]==target. If the element is equal to the target we return 1 else we return 0.

f(ind,target){
    if(target==0)return 1;
    if(ind==0)return arr[ind]==target;
}
Step 2: Try out all possible choices at a given index.

We need to generate all the subsequences. We will use the pick/non-pick technique as discussed in this video “Recursion on Subsequences”.

We have two choices:

    Exclude the current element in the subsequence: We first try to find a subsequence without considering the current index element. For this, we will make a recursive call to f(ind-1,target).
    Include the current element in the subsequence: We will try to find a subsequence by considering the current index as element as part of subsequence. As we have included arr[ind], the updated target which we need to find in the rest if the array will be target - arr[ind]. Therefore, we will call f(ind-1,target-arr[ind]).
Note: We will consider the current element in the subsequence only when the current element is less than or equal to the target.

f(ind,target){
    if(target==0)return 1;
    if(ind==0)return arr[ind]==target;
    notTaken = f(ind-1,target);
    taken = 0;
    if(arr[ind]<=target)
    taken = f(ind-1,target-arr[ind]);
}

Step 3:  Return sum of taken and notTaken

As we have to return the total count of subsets with the target sum, we will return the sum of taken and notTaken from our recursive call.

The final pseudocode after steps 1, 2, and 3:

f(ind,target){
    if(target==0)return 1;
    if(ind==0)return arr[ind]==target;
    notTaken = f(ind-1,target);
    taken = 0;
    if(arr[ind]<=target)
    taken = f(ind-1,target-arr[ind]);
    return notTaken + taken;
}

Steps to memoize a recursive solution:

If we draw the recursion tree, we will see that there are overlapping subproblems. In order to convert a recursive solution the following steps will be taken:

    -> Create a dp array of size [n][k+1]. The size of the input array is ‘n’, so the index will always lie between ‘0’ and ‘n-1’. The target can take any value between ‘0’ and ‘k’. Therefore we take the dp array as dp[n][k+1]
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer of particular parameters (say f(ind,target)), we first check whether the answer is already calculated using the dp array(i.e dp[ind][target]!= -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[ind][target] to the solution we get.

Complexity Analysis
Time Complexity: O(N*K)

Reason: There are N*K states therefore at max ‘N*K’ new problems will be solved.

Space Complexity: O(N*K) + O(N)

Reason: We are using a recursion stack space(O(N)) and a 2D array ( O(N*K)).

Tabulation Approach
Algorithm / Intuition
To convert the memoization approach to a tabulation one, create a dp array with the same size as done in memoization. We can initialize it as 0.

First, we need to initialize the base conditions of the recursive solution.

    If target == 0, ind can take any value from 0 to n-1, therefore we need to set the value of the first column as 1.


    The first row dp[0][] indicates that only the first element of the array is considered, therefore for the target value equal to arr[0], only cell with that target will be true, so explicitly set dp[0][arr[0]] =1, (dp[0][arr[0]] means that we are considering the first element of the array with the target equal to the first element itself). Please note that it can happen that arr[0]>target, so we first check it: if(arr[0]<=target) then set dp[0][arr[0]] = 1.


    After that, we will set our nested for loops to traverse the dp array, and following the logic discussed in the recursive approach, we will set the value of each cell. Instead of recursive calls, we will use the dp array itself.
    At last, we will return dp[n-1][k] as our answer.

Complexity Analysis
Time Complexity: O(N*K)

Reason: There are two nested loops

Space Complexity: O(N*K)

Reason: We are using an external array of size ‘N*K’. Stack Space is eliminated.

Space Optimization Approach
Algorithm / Intuition
If we closely look the relation,

dp[ind][target] =  dp[ind-1][target] + dp[ind-1][target-arr[ind]]

We see that to calculate a value of a cell of the dp array, we need only the previous row values (say prev). So, we don’t need to store an entire array. Hence we can space optimize it.

Note: Whenever we create a new row ( say cur), we need to explicitly set its first element is true according to our base condition.

Complexity Analysis
Time Complexity: O(N*K)

Reason: There are two nested loops

Space Complexity: O(K)

Reason: We are using an external array of size ‘K+1’ to store only one row.

Extra edge case for the problem Count Subsets with Sum K

In the problem Count Subsets with Sum K, the problem constraints stated that an array element is greater than 0, so the code we have written there works perfectly for the given constraints.

If the constraints mentioned that an array element can also be equal to 0 and the target sum can also be 0, then that code will fail. To understand it we will take an example:

Let the target arr = [0,0,1] and the target = 1.

The previous code will give us the answer 1 as it first takes the element arr[2] and then finds the answer by picking it. Then from the base condition, we will return 0 ( as the target will become 0 by picking 1). But for this question, the answer will be 4 with the following subsets({0,1},{0,1},{0,0,1} and {1}).

Therefore we need to modify the base conditions in order to handle the changes. These are the base conditions of that problem.

f(ind,target){
    if(target==0)return 1;
    if(ind==0)return arr[ind]==target;
}

First of all, we will remove target==0 because now when target ==0, there can be many 0s present in the array which needs to be counted in the answer.

for(int i=0;i<n;i++){
    if(ind==0)return arr[ind]==target;

Now, the following cases can arise when we are at index 0, if the target sum is 0 and the first index is also 0, like in case [0,1], we can form the subset in two ways, either by considering the first element or leaving it, so we can return 2.
f(ind,target){                                        arr=[0,1] target=1
    if(ind==0){                                      ind=1{}
    if(target==0 && arr[ind]==0)return 2;              |pick1
    }                                                ind=0{1,}  ind=0&&target=0 &&arr[0]=0
}                                             Pick 0   /\ Not pick 0
                                               {0,1}         {1}

Else at index 0, if target == 0, and the first element is not 0, it means we will not pick the first element so we just return 1 way.
f(ind,target){
if(ind==0){
    if(target==0 && arr[ind]==0)return 2;
    if(target==0 )return 1;
}

Or if at index 0, when the first element is not 0, and the target is equal to the first element , then we will include it in the subset and we will return 1 way.
f(ind,target){
if(ind==0){
    if(target==0 && arr[ind]==0)return 2;
    if(target==0 || arr[0]==target)return 1;
}
Else in all other cases, we simply return 0.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to count the number of subsets with a given sum
int findWaysUtil(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    // Base case: If the target sum is 0, we found a valid subset
    if (target == 0)
        return 1;

    // Base case: If we have considered all elements and the target is still not 0, return 0
    if (ind == 0)
        return (arr[0] == target) ? 1 : 0;

    // If the result for this state is already calculated, return it
    if (dp[ind][target] != -1)
        return dp[ind][target];

    // Recursive cases
    // 1. Exclude the current element
    int notTaken = findWaysUtil(ind - 1, target, arr, dp);

    // 2. Include the current element if it doesn't exceed the target
    int taken = 0;
    if (arr[ind] <= target)
        taken = findWaysUtil(ind - 1, target - arr[ind], arr, dp);

    // Store the result in the DP table and return
    return dp[ind][target] = notTaken + taken;
}

// Using Memoization
//  Function to count the number of subsets with a given sum
int findWays(vector<int> &num, int k)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return findWaysUtil(n - 1, k, num, dp);
}

// Using Tabulation
//  Function to count the number of subsets with a given sum
int findWays_Tab(vector<int> &num, int k)
{
    int n = num.size();

    // Create a 2D DP table with dimensions n x k+1, initialized with zeros
    vector<vector<int>> dp(n, vector<int>(k + 1, 0));

    // Base case: If the target sum is 0, there is one valid subset (the empty subset)
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = 1;
    }

    // Initialize the first row based on the first element of the array
    if (num[0] <= k)
    {
        dp[0][num[0]] = 1;
    }

    // Fill in the DP table using a bottom-up approach
    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= k; target++)
        {
            // Exclude the current element
            int notTaken = dp[ind - 1][target];

            // Include the current element if it doesn't exceed the target
            int taken = 0;
            if (num[ind] <= target)
            {
                taken = dp[ind - 1][target - num[ind]];
            }

            // Update the DP table
            dp[ind][target] = notTaken + taken;
        }
    }

    // The final result is in the last cell of the DP table
    return dp[n - 1][k];
}

// Using Space Optimization
//  Function to count the number of subsets with a given sum
int findWays_SO(vector<int> &num, int k)
{
    int n = num.size();

    // Initialize a vector 'prev' to represent the previous row of the DP table
    vector<int> prev(k + 1, 0);

    // Base case: If the target sum is 0, there is one valid subset (the empty subset)
    prev[0] = 1;

    // Initialize the first row based on the first element of the array
    if (num[0] <= k)
    {
        prev[num[0]] = 1;
    }

    // Fill in the DP table using a bottom-up approach
    for (int ind = 1; ind < n; ind++)
    {
        // Create a vector 'cur' to represent the current row of the DP table
        vector<int> cur(k + 1, 0);

        cur[0] = 1;

        for (int target = 1; target <= k; target++)
        {
            // Exclude the current element
            int notTaken = prev[target];

            // Include the current element if it doesn't exceed the target
            int taken = 0;
            if (num[ind] <= target)
            {
                taken = prev[target - num[ind]];
            }

            // Update the current row of the DP table
            cur[target] = notTaken + taken;
        }

        // Set 'cur' as 'prev' for the next iteration
        prev = cur;
    }

    // The final result is in the last cell of the 'prev' vector
    return prev[k];
}

// Function to count the number of subsets with a given sum
int findWaysUtil_mod(int ind, int target, vector<int> &arr, vector<vector<int>> &dp)
{
    // Base case: If the target sum is 0, we found a valid subset
    if (ind == 0)
    {
        if (target == 0 and arr[0] == 0)
            return 2;
        if (target == 0 || target == arr[0])
            return 1;
        return 0;
    }

    // If the result for this state is already calculated, return it
    if (dp[ind][target] != -1)
        return dp[ind][target];

    // Recursive cases
    // 1. Exclude the current element
    int notTaken = findWaysUtil_mod(ind - 1, target, arr, dp);

    // 2. Include the current element if it doesn't exceed the target
    int taken = 0;
    if (arr[ind] <= target)
        taken = findWaysUtil_mod(ind - 1, target - arr[ind], arr, dp);

    // Store the result in the DP table and return
    return dp[ind][target] = notTaken + taken;
}

// Using Memoization With constraints num[i]>=0
//  Function to count the number of subsets with a given sum
int findWays_mod(vector<int> &num, int k)
{
    int n = num.size();
    vector<vector<int>> dp(n, vector<int>(k + 1, -1));
    return findWaysUtil_mod(n - 1, k, num, dp);
}
int main()
{
    vector<int> arr = {1,2,2,3};
    int k = 3;

    cout << "The number of subsets found are " << findWays(arr, k) << endl;     // Using Memoization
    cout << "The number of subsets found are " << findWays_Tab(arr, k) << endl; // Using Tabulation
    cout << "The number of subsets found are " << findWays_SO(arr, k) << endl;  // Using Space Optimization

    arr = {0,0,1};
    k = 1;
    cout << "The number of subsets found are " << findWays_mod(arr, k) << endl; // Using Memoization With constraints num[i]>=0

    return 0;
}
