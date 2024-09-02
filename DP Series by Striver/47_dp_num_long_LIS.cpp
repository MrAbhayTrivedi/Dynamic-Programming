/*
Number of Longest Increasing Subsequences 

Prerequisite: Longest increasing subsequence, Printing Longest Increasing subsequence

Problem Link: 

Given an array, ‘Arr’ of length ‘n’, count the number of longest increasing subsequences (LIS).

Array:[1,3,5,4,7]
The lenght of the longest increasing subsequence is 4.
The count of the longest increasing subsequence is 2.
The two longest increasing subsequences are [1,3,5,7] and [1,3,4,7].

Solution

Intuition:

Now let us revise the approach for finding the LIS as discussed in Printing Longest Increasing subsequence. Readers are highly advised to understand that approach first. In that solution, we write two nested loops to get a dp array whose maximum element gives us the length of the LIS as shown below:

for(int i=0;i<=n;i++){
    for(int prev_index=0;prev_index<=ind-1;prev_index++){
        if(arr[prev_index]<arr[i]){
            dp[i]=max(dp[i],1+dp[prev_index]);
        }
    }
}

Now, what does this dp[i] represent? It represents the LIS in the array ‘arr’ from index 0 to index i in the array ending with element arr[i]. Therefore the maximum value of dp[i] in gives us the LIS of the array.

arr[]:[1 11 2 10 4 5 2 1]
dp[]: [1 2 2 3 3 4 2 1]
dp[i] gives the length of the LIS from index 0 to index i in the array ending with element arr[i].
Here dp[5] gives us the length of LIS (4)

Now, after understanding the approach to finding the LIS, let us revisit the problem of counting the number of longest increasing subsequences of the array.

Let us take a new array ct[ ] to calculate the count and initialize it to 1. Then ct[i] will be the count of the number of longest increasing subsequences where each LIS ends where arr[i] is the last element of the subsequence.

Let us now understand the approach to get the values of the ct[ ] array, i.e to count the number of LIS. For that we will consider the below example:

Logic and approach for the dp and ct array[ ]

Initial example:

The initial example is given below and the dp[ ] and ct[ ] array are initialized to 1.

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 1 1 1 1 1 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

Now, we will iterate over the array and one by one see the final value of the dp[ ] and ct[ ] array. At this stage, it is super important to have a crystal clear understanding of what dp[i] and ct[i] means. Therefore their definitions are given in the below figure:

Definition of dp[i]: dp[i] reefers to the length of the LIS of the orignal array with the element arr[i] as the last element of the LIS.

Definition of ct[i]: ct[i] refers to the count of LIS of the original array that are possible of length dp[i] with the element arr[i] as the last element of the LIS.

For i = 0,

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 1 1 1 1 1 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

We know that dp[i] and ct[i] will be 1 as they will be the only member of the unique LIS.

For i=1,

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 1 1 1 1 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

We know that 5 is greater than 1, so we can append it, therefore dp[1] will be 2 and the count still remains 1.

Similar is the case for i = 2,3 and 4.

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 1 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

For i=5,
This is an interesting case and we will break it into pieces. We are setting a nested loop, where i =5 and prev_index(say j) runs from 0 to 4.

Initially j=0,

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 2 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

At j=0, arr[j]<arr[i] and dp[j+1]>dp[i], therefore we can place 1 before 6 in the subsequence([1, 6]) to get LIS of length 2 in such a case, ct[i] will be ct[j]. In other words, the number of ways of getting LIS ending at arr[i], i.e ct[i] is equal to the number of ways of getting ct[j]. (ct[i] = ct[j]).

At j=1, a similar case will follow, as arr[j]<arr[i] and dp[j+1]>dp[i], therefore we again update ct[i] to the value of ct[j].

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 3 1 1 1 1]
ct[]: [1 1 1 1 1 1 1 1 1 1]

Now let us see what happens at j =2,

At j=2, arr[j]<arr[i], therefore we can consider placing before 6 but the length o0f LIS by placing the 4 before 6 will be 3, which is the existing value of dp[i]. In such a case we need to consider both the existing and the new LIS. Therefore, we will update ct[i] = ct[i] + ct[j], i.e 2 to count both the LIS ( [1, 5, 6] and [1, 4, 6]).

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 3 1 1 1 1]
ct[]: [1 1 1 1 1 2 1 1 1 1]

Similar will be the case for j=3, and j=4 as both will give us LIS of length 3 so we will count them as well.

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 3 1 1 1 1]
ct[]: [1 1 1 1 1 4 1 1 1 1]
LIS with arr[i] as last child: [1, 5, 6], [1, 4, 6] ,[1, 3, 6]. [1, 2, 6]
Count of such  LIS: 4

For i=6,
When j=5, arr[j]<arr[i], so we can add 6 before 7 for LIS, so we can again have 4 LIS.

arr[]:[1 5 4 3 2 6 7 10 8 9]
dp[]: [1 2 2 2 2 3 4 1 1 1]
ct[]: [1 1 1 1 1 4 4 1 1 1]
LIS with arr[i] as last child: [1, 5, 6, 7], [1, 4, 6, 7], [1, 3, 6, 7], [1, 2, 6, 7]
Count of such  LIS: 4

Approach:

If we closely see the example we see two patterns for the nested loop conditions. We will always consider element at prev_index( say j) to place before element at index i only if arr[j] < arr[i]. Now, there arises two conditions:

    -> if( arr[j] < arr[i] && dp[j+1] > dp[i]), in this case we get a new LIS of greater length, therefore the number of LIS ending at arr[i], is the same as number of LIS ending at arr[j] as we simply append the element arr[j] to all those LIS. In simple terms, ct[i] = ct[j]. Try to dry run this example to understand: [1, 2, 3],
    -> if( arr[j] < arr[i] && dp[j+1]==dp[i]) in this case we get a new LIS of same length at which the ct[i] is originally holding the value for. Therefore the new ct[j] value will be the number of LIS that was given by its original value plus the number of LIS that ends at element arr[j] at length dp[j]. In simple terms, ct[i] = ct[i] + ct[j]. Try to dry run this example to understand: [1, 5, 6, 10].
Based on these two conditions we can easily calculate the ct[ ]n array and return the ct[ ] value for the maximum value(s) of the dp[ ] array.

Time Complexity: O(N*N)

Reason: There are two nested loops that are run twice.

Space Complexity: O(N)

Reason: We are only using two rows of size n.

*/
#include <bits/stdc++.h>
using namespace std;

