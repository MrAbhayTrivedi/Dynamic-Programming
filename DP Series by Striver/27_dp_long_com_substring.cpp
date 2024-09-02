/*
Problem Statement: Longest Common Substring

A substring of a string is a subsequence in which all the characters are consecutive. Given two strings, we need to find the longest common substring.

We need to print the length of the longest common substring.

Pre-req: Longest Common Subsequence, Print Longest Common Subsequence

Example:
S1:"abcjklp"   S2: "acjkp"
Longest Common Substring: "cjk"

Tabulation Approach
Algorithm / Intuition
We can modify the approach we used in the article Longest Common Subsequence, in order to find the longest common substring. The main distinguishing factor between the two is the consecutiveness of the characters.

While finding the longest common subsequence, we were using two pointers (ind1 and ind2) to map the characters of the two strings. We will again have the same set of conditions for finding the longest common substring, with slight modifications to what we do when the condition becomes true.

We will try to form a solution in the bottom-up (tabulation) approach. We will set two nested loops with loop variables i and j.

Thinking in terms of consecutiveness of characters

We have two conditions:

    -> if(S1[i-1] != S2[j-1]), the characters don’t match, therefore the consecutiveness of characters is broken. So we set the cell value (dp[i][j]) as 0.
    -> if(S1[i-1] == S2[j-1]), then the characters match and we simply set its value to 1+dp[i-1][j-1]. We have done so because dp[i-1][j-1] gives us the longest common substring till the last cell character (current strings -{matching character}). As the current cell’s character is matching we are adding 1 to the consecutive chain.
Note: dp[n][m] will not give us the answer; rather the maximum value in the entire dp array will give us the length of the longest common substring. This is because there is no restriction that the longest common substring is present at the end of both the strings.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops

Space Complexity: O(N*M)

Reason: We are using an external array of size ‘N*M)’. Stack Space is eliminated.

Space Optimization Approach
Algorithm / Intuition
If we look closely, we need values from the previous row: dp[ind-1][ ]

So we are not required to contain an entire array, we can simply have two rows prev and cur where prev corresponds to dp[ind-1] and cur to dp[ind].

After declaring prev and cur, replace dp[ind-1] to prev and dp[ind] with cur and after the inner loop executes, we will set prev = cur, so that the cur row can serve as prev for the next index.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops.

Space Complexity: O(M)

Reason: We are using an external array of size ‘M+1’ to store only two rows.
*/


#include <bits/stdc++.h>
using namespace std;

//Using Tabulation
// Function to find the length of the Longest Common Substring (LCS)
int lcs(string &s1, string &s2){
    int n = s1.size();
    int m = s2.size();
    
    // Create a 2D DP table with dimensions (n+1) x (m+1)
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

    int ans = 0; // Initialize the answer variable

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s1[i-1] == s2[j-1]){
                int val = 1 + dp[i-1][j-1]; // Characters match, increment substring length
                dp[i][j] = val; // Update the DP table
                ans = max(ans, val); // Update the maximum substring length found so far
            }
            else
                dp[i][j] = 0; // Characters don't match, substring length becomes 0
        }
    }
    
    return ans; // Return the length of the Longest Common Substring
}

//Using  Space Optimization
// Function to find the length of the Longest Common Substring (LCS)
int lcs_SO(string &s1, string &s2){
    int n = s1.size();
    int m = s2.size();
    
    // Initialize two vectors to store previous and current row values
    vector<int> prev(m+1, 0); // Stores values of the previous row
    vector<int> cur(m+1, 0);  // Stores values of the current row

    int ans = 0; // Initialize the answer variable to store the maximum LCS length found
    
    // Loop through both strings
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(s1[i-1] == s2[j-1]){
                int val = 1 + prev[j-1]; // Characters match, increment substring length
                cur[j] = val; // Update the current row with the new value
                ans = max(ans, val); // Update the maximum substring length found so far
            }
            else
                cur[j] = 0; // Characters don't match, substring length becomes 0
        }
        prev = cur; // Update the previous row with the values of the current row
    }
    
    return ans; // Return the length of the Longest Common Substring
}

int main() {
    string s1 = "abcjklp";
    string s2 = "acjkp";

    // Call the function to find and output the length of the Longest Common Substring
    cout << "The Length of Longest Common Substring is " << lcs(s1, s2) << endl;//Using Tabulation
    cout << "The Length of Longest Common Substring is " << lcs_SO(s1, s2) << endl;//Using Space Optimization


    return 0; // Return 0 to indicate successful program execution
}


