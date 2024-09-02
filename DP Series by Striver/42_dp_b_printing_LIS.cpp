/*
Part 2: Tabulation algorithm to find the length of the longest increasing subsequence.

Algorithm description:

We need to find the length of the longest increasing subsequence if an array of length n.

For example:

arr[6]:[5,4,11,1,16,8]

Now in this algorithm, we need to build logic to get an array( say dp), For this particular example, the dp array will look like this:

dp[6]: [1 1 2 1 3 2]

Now every cell value in this dp array is defined as follows:

For every index i of the array ‘arr’;
dp[ i ] is the length of the longest increasing subsequence that is possible that end with index ind of the original array.

Few examples:

(i) For i = 0, dp[i] =1 , therefore LIS length with the element arr[0], i.e 5 as its last element is 1. The case :[ 5 ].

(ii) For i = 4, dp[i] =3 , therefore LIS length with the element arr[4], i.e 16 as its last element is 3. The case :[ 5, 11, 16 ].

Once we get this dp array our job is to simply return the maximum cell value of the entire array as the length of the longest increasing subsequence.

Now, the main question arises: how do we get this dp[ ] array? The following section explains the logic and the approach.

Logic and approach for the dp array

We know that a single element can always be considered to be included in the LIS, as it can not break any rule of forming the LIS. Therefore we can initialize the dp array by 1, it simply means that currently, LIS is having only that particular member element itself ([5], [4], [11], …). 

arr[6]: [5 4 11 1 16 8]
dp[6]:  [1 1 1  1 1  1]
         0 1 2  3 4  5

Now let us manually try to find dp[i], for some indexes in order to understand the algorithm.

(i) For i = 0, 5 can be the only element that can be in the LIS, as there is no element before it therefore the final dp[i] for i=0, will be 1 only (marked in red).

i=0
arr[6]: [5, 4, 11, 1, 16, 8]
        
dp[6]:  [1, 1, 1,  1, 1,  1]
         ^--Remain 1 only
(ii)  For i = 1, 4 can be the only element that can be in the LIS, as there is only element 5 before but 5 is greater than 4 so cannot be considered in the LIS. therefore the final dp[i] for i=1, will be 1 only (marked in red).

i=1
arr[6]: [5, 4, 11, 1, 16, 8]
        
dp[6]:  [1, 1, 1,  1, 1,  1]
            ^--Remain 1 only

(iii) For i = 2, either 5 or 4 can be considered in the LIS as the last element of 11. We will run a loop that checks all prev_index and if the arr[prev_index] < arr[i], we can simply say that the element should be updated to 1+dp[prev_index]. 1 means that we are adding one element to the LIS, here 11, and also the LIS of the previous indexes which are given by dp[prev_index]. Note we will update only for that prev_index, whose prev_index is the maximum. We will discuss this in the next to next case also.

i=2,dp[2]=1+dp[prev_index]
arr[6]: [5, 4, 11, 1, 16, 8]
        
dp[6]:  [1, 1, 2,  1, 1,  1]
               ^--Change 1 to 2

(iv) For i=3, it is the similar case as (ii), so dp[3] = 1.

(v) For i=4, we will again loop for all the prev_index of 4 and we make the following observations:

    -> LIS ending at element 5 can be considered (dp[0] = 1)
    -> LIS ending at element 4 can also be considered. (dp[1] = 1)
    -> LIS ending at element 11 can also be considered. (dp[1] = 2)

Out of all these possible choices, we will consider LIS ending at element 11 because if we consider it we will have 2 elements of that  [ 5, 11] and element 16 itself, giving us a LIS of length 3, the maximum. All other options were giving a LIS of length 2.

This is the reason that we consider that prev_index whose dp[prev_index] is maximum.

i=4,dp[4]=1+dp[prev_index]
arr[6]: [5, 4, 11, 1, 16, 8]
        
dp[6]:  [1, 1, 2,  1, 3,  1]
                      ^--Change 1 to 3

Algorithm approach:

The algorithm approach can be stated as follows:

    Run an outer loop running from 0 to n-1. Every outer loop iteration will find the dp[i] value.
    Nest another loop inside it. For particular index i, this inner loop will help us to find the maximum value of dp[prev_index].

    for(int i=0;i<n;i++){
    for(int prev_index = 0; prev_index < i; prev_index++){

        }
    }

    Now inside the inner loop, we will first of all see that the element at the prev_index is smaller than the element at index i. If it is, we update dp[i] with the max(1+dp[prev_ind],dp[prev_index]).

    for(int i=0;i<n;i++){
        for(int prev_index = 0; prev_index < i; prev_index++){
            if(arr[prev_index]<arr[i]){
                dp[i] = max(1+dp[prev_ind],dp[prev_index]);
            }
        }
    }

    At last, we will loop over the dp array and return its largest value as our answer.

Time Complexity: O(N*N)

Reason: There are two nested loops.

Space Complexity: O(N)

Reason: We are only using two rows of size ‘N’.

Part 3: Printing the LIS

In order to print the LIS, we maintain a separate array along with a dp array (say hash).

Whenever we update our dp[i] value in the inner loop, we know that for index i, the previous index is prev_index. Therefore we simply store prev_index to hash[ i ]. In this way, we will have a way to trace back the LIS.

Whenever we have computed the entire dp array and we find the maximum value in it. We store that maximum value’s index in a variable ( say last_index). Now with this last_index, and the hash array we can trace back the LIS elements.

Time Complexity: O(N*N)

Reason: There are two nested loops.

Space Complexity: O(N)

Reason: We are only using two rows of size ‘N’.

*/
#include <bits/stdc++.h>
using namespace std;