// Function to find the count of Longest Increasing Subsequences (LIS)
int findNumberOfLIS(vector<int>& arr) {
    int n = arr.size();

    vector<int> dp(n, 1); // dp[i] stores the length of the LIS ending at arr[i]
    vector<int> ct(n, 1); // ct[i] stores the count of LIS ending at arr[i]

    int maxi = 1; // Initialize the maximum length as 1

    for (int i = 0; i < n; i++) {
        for (int prev_index = 0; prev_index < i; prev_index++) {
            if (arr[prev_index] < arr[i] && dp[prev_index] + 1 > dp[i]) {
                dp[i] = dp[prev_index] + 1;
                // Inherit count
                ct[i] = ct[prev_index];
            } else if (arr[prev_index] < arr[i] && dp[prev_index] + 1 == dp[i]) {
                // Increase the count
                ct[i] = ct[i] + ct[prev_index];
            }
        }
        maxi = max(maxi, dp[i]);
    }

    int numberOfLIS = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == maxi) {
            numberOfLIS += ct[i];
        }
    }

    return numberOfLIS;
}

int main() {
    vector<int> arr = {1, 5, 4, 3, 2, 6, 7, 2};

    cout << "The count of Longest Increasing Subsequences (LIS) is " << findNumberOfLIS(arr) << endl;

    return 0;
}