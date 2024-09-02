/*
Problem Statement: Distinct Subsequences

We are given two strings S1 and S2, we want to know how many distinct subsequences of S2 are present in S1.

Example: S1:"babgbag"    S2: "bag"
Distinct Subsequences: 5
String S2 ("bag") is present as 5 distinct subsequences in S1 ("babgbag").

"ba"bgba"g"    ba"b"g"b"ag"     babg"bag"     "ba"bgba"g"     "b"abgb"ag"

Memoization Approach
Algorithm / Intuition
We have to find distinct subsequences of S2 in S1. As there is no uniformity in data, there is no other way to find out than to try out all possible ways. To do so we will need to use recursion.

Steps to form the recursive solution: 

We will first form the recursive solution by the three points mentioned in the Dynamic Programming Introduction. 

Step 1: Express the problem in terms of indexes.

We are given two strings. We can represent them with the help of two indexes i and j. Initially, i=n-1 and j=m-1, where n and m are lengths of strings S1 and S2. Initially, we will call f(n-1,j-1), which means the count of all subsequences of string S2[0…m-1] in string S1[0…n-1]. We can generalize it as follows:

f(i,j)-> Count of all distinct subsequences of S2[0…j-1] in S1[0…i-1]

Step 2: Try out all possible choices at a given index.

Now, i and j represent two characters from strings S1 and S2 respectively. We want to find distinct subsequences. There are only two options that make sense: either the characters represented by i and j match or they don’t.

Case 1: When the characters match

if(S1[i]==S2[j]), let’s understand it with the following example:

S1: "babgbag"
           ^i
S2: "bag"
       ^j
S1[i] == S2[j], now as the characters at i and j match, we would want to check the possibility of the remaining characters of S2 in S1 therefore we reduce the length of both the strings by 1 and call the function recursively.

S1: "babgbag"
           ^i
S2: "bag"
       ^j
       /
    S1: "babgba"
              ^i
    S2: "ba"
          ^j

Now, if we only make the above single recursive call, we are rejecting the opportunities to find more than one subsequences because it can happen that the jth character may match with more characters in S1[0…i-1], for example where there are more occurrences of ‘g’ in S1 from which also an answer needs to be explored.

S1:"bab'g'bag"
           ^i
S2: "bag"
       ^j
       Answer from g (marked in '') also needs to be explored

To explore all such possibilities, we make another recursive call in which we reduce the length of the S1 string by 1 but keep the S2 string the same, i.e we call f(i-1,j).

                    S1: "babgbag"
                               ^i
                    S2: "bag"
                           ^j
                    /       \ 
            S1: "babgba"     S1: "babgba"
                      ^i               ^i
            S2: "ba"         S2: "bag"
                  ^j                ^j

Case 2: When the characters don’t match

if(S1[i] != S2[j]), it means that we don’t have any other choice than to try the next character of S1 and match it with the current character S2.

S1: "babgbak"
           ^i
S2: "bag"
       ^j
    ||
S1: "babgba"
          ^i
S2: "bag"
       ^j

This can be summarized as :

if(S1[i]==S2[j]), call f(i-1,j-1) and f(i-1,j).
if(S1[i]!=S2[j]), call f(i-1,j).
Step 3:  Return the sum of choices 

As we have to return the total count, we will return the sum of f(i-1,j-1) and f(i-1,j) in case 1 and simply return f(i-1,j) in case 2. 

Base Cases:

We are reducing i and j in our recursive relation, there can be two possibilities, either i becomes -1 or j becomes -1.

    -> if j<0, it means we have matched all characters of S2 with characters of S1, so we return 1.
    -> if i<0, it means we have checked all characters of S1 but we are not able to match all characters of S2, therefore we return 0.
The final pseudocode after steps 1, 2, and 3:

f(i,j){
     //Base Case
    if(j<0) return 1;
    if(i<0) return 0;
    //Recursive Case
    if(S1[i]==S2[j])
    return f(i-1,j-1) + f(i-1,j);
    else
    return f(i-1,j);
}

Steps to memoize a recursive solution:

If we draw the recursion tree, we will see that there are overlapping subproblems. In order to convert a recursive solution the following steps will be taken:

    -> Create a dp array of size [n][m]. The size of S1 and S2 are n and m respectively, so the variable i will always lie between ‘0’ and ‘n-1’ and the variable j between ‘0’ and ‘m-1’.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to particular parameters (say f(i,j)), we first check whether the answer is already calculated using the dp array(i.e dp[i][j]!= -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[i][j] to the solution we get.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are N*M states therefore at max ‘N*M’ new problems will be solved.

Space Complexity: O(N*M) + O(N+M)

Reason: We are using a recursion stack space(O(N+M)) and a 2D array ( O(N*M)).


Tabulation Approach
Algorithm / Intuition
In the recursive logic, we set the base case too if(i<0 ) and if(j<0) but we can’t set the dp array’s index to -1. Therefore a hack for this issue is to shift every index by 1 towards the right.

Recursive Code indexes: -1,0,1,...,n
Shifted indexes: 0,1,2,...,n+1

    -> First we initialize the dp array of size [n+1][m+1] as zero.
    -> Next, we set the base condition (keep in mind 1-based indexing), we set the first column’s value as 1 and the first row as 1.
    -> Similarly, we will implement the recursive code by keeping in mind the shifting of indexes, therefore S1[i] will be converted to S1[i-1]. Same for S2.
    -> At last, we will print dp[N][M] as our answer.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops

Space Complexity: O(N*M)

Reason: We are using an external array of size ‘N*M’. Stack Space is eliminated.

Space Optimization Approach
Algorithm / Intuition
If we closely look the relation,

dp[i][j] =  dp[i-1][j-1] + dp[i-1][j]  or dp[i][j] = dp[i-1][j]

We see that to calculate a value of a cell of the dp array, we need only the previous row values (say prev). So, we don’t need to store an entire array. Hence we can space optimize it.

We will be space-optimizing this solution using only one row.

Intuition:
If we clearly see the values required:  dp[i-1][j-1] and dp[i-1][j], we can say that if we are at a column j, we will only require the values shown in the grey box from the previous row and other values will be from the cur row itself. So why do we need to store an entire array for it?
prev(dp[ind-1][]) : [ | |*|*| | | | | ]
                          \|                  Only these two values 
cur(dp[ind][]) :    [ | | | | | | | | ]       of thetop row are required

If we need only two values from the prev row, there is no need to store an entire row. We can work a bit smarter.

We can use the cur row itself to store the required value in the following way:

    -> We take a single row ‘prev’.
    -> We initialize it to the base condition.
    -> Whenever we want to compute a value of the cell prev[j], we take the already existing value (prev[j] before new computation) and prev[j-1] (if required, in case of character match).
    -> We perform the above step on all the indexes.
    -> So we see how we can space optimize using a single row itself.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops.

Space Complexity: O(M)

Reason: We are using an external array of size ‘M+1’ to store only one row.
*/