int longestIncreasingSubsequence(int arr[], int n){
    
    vector<int> dp(n,1);
    
    for(int i=0; i<=n-1; i++){
        for(int prev_index = 0; prev_index <=i-1; prev_index ++){
            
            if(arr[prev_index]<arr[i]){
                dp[i] = max(dp[i], 1 + dp[prev_index]);
            }
        }
    }
    
    int ans = -1;
    
    for(int i=0; i<=n-1; i++){
        ans = max(ans, dp[i]);
    }
    
    return ans;
}

int longestIncreasingSubsequence_printing(int arr[], int n){
    
    vector<int> dp(n,1);
    vector<int> hash(n,1);
    
    for(int i=0; i<=n-1; i++){
        
        hash[i] = i; // initializing with current index
        for(int prev_index = 0; prev_index <=i-1; prev_index ++){
            
            if(arr[prev_index]<arr[i] && 1 + dp[prev_index] > dp[i]){
                dp[i] = 1 + dp[prev_index];
                hash[i] = prev_index;
            }
        }
    }
    
    int ans = -1;
    int lastIndex =-1;
    
    for(int i=0; i<=n-1; i++){
        if(dp[i]> ans){
            ans = dp[i];
            lastIndex = i;
        }
    }
    
    vector<int> temp;
    temp.push_back(arr[lastIndex]);
    
    while(hash[lastIndex] != lastIndex){ // till not reach the initialization value
        lastIndex = hash[lastIndex];
        temp.push_back(arr[lastIndex]);    
    }
    
    // reverse the array 
    reverse(temp.begin(),temp.end());
    
    cout<<"The subsequence elements are ";
    
    for(int i=0; i<temp.size(); i++){
        cout<<temp[i]<<" ";
    }
    cout<<endl;
    // for(int i=0; i<hash.size(); i++){
    //     cout<<hash[i]<<" ";
    // }
    // cout<<endl;
    
    return ans;
}

int main() {
	
	// int arr[] = {10,9,2,5,3,7,101,18};
    int arr[]= {5, 4, 11, 1, 16, 8};
	
	int n = sizeof(arr)/sizeof(arr[0]);
	
	cout<<"The length of the longest increasing subsequence is "
        <<longestIncreasingSubsequence(arr,n)<<endl;//LIS Using Tabulation Algorithm
    
    cout<<"The length of the longest increasing subsequence is "<<
    longestIncreasingSubsequence_printing(arr,n)<<endl;//Printing LIS Using Tabulation Algorithm
	
	return 0;
}