/*
Printing Longest Increasing Subsequence

This article will consist of three parts:

    -> First, we will discuss the tabulation dp approach in continuation of the previous article.
    -> Next, we will discuss a new algorithm called the “Tabulation algorithm” to solve the problem of finding the longest increasing subsequence.
    -> In the last section, we will discuss the approach to printing the longest increasing subsequence.


Part 1: Writing the tabulation approach for finding LIS.

To convert the memoization approach to a tabulation one, create a dp array with the same size as done in memoization i.e dp[N][N+1]. 

    -> Now the base case is if(ind==n), we return 0. We can initialize the entire dp array as 0. In this way, we need to write the base case explicitly.
    -> The changing parameters in the recursive code are ind and prev_index. We will write them in the opposite direction of memoization. 
    -> We will set for a loop of ind to range from n-1 to 0.
    -> If we look closely at the recursive tree, we will see a pattern that the second parameter, prev_index is always smaller than the first parameter ind. Therefore we will write the for loop for prev_index to start from ind-1 till -1.
    -> Next, we write the recursive logic inside the nested loops.
    -> We need to keep in that mind that we are storing prev_index in the dp array by making a coordinate shift (discussed in /** link to dp - 41 ** /).
    -> At last, we will print dp[0][0] as our answer.

Time Complexity: O(N*N)

Reason: There are two nested loops

Space Complexity: O(N*N)

Reason: We are using an external array of size ‘(N+1)*(N+1)’. Stack Space is eliminated.

 Space Optimization

If we closely we are using two rows: dp[ind+1][ ], dp[ind][ ],

So we are not required to contain an entire array, we can simply have two rows next and cur where next corresponds to dp[ind+1] and cur to dp[ind].

After declaring next and cur, replace dp[ind+1] to next and dp[ind] with cur and after the inner loop executes, we will set next = cur, so that the cur row can serve as next for the coming iteration.

Time Complexity: O(N*N)

Reason: There are two nested loops.

Space Complexity: O(N)

Reason: We are only using two rows of size n.

*/
#include <bits/stdc++.h>
using namespace std;

//LIS Using Tabulation
int longestIncreasingSubsequence(int arr[], int n){
    
    vector<vector<int>> dp(n+1,vector<int>(n+1,0));
    
    for(int ind = n-1; ind>=0; ind --){
        for (int prev_index = ind-1; prev_index >=-1; prev_index --){
            
            int notTake = 0 + dp[ind+1][prev_index +1];
    
            int take = 0;
    
            if(prev_index == -1 || arr[ind] > arr[prev_index]){
                
                take = 1 + dp[ind+1][ind+1];
            }
    
            dp[ind][prev_index+1] = max(notTake,take);
            
        }
    }
    
    return dp[0][0];
}

//LIS using Space Optimization
int longestIncreasingSubsequence_SO(int arr[], int n){
    
    vector<int> next(n+1,0);
    
    vector<int> cur(n+1,0);
    
    for(int ind = n-1; ind>=0; ind --){
        for (int prev_index = ind-1; prev_index >=-1; prev_index --){
            
            int notTake = 0 + next[prev_index +1];
    
            int take = 0;
    
            if(prev_index == -1 || arr[ind] > arr[prev_index]){
                
                take = 1 + next[ind+1];
            }
    
            cur[prev_index+1] = max(notTake,take);
        }
        next = cur;
    }
    
    return cur[0];
}

int main() {
	
	int arr[] = {10,9,2,5,3,7,101,18};
	
	int n = sizeof(arr)/sizeof(arr[0]);
	
	cout<<"The length of the longest increasing subsequence is "
        <<longestIncreasingSubsequence(arr,n)<<"\n";//LIS using tabulation
    cout<<"The length of the longest increasing subsequence is "<<longestIncreasingSubsequence_SO(arr,n)<<"\n";//LIS using space optimization
	
	return 0;
}