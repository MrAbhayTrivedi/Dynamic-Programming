/*
Partition Array for Maximum Sum | Front Partition 

Problem Statement: Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has its values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning.

Example 1:
Input:arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation:The partition will be the following to get the largest sum:[1, 15, 7 | 9 | 2, 5, 10]. 
After replacing the elements of each subarray with its maximum, the array will look like this:[15,15,15,9,10,10,10] and the sum will be 84.

Example 2:
Input: arr[] = [1], k = 1
Output: 1
Explanation: only one partition is possible like this: [1] and the sum will be 1.


Recursive Approach
Algorithm / Intuition
In order to solve this problem, we need to partition the given array in such a way that the length of every substring does not exceed k. For example, if the array, [1,15,7,9,2,5,10], is given and the value of k is 3, one of the valid partitions will be [1,15, | 7,9,2, | 5,10].  In this case, the length of each substring is smaller or equal to k.
Now, after making such partitions following the above way, we need to change the elements of each substring with its maximum element. Then we will calculate the sum of the whole array. If we apply this to the above array, it will be like  [15,15, | 9,9,9, | 10,10] and the sum will be 77.

Here, in the question, it is clearly mentioned that we have to do the partition in such a way that the sum of the array becomes the maximum possible.

Intuition:
This problem is similar to the problem Palindrome Partitioning - II. We are also going to solve this problem using the front partition. In the front partition technique, we generally start checking from the starting index and check if we can make a partition after that particular index.

We have found the right approach so far. Now, let us quickly discuss the rules to write the recurrence to solve this problem:

    -> Express everything(i.e. the given array) in terms of the index.
    -> Try all partitions.
    -> Return the best possible answer of all partitions (i.e. the answers that come after dividing the problem into subproblems and solving them recursively).
Derive the base case as well.
To explain the rules, we are considering example 1 i.e. arr = [1,15,7,9,2,5,10] and k = 3.

Express everything(i.e. the given array) in terms of the index:
We are given an array and so it is easy to express the array in terms of the index. Now, following the front partition rules we will place the pointer ind to index 0 i.e. the first index. The function will look like the following:

[1, 15, 7, 9, 2, 5, 10]  f(ind){}
 ind

Try all partitions:

f(ind) actually considers the subarray starting from index ind up to the end index and returns the maximum possible sum by making partitions in that particular subarray. For example, if the given array is [1,15,7,9,2,5,10], f(2) considers the subarray [7,9,2,5,10](following 0-based indexing).
As we have figured out the logic for marking the pointer, ind, we will move to the partitioning loop. We can simply write a for loop(say j) starting from ind to ind+k-1(k = given subarray size) as it is clearly mentioned that the length of a partition can be at most k.  The problem is being broken in the following manner(considering the specified example):

                    1, 15, 7, 9, 2, 5, 10
                    /         \          \ 
    1|15,7,9,2,5,10       1,15|7,9,2,5,10  1,15,7|9,2,5,10
    |    /\..                  |   /\..             | /\..
    Subarray of size 1    Subarray of size 2  subarray of size 3

Note: It may happen that the limit ind+k-1 exceeds the length of the array. That is why we will take the limit of j as min(n, ind+k-1) where n = size of the array. This will avoid the runtime error.
Base case: When the value of ind becomes equal to n(n = size of the array), we can say there are no elements left to be considered. So, when (ind == n) the function will return 0.

f(ind){
    if(ind == n)
        return 0;//base case
    //partitioning loop
    for(int j = ind; j <= min(n, ind+k-1); j++){
        //calculations
    }
}
Return the best possible answer of all partitions:

Observation: How to calculate the answer

It is clearly stated in the question that after making a partition, we have to replace all the elements of the subarray with the maximum element of that subarray. So, we will follow the same.Inside the partitioning loop, after making a partition at j, all the elements of the subarray arr[ind….j] will turn into the maximum element of that subarray i.e. maximum(arr[ind….j]). Therefore, the sum of the subarray will be (maximum element * length of the subarray). Consider the illustration below:

1, 15, 7, 9, 2, 5, 10        =>f(0)-> Sum+f(j+1)
Assuming the partition |
is done after index 2  |
         j
    1,15,7 | 9,2,5,10
    |_____|     |____________f(j+1)//Subproblem
       |
    15,15,15 Converted all the elements of the subarray into the maximum element of that subarray.
    Sum=maximum of subarray * length of the subarray
    Sum = 15 * 3 = 45

So, the answer will be the summation of the sum of the left subarray and the answer returned by the subproblem starting from index j+1 i.e. Sum =  (maximum element * length of the subarray) + f(j+1).

Now, calculating all possible sums, we will consider the maximum one.

f(ind){
    iff(ind == n) return 0;//base case
    int maxAns = INT_MIN;
    int len=0,maxEleement=INT_MIN;
    for(int j = ind; j <= min(n, ind+k-1); j++){
        maxElement = max(maxElement, arr[j]);
        len++;
        int sum = maxElement * len//sum of the subarray
                  +f(j+1);//subproblem
        maxAns = max(maxAns, sum);
    }
    return maxAns;

}

Approach: 
The recursive algorithm steps are as follows:

    -> Convert the problem to a recursive function marked by the pointer ind.
    -> Use a loop to check all possible partitions of the array and calculate the maximum sum we can achieve.
    -> Return the maximum possible sum.
    -> Base case: When the value of ind becomes equal to n(n = size of the array), we can say there are no elements left to be considered. So, when (ind == n) the function will return 0.

Complexity Analysis
Time Complexity: Exponential

Algorithm / Intuition
Steps to memoize the recursive solution:

    -> Create a 1D dp array of size [n]. ind can range from 0 to n-1. So we take the size n.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to a particular parameter (say f(ind)), we first check whether the answer is already calculated using the dp array(i.e dp[ind] != -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[ind] to the solution we get.

Complexity Analysis
Time Complexity: O(N*k)
Reason: There are a total of N states and for each state, we are running a loop from 0 to k.

Space Complexity: O(N) + Auxiliary stack space O(N)
Reason: First O(N) for the dp array we are using.

Tabulation Approach
Algorithm / Intuition
Tabulation:

    -> First of all, we handle the base case. If (ind == n) we return 0. To cover this case we can initialize the entire dp array with 0.
    -> Here, as we are checking dp[j+1]  every time, the function will give a runtime error if j = n-1. To avoid this, we will take the array size as n+1 instead of n.
    -> Next, memoization is a top-down approach, whereas tabulation is bottom-up. Our changing parameter ind will change in opposite directions, i.e ind will change from n-1→0.
    -> Next, we copy down the recursive logic(recurrence) inside the loop.

Complexity Analysis
Time Complexity: O(N*k)
Reason: There are a total of N states and for each state, we are running a loop from 0 to k.

Space Complexity: O(N)
Reason: O(N) for the dp array we are using.
*/

