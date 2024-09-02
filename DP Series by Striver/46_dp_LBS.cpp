/*
Longest Bitonic Subsequence

Problem Statement: 

Longest Bitonic Subsequence

Prerequisite: Longest increasing subsequence, Printing Longest Increasing subsequence

Given an array, ‘Arr’ of length ‘n’, find the longest bitonic subsequence.

Array: [1, 11, 2, 10, 4, 5, 2, 1]
Length of the longest bitonic subsequence: 6

Problem Statement:

Let us first understand what a bitonic subsequence means.

A bitonic subsequence is a subsequence of an array in which the elements can be any of these three:

    -> First, increase till a point and then decrease.
    -> Goes on increasing (Longest increasing subsequence)
    -> Goes on decreasing (Longest decreasing subsequence)

Bitonic subsequence for the below example is:
Array: [1, 11, 2, 10, 4, 5, 2, 1]
Bitonic subsequence: [1, 2, 10, 4, 2, 1]
                     [1,2,10,5,2,1]
                     [1,11,10,5,2,1]
                     [1,11,10,4,2,1]

Similarly, a subsequence having the elements in either increasing or decreasing order only also counts as a bitonic subsequence. For example:
Array:[1,10,2,3,4,5,6]
Longest Bitonic Subsequence: [1,2,3,4,5,6]

We need to return the length of the longest bitonic subsequence as our answer. 

Solution

Intuition:
The length of the increasing and then decreasing subsequence gives us the hint to think in terms of the longest increasing subsequence (LIS). Now let us revise the approach for finding the LIS as discussed in Printing Longest Increasing subsequence. Readers are highly advised to understand that approach first. In that solution, we write two nested loops to get a dp array whose maximum element gives us the length of the LIS as shown below:

for(int i=0;i<n;i++){
    for(int prev_index=0;prev_index<i;prev_index++){
        if(arr[i]>arr[prev_index]){
            dp[i]=max(dp[i],dp[prev_index]+1);
        }
    }
}

Now, what does this dp[i] represent? It represents the LIS in the array ‘arr’ from index 0 to index i in the array ending with element arr[i]. Therefore the maximum value of dp[i] gives us the LIS of the array.

arr[]=[1,11,2,10,4,5,2,1]
dp: [1,2,2,3,3,4,2,1]
dp[i] gives the length of the LIS from index 0 to index i.
Here, dp[5] gives us length of LIS 4.

Now, after understanding the approach to finding the LIS let us revisit the problem of the longest bitonic subsequence and how it is linked with the problem of LIS.

The below figure breaks general bitonic subsequence into two parts:

arr[]=[1,11,2,10,4,5,2,1]
                   |
                   |
                   |  /\
                   | /  \
                   |/    \ 
                   |____________________________index i
                      i=3,arr[i]=10
                   /                   \
        |                                  |
        |                                  |
        |                                  |
        |  /                               |       \
        | /                                |        \
        |/                                 |         \
        |____________                      |______________
        i=3,arr[i]=10                      i=3,arr[i]=10
        LIS from index 0 to index i        LDS from index i to index n-1
                                                  or
                                            LIS from index n-1 to index i

As we can see in the second part of the bitonic subsequence, the decreasing part, LDS from index i to index n-1 can also be thought of in terms of LIS from index n-1 to index i. Therefore we can compute this two LIS separately to determine the length of the bitonic subsequence:

dp1 gives  the length of the LIS from index 0 to index i.
arr[]=[1,11,2,10,4,5,2,1]
dp1: [1,2,2,3,3,4,2,1]

dp2 gives the length of the LIS from index n-1 to index i.
arr[]=[1,11,2,10,4,5,2,1]
dp2: [1,5,2,4,3,3,2,1]

Now with these two separate lengths of LIS, we can calculate the length of the longest bitonic subsequence for each index i. Here index i is acting as the pivot point of the points. Therefore the length of the longest bitonic subsequence at pivot [ i ] will be dp1[i] + dp2[i] -1. (Note that we are counting the element at index i twice in both the parts so we need to subtract 1 from the final answer). We will return the maximum value of this addition as the final answer as the length of the longest bitonic subsequence.

ans[i] = dp1[i] + dp2[i] -1
arr[]=[1,11,2,10,4,5,2,1]
dp1: [1,2,2,3,3,4,2,1]
dp2: [1,5,2,4,3,3,2,1]
ans: [1,6,3,6,5,6,3,1]

Therefore we will return the max in ans array (6) as the final answer.

Approach:
The algorithm approach is stated as follows:

    -> Using the approach of the article Printing Longest Increasing subsequence, find the dp1[ ] array, where dp1[i] gives us the length of the LIS from index 0 to index i.
    -> Modifying the approach slightly, find the dp2[ ] array, where dp2[i] gives us the length of the LIS from index n-1 to index i. To find this opposite direction LIS simply reverses the direction of variables in the nested loops (see the code).
    -> At last return the answer (the length of the longest bitonic subsequence) as the maximum value of dp1[i] - dp2[i] -1.

Time Complexity: O(N*N)

Reason: There are two nested loops that are run twice.

Space Complexity: O(N)

Reason: We are only using two rows of size n.
*/
#include <bits/stdc++.h>
using namespace std;

// Function to find the length of the longest bitonic subsequence
int longestBitonicSequence(vector<int>& arr, int n) {
    // Initialize two arrays to store the increasing and decreasing subsequences
    vector<int> dp1(n, 1); // dp1[i] stores the length of the longest increasing subsequence ending at arr[i]
    vector<int> dp2(n, 1); // dp2[i] stores the length of the longest decreasing subsequence ending at arr[i]

    // Calculate the longest increasing subsequence
    for (int i = 0; i < n; i++) {
        for (int prev_index = 0; prev_index < i; prev_index++) {
            if (arr[prev_index] < arr[i]) {
                dp1[i] = max(dp1[i], 1 + dp1[prev_index]);
            }
        }
    }

    // Reverse the direction of nested loops to calculate the longest decreasing subsequence
    for (int i = n - 1; i >= 0; i--) {
        for (int prev_index = n - 1; prev_index > i; prev_index--) {
            if (arr[prev_index] < arr[i]) {
                dp2[i] = max(dp2[i], 1 + dp2[prev_index]);
            }
        }
    }

    int maxi = -1;

    // Find the maximum length of the bitonic subsequence
    for (int i = 0; i < n; i++) {
        maxi = max(maxi, dp1[i] + dp2[i] - 1);
    }

    return maxi;
}

int main() {
    vector<int> arr = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = arr.size();

    cout << "The length of the longest bitonic subsequence is " << longestBitonicSequence(arr, n) << endl;

    return 0;
}