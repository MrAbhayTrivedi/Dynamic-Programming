/*
Longest Palindromic Subsequence

A palindromic string is a string that is equal to its reverse. For example: “Nitin” is a palindromic string. Now the question states to find the length of the longest palindromic subsequence of a string. It is that palindromic subsequence of the given string with the greatest length. We need to print the length of the longest palindromic subsequence.

Example:
str:"bbbab"

Longest Palindromic Subsequence:"bbbb"
There can be many subsequences like "b", "ba", "bb", "bbab", "bbba" etc. But the longest palindromic subsequence is "bbbb".

Tabulation Approach
Algorithm / Intuition
We are given a string S, the simplest approach will be to generate all the subsequences and store them, then manually find out the longest palindromic subsequence.

This naive approach will give us the correct answer but to generate all the subsequences, we will require exponential ( 2n ) time. Therefore we will try some other approaches.

Using Dynamic Programming

We can use the approach discussed in the article Longest Common Subsequence, to find the Longest Palindromic Subsequence.

Intuition:

Let us say that we are given the following string.

str: "bbabcbcab"

The longest palindromic subsequence will be: “babcbab”.

What is special about this string is that it is palindromic (equal to its reverse) and of the longest length.

Now let us write the reverse of str next to it and please think about the highlighted characters.

str: "bbabcbcab"
      _ ____ __
rev(str): "bacbcbabb"
           __ ____

If we look closely at the highlighted characters, they are nothing but the longest common subsequence of the two strings.

Now, we have taken the reverse of the string for the following two reasons:

    The longest palindromic subsequence being a palindrome will remain the same when the entire string is reversed.
    The length of the palindromic subsequence will also remain the same when the entire string is reversed.

From the above discussion we can conclude:

The longest palindromic subsequence of a string is the longest common subsequence of the given string and its reverse.

Approach:

The algorithm is stated as follows:

    -> We are given a string (say s), make a copy of it and store it( say string t).
    -> Reverse the original string s.
    -> Find the longest common subsequence as discussed in dp-25.

Complexity Analysis
Time Complexity: O(N*N)

Reason: There are two nested loops

Space Complexity: O(N*N)

Reason: We are using an external array of size ‘(N*N)’. Stack Space is eliminated.

Space Optimization Approach
Algorithm / Intuition
If we closely we are using two rows: dp[ind1-1][ ], dp[ind][ ],

So we are not required to contain an entire array, we can simply have two rows prev and cur where prev corresponds to dp[ind-1] and cur to dp[ind].

After declaring prev and cur, replace dp[ind-1] to prev and dp[ind] with cur and after the inner loop executes, we will set prev = cur, so that the cur row can serve as prev for the next index.

Complexity Analysis
Time Complexity: O(N*N)

Reason: There are two nested loops.

Space Complexity: O(N)

Reason: We are using an external array of size ‘N+1’ to store only two rows.
*/


#include <bits/stdc++.h>
using namespace std;

// Function to calculate the length of the Longest Common Subsequence
int lcs(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    // Create a 2D DP array to store the length of the LCS
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

    // Initialize the first row and first column to 0
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = 0;
    }

    // Fill in the DP array
    for (int ind1 = 1; ind1 <= n; ind1++) {
        for (int ind2 = 1; ind2 <= m; ind2++) {
            if (s1[ind1 - 1] == s2[ind2 - 1])
                dp[ind1][ind2] = 1 + dp[ind1 - 1][ind2 - 1];
            else
                dp[ind1][ind2] = max(dp[ind1 - 1][ind2], dp[ind1][ind2 - 1]);
        }
    }

    // The value at dp[n][m] contains the length of the LCS
    return dp[n][m];
}

//Using Tabulation
// Function to calculate the length of the Longest Palindromic Subsequence
int longestPalindromeSubsequence(string s) {
    // Create a reversed copy of the string
    string t = s;
    reverse(s.begin(), s.end());

    // Call the LCS function to find the length of the Longest Common Subsequence
    return lcs(s, t);
}

// Function to calculate the length of the Longest Common Subsequence
int lcs_SO(string s1, string s2) {
    int n = s1.size();
    int m = s2.size();

    // Create two arrays to store the previous and current rows of DP values
    vector<int> prev(m + 1, 0), cur(m + 1, 0);

    // Base Case is covered as we have initialized the prev and cur to 0.

    for (int ind1 = 1; ind1 <= n; ind1++) {
        for (int ind2 = 1; ind2 <= m; ind2++) {
            if (s1[ind1 - 1] == s2[ind2 - 1])
                cur[ind2] = 1 + prev[ind2 - 1];
            else
                cur[ind2] = max(prev[ind2], cur[ind2 - 1]);
        }
        // Update the prev array with the current values
        prev = cur;
    }

    // The value at prev[m] contains the length of the LCS
    return prev[m];
}

//Using Space Optimization
// Function to calculate the length of the Longest Palindromic Subsequence
int longestPalindromeSubsequence_SO(string s) {
    // Create a reversed copy of the string
    string t = s;
    reverse(s.begin(), s.end());

    // Call the LCS function to find the length of the Longest Common Subsequence
    return lcs_SO(s, t);
}

int main() {
    string s = "bbabcbcab";

    // Call the longestPalindromeSubsequence function and print the result
    cout << "The Length of Longest Palindromic Subsequence is " << longestPalindromeSubsequence(s)<< endl;//Using Tabulation
    cout << "The Length of Longest Palindromic Subsequence is " << longestPalindromeSubsequence_SO(s)<< endl;//Using Space Optimization
    return 0;
}