#include <bits/stdc++.h>
using namespace std;

//Using Recursive Approach
// Recursive function to find the maximum sum after partitioning.
int maxSumAfterPartitioning(int ind,vector<int>& num, int k) {
    int n = num.size();

    // Base case: If the current index is equal to the size of the array, return 0.
    if (ind == n) return 0;

    int len = 0;
    int maxi = INT_MIN;
    int maxAns = INT_MIN;

    // Loop through the array starting from the current index.
    for (int j = ind; j < min(ind + k, n); j++) {
        len++;
        maxi = max(maxi, num[j]);
        int sum = len * maxi + maxSumAfterPartitioning(j + 1, num, k);
        maxAns = max(maxAns, sum);
    }
    return maxAns;
}


// Recursive function to find the maximum sum after partitioning.
int f(int ind, vector<int> &num, int k, vector<int> &dp) {
    int n = num.size();

    // Base case: If the current index is equal to the size of the array, return 0.
    if (ind == n) return 0;

    // If the result for this index is already computed, return it from dp array.
    if (dp[ind] != -1) return dp[ind];

    int len = 0;
    int maxi = INT_MIN;
    int maxAns = INT_MIN;

    // Loop through the array starting from the current index.
    for (int j = ind; j < min(ind + k, n); j++) {
        len++;
        maxi = max(maxi, num[j]);
        int sum = len * maxi + f(j + 1, num, k, dp);
        maxAns = max(maxAns, sum);
    }

    // Store the computed result in the dp array and return it.
    return dp[ind] = maxAns;
}

//Using Memoization
int maxSumAfterPartitioning_Memo(vector<int>& num, int k) {
    int n = num.size();
    vector<int> dp(n, -1);
    return f(0, num, k, dp);
}

//Using Tabulation
// Function to find the maximum sum after partitioning the array.
int maxSumAfterPartitioning_Tab(vector<int>& num, int k) {
    int n = num.size();
    
    // Create a DP array to store the maximum sum.
    vector<int> dp(n + 1, 0);
    
    // Iterate through the array from right to left.
    for (int ind = n - 1; ind >= 0; ind--) {
        int len = 0;
        int maxi = INT_MIN;
        int maxAns = INT_MIN;
        
        // Loop through the next k elements (or remaining elements if k is smaller).
        for (int j = ind; j < min(ind + k, n); j++) {
            len++;
            maxi = max(maxi, num[j]);
            int sum = len * maxi + dp[j + 1];
            maxAns = max(maxAns, sum);
        }
        
        // Store the computed maximum sum in the DP array.
        dp[ind] = maxAns;
    }
    
    // The maximum sum after partitioning the entire array is stored in dp[0].
    return dp[0];
}


int main() {
    vector<int> num = {1, 15, 7, 9, 2, 5, 10};
    int k = 3;
    cout << "The maximum sum is: " << maxSumAfterPartitioning(0,num, k)<< "\n";//Uisng Recursive Approach
    cout << "The maximum sum is: " << maxSumAfterPartitioning_Memo(num, k)<< "\n";//Using Memoization
    cout << "The maximum sum is: " << maxSumAfterPartitioning_Tab(num, k)<<"\n";//Using Tabulation
    return 0;
}