#include <bits/stdc++.h>
using namespace std;

const int prime = 1e9 + 7;

// Function to count the number of distinct subsequences of s2 in s1
int countUtil(string s1, string s2, int ind1, int ind2, vector<vector<int>>& dp) {
    // If s2 has been completely matched, return 1 (found a valid subsequence)
    if (ind2 < 0)
        return 1;
    
    // If s1 has been completely traversed but s2 hasn't, return 0
    if (ind1 < 0)
        return 0;

    // If the result for this state has already been calculated, return it
    if (dp[ind1][ind2] != -1)
        return dp[ind1][ind2];

    int result = 0;

    // If the characters match, consider two options: either leave one character in s1 and s2
    // or leave one character in s1 and continue matching s2
    if (s1[ind1] == s2[ind2]) {
        int leaveOne = countUtil(s1, s2, ind1 - 1, ind2 - 1, dp);
        int stay = countUtil(s1, s2, ind1 - 1, ind2, dp);

        result = (leaveOne + stay) % prime;
    } else {
        // If characters don't match, just leave one character in s1 and continue matching s2
        result = countUtil(s1, s2, ind1 - 1, ind2, dp);
    }

    // Store the result and return it
    dp[ind1][ind2] = result;
    return result;
}

//Using Memoization
// Function to count the number of distinct subsequences of s2 in s1
int subsequenceCounting(string &s1, string &s2, int lt, int ls) {
    vector<vector<int>> dp(lt, vector<int>(ls, -1));
    return countUtil(s1, s2, lt - 1, ls - 1, dp);
}

//Using Tabulation
// Function to count the number of distinct subsequences of s2 in s1
int subsequenceCounting_Tab(string &s1, string &s2, int n, int m) {
    // Create a 2D DP array to store the count of distinct subsequences
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    // Initialize the first row: empty string s2 can be matched with any non-empty s1 in one way
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 1;
    }

    // Initialize the first column: s1 can't match any non-empty s2
    for (int i = 1; i <= m; i++) {
        dp[0][i] = 0;
    }

    // Fill in the DP array
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // If the characters match, we have two options:
                // 1. Match the current characters and move diagonally (dp[i-1][j-1])
                // 2. Leave the current character in s1 and match s2 with the previous characters (dp[i-1][j])
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % prime;
            } else {
                // If the characters don't match, we can only leave the current character in s1
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // The value at dp[n][m] contains the count of distinct subsequences
    return dp[n][m];
}

//Using Space Optimization
// Function to count the number of distinct subsequences of s2 in s1
int subsequenceCounting_SO(string &s1, string &s2, int n, int m) {
    // Create an array to store the count of distinct subsequences for each character in s2
    vector<int> prev(m + 1, 0);

    // Initialize the count for an empty string (base case)
    prev[0] = 1;

    // Iterate through s1 and s2 to calculate the counts
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 1; j--) { // Iterate in reverse direction to avoid overwriting values prematurely
            if (s1[i - 1] == s2[j - 1]) {
                // If the characters match, we have two options:
                // 1. Match the current characters and add to the previous count (prev[j-1])
                // 2. Leave the current character in s1 and match s2 with the previous characters (prev[j])
                prev[j] = (prev[j - 1] + prev[j]) % prime;
            }
            // No need for an else statement since we can simply leave the previous count as is
        }
    }

    // The value at prev[m] contains the count of distinct subsequences
    return prev[m];
}

int main() {
    string s1 = "babgbag";
    string s2 = "bag";

    // Call the subsequenceCounting function and print the result
    cout << "The Count of Distinct Subsequences is " << subsequenceCounting(s1, s2, s1.size(), s2.size())<< endl;//Using Memoization
    cout << "The Count of Distinct Subsequences is " << subsequenceCounting_Tab(s1, s2, s1.size(), s2.size())<< endl;//Using Tabulation
    cout << "The Count of Distinct Subsequences is " << subsequenceCounting_SO(s1, s2, s1.size(), s2.size())<< endl;//Using Space Optimization
    return 0;
}

