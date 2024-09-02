/*
Problem Statement: Wildcard Matching

We are given two strings ‘S1’ and ‘S2’. String S1 can have the following two special characters:

    -> ‘?’ can be matched to a single character of S2.
    -> ‘*’ can be matched to any sequence of characters of S2. (sequence can be of length zero or more).
We need to check whether strings S1 and S2 match or not.

Example:
S1:"?ay"      Matches
S2:"ray"
We can replace '?' with 'r' and string S1 and S2 will become equal.

S1:"**abcd"      Matches
S2:"abcd"
We can replace "*" of S1 at index 0 and 1 with '' (sequence of length 0).

S1: "ab*cd"      Matches
S2:"abdefcd"
We can replace "*" of S1 at index 2 with 'def'

S1: "ab?d"
S2:"abcc"     Not Match
Character 'd' at index 3 of S1 cannot be matched with character 'c' at index 3 of S2.

Memoization Approach
Algorithm / Intuition
Intuition:
For every index of string S1, we have different options to match that index with string S2. Therefore, we can think in terms of string matching path as we have done already in previous questions.

    -> Either the characters match already.
    -> Or, if there is a ‘?’, we can explicitly match a single character.
    -> For a ‘*’, the following figure explains the scenario.

                        S1: "ab*|cd"
                        S2: "abdef|cd"
                        /  /  |  \  \  \
                       /  /   |   \  \   Match '*' with "abdef"
    Match '*' with ""    /    |    \   Match '*' with "bdef"
        Match '*' with "f"    |   Match '*' with "def"
                  Match '*' with "ef"
                     Try all possible ways

As there is no uniformity in data, there is no other way to find out than to try out all possible ways. To do so we will need to use recursion.

Steps to form the recursive solution:

We will first form the recursive solution by the three points mentioned in the Dynamic Programming Introduction.

Step 1: Express the problem in terms of indexes.

We are given two strings. We can represent them with the help of two indexes i and j. Initially, i=n-1 and j=m-1, where n and m are lengths of strings S1 and S2. Initially, we will call f(n-1,m-1), which means whether string S1[0…n-1] matches with string S2[0…m-1].

We can generalize this as follows:

f(i,j)->Return whether string S1[0…i] matches with string S2[0…j] or not.

Step 2: Try out all possible choices at a given index.

Now, i and j represent two characters from strings S1 and S2 respectively. There are only two options that make sense: either the characters represented by i and j match or they don’t.

(i) When the characters match

if(S1[i]==S2[j]),

If this is true, the characters at i and j match, we can simply move to the next characters of both the strings. So we will just decrement both i and j by 1 and recursively find the answer for the remaining string portions. We return f(i-1,j-1). The following figure makes it clear.
         i
S1: "ab*cd"
S2: "abdefcd"
           j
    ||  i
S1: "ab*c"
S2: "abdefc"
          j

(ii) When the characters don’t match

If the characters don’t match, there are three possible scenarios:

    -> S1[i] == ‘?’
    -> S1[i] == ‘*’
    -> S1[i] is some other character
Let us discuss them one by one:

(i) If S1[i] == ‘?’

In this case, we can explicitly match ‘?’ at index i of S1 with the corresponding character at index j of S2. And then recursively call f(i-1,j-1) to check for the remaining string.

(ii) If S1[i] == ‘*’

This is an interesting case as now ‘*’ can be replaced with any sequence of characters( of length 0 or more) from S2.

We will revisit this example:

                        S1: "ab*|cd"
                        S2: "abdef|cd"
                        /    /  |  \  \  \
                       /    /   |   \  \   Replace & Match  '*' with "abdef"
Replace & Match '*' with ""/    |    \   Replace & Match  '*' with "bdef"
Replace & Match  '*' with "f"   |      Replace & Match  '*' with "def"
                  Replace & Match  '*' with "ef"
                     Try all possible ways

If any of these cases return true, we can say that the characters do match. The next question is how to try all possible ways?

We are using two pointers i and j to represent characters of strings S1 and S2. We can surely write a for loop to compare characters from 0 to j of S2 for the above scenario. Can we do it more smartly? Yes, we can. Please understand the approach explained below.

We are using a recursive function f(i,j). If we do only the following two recursive calls:

    -> Call f(i-1,j). i.e replace ‘*’ with nothing and act as if it was not present.
    -> Call f(i,j-1). i.e replace ‘*’ with a single character at index j and make the i pointer to still point at index i. In this, we matched it with a single character (one of the many options that need to be tried) and in the next recursive call, as i still point to ‘*’, we get the exact two recursive calls again.
The following recursive tree will help us to understand the recursion better.
                                i            j
                          S1:"ab*"  S2: "abdef"
                                 /  \
             i          j             i          j
        S1:"ab" S2:"abdef"      S1:"ab*"  S2:"abde"
                                    /   \
                             i         j            i         j
                        S1:"ab" S2:"abde"     S1:"ab*"  S2:"abd"
                                                    /   \
                                             i        j          i        j
                                        S1:"ab" S2:"abd"   S1:"ab*"  S2:"ab"
                                                                 /   \
                                                     i       j             i       j
                                                S1:"ab" S2:"ab"      S1:"ab*"  S2:"a"
                                                      |                  \
                                                S1:"a" S2:"a"             So on...
                                                      |
                                                S1:"" S2:""

So we see how we can tackle all the required cases associated with ‘*’ by using recursion.

(iii) If S1[i] is neither ‘?’ nor ‘*’, then we can say as the characters at i and j don’t match then the strings don’t match, so we return false.

To summarise:

    -> If S1[i] == ‘?’, return f(i-1,j)
    -> Else if S1[i] == ‘*’, return f(i-1,j) || f(i,j-1)
    -> Else return false
Step 3: Return logical OR (||) of all the choices

If any of the cases return true, we can say that strings do match. We can use OR operator (||) with the recursive calls.

Base Cases:

We are reducing i and j in our recursive relation, there can be two possibilities, either i becomes -1 or j becomes -1., i,e we exhaust either S1 or S2 respectively.

(i) When S1 is exhausted:

When S1 is exhausted (i<0), we know that in order for the strings to match, String S2 should also exhaust simultaneously. If it does, we return true, else we return false.

We can say:

if(i<0 && j<0), return true.
if(i<0 && j>=0), return false.
(ii) When S2 is exhausted:

When S2 is exhausted(j<0) and S1 has not, there is only one pattern that can account for true(matching of strings). It is if S1 is like this “*”,”****”,”***”, i.e: S1 contains only stars. Then we can replace every star with a sequence of length 0 and say that the string match.

If S1 is all-stars, we return true, else return false.

The final pseudocode after steps 1, 2, and 3:

f(i,j){
    // Base cases
    if(i<0 && j<0) return true;
    if(i<0 && j>=0) return false;
    if(i>=0 && j<0)
        return all_stars(S1,i);
    // Recursive calls
    if(S1[i]==S2[j] || S1[i]=='?')
    return f(i-1,j-1);
    if(S1[i]=='*')
    return f(i-1,j) || f(i,j-1);
    else return false;
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

     Recursive code indexes: -1, 0, 1,..,n
     Shifted indexes: 0, 1, 2,...,n+1


    -> First we initialise the dp array of size [n+1][m+1] as zero.
    -> Next, we set the base condition (keep in mind 1-based indexing), we set the top-left cell as ‘true’, then we set the first column’s value as ‘false’; and for the first row, we will run isAllStars() for every cell value.
    -> Similarly, we will implement the recursive code by keeping in mind the shifting of indexes, therefore S1[i] will be converted to S1[i-1]. Same for S2.
    -> At last we will print dp[n][m] as our answer.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops

Space Complexity: O(N*M)

Reason: We are using an external array of size ‘N*M’. Stack Space is eliminated.

Space Optimization Approach
Algorithm / Intuition
If we closely look the relation,

dp[i][j] =  dp[i-1][j-1], dp[i][j] = dp[i-1][j] ||dp[i][j-1]

We see that to calculate a value of a cell of the dp array, we need only the previous row values (say prev) and current row’s previous columns values. So, we don’t need to store an entire array. Hence we can space optimise it.

Approach:

We will space optimize in the following way:

    -> We take two rows ‘prev’ and ‘cur’.
    -> We initialize it to the base condition. We first initialize the prev row. Its first value needs to be true. Rest all the values of the prev row meeds to be false.
    -> Moreover, the cur variable whenever declared should have its first cell’s value given by isAllStarts() function.
    -> Next, we implement the memoization logic. We replace dp[i-1] with prev and dp[i] by cur.
    -> After every inner loop execution, we set prev=cur, for the next iteration.
    -> At last, we return prev[m] as our answer.

Complexity Analysis
Time Complexity: O(N*M)

Reason: There are two nested loops.

Space Complexity: O(M)

Reason: We are using an external array of size ‘M+1’ to store two rows.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to check if a substring of S1 contains only '*'
bool isAllStars(string &S1, int i)
{
    for (int j = 0; j <= i; j++)
    {
        if (S1[j] != '*')
            return false;
    }
    return true;
}

// Function to check if S1 matches S2 using wildcard pattern matching
bool wildcardMatchingUtil(string &S1, string &S2, int i, int j, vector<vector<bool>> &dp)
{
    // Base Cases
    if (i < 0 && j < 0)
        return true;
    if (i < 0 && j >= 0)
        return false;
    if (j < 0 && i >= 0)
        return isAllStars(S1, i);

    // If the result for this state has already been calculated, return it
    if (dp[i][j] != -1)
        return dp[i][j];

    // If the characters at the current positions match or S1 has a '?'
    if (S1[i] == S2[j] || S1[i] == '?')
        return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j - 1, dp);
    else
    {
        if (S1[i] == '*')
            // Two options: either '*' represents an empty string or it matches a character in S2
            return dp[i][j] = wildcardMatchingUtil(S1, S2, i - 1, j, dp) || wildcardMatchingUtil(S1, S2, i, j - 1, dp);
        else
            return false;
    }
}

// Using Memoization
//  Main function to check if S1 matches S2 using wildcard pattern matching
bool wildcardMatching(string &S1, string &S2)
{
    int n = S1.size();
    int m = S2.size();

    // Create a DP table to memoize results
    vector<vector<bool>> dp(n, vector<bool>(m, -1));
    return wildcardMatchingUtil(S1, S2, n - 1, m - 1, dp);
}

// Function to check if a substring of S1 contains only '*'
bool isAllStars_Tab(string &S1, int i)
{
    // S1 is taken in 1-based indexing
    for (int j = 1; j <= i; j++)
    {
        if (S1[j - 1] != '*')
            return false;
    }
    return true;
}

// Using Tabulation
//  Function to perform wildcard pattern matching between S1 and S2
bool wildcardMatching_Tab(string &S1, string &S2)
{
    int n = S1.size();
    int m = S2.size();

    // Create a DP table to memoize results
    vector<vector<bool>> dp(n + 1, vector<bool>(m, false));

    // Initialize the first row and column
    dp[0][0] = true;
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = isAllStars_Tab(S1, i);
    }

    // Fill in the DP table
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (S1[i - 1] == S2[j - 1] || S1[i - 1] == '?')
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                if (S1[i - 1] == '*')
                {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                }
                else
                {
                    dp[i][j] = false;
                }
            }
        }
    }

    // The value at dp[n][m] contains whether S1 matches S2
    return dp[n][m];
}

// Function to check if a substring of S1 contains only '*'
bool isAllStars_SO(string &S1, int i)
{
    // S1 is taken in 1-based indexing
    for (int j = 1; j <= i; j++)
    {
        if (S1[j - 1] != '*')
            return false;
    }
    return true;
}

// Using Space Optimization
//  Function to perform wildcard pattern matching between S1 and S2
bool wildcardMatching_SO(string &S1, string &S2)
{
    int n = S1.size();
    int m = S2.size();

    // Create two arrays to store previous and current rows of matching results
    vector<bool> prev(m + 1, false);
    vector<bool> cur(m + 1, false);

    prev[0] = true; // Initialize the first element of the previous row to true

    for (int i = 1; i <= n; i++)
    {
        cur[0] = isAllStars_SO(S1, i); // Initialize the first element of the current row
        for (int j = 1; j <= m; j++)
        {
            if (S1[i - 1] == S2[j - 1] || S1[i - 1] == '?')
            {
                cur[j] = prev[j - 1]; // Characters match or S1 has '?'
            }
            else
            {
                if (S1[i - 1] == '*')
                {
                    cur[j] = prev[j] || cur[j - 1]; // '*' represents empty or a character
                }
                else
                {
                    cur[j] = false; // Characters don't match and S1[i-1] is not '*'
                }
            }
        }
        prev = cur; // Update the previous row with the current row
    }

    // The value at prev[m] contains whether S1 matches S2
    return prev[m];
}

int main()
{
    string S1 = "ab*cd";
    string S2 = "abdefcd";

    // Call the wildcardMatching function and print the result
    // Using Memoization
    if (wildcardMatching(S1, S2))
        cout << "String S1 and S2 do match";
    else
        cout << "String S1 and S2 do not match";

    cout << endl;
    // Using Tabulation
    if (wildcardMatching_Tab(S1, S2))
        cout << "String S1 and S2 do match";
    else
        cout << "String S1 and S2 do not match";
    cout << endl;

    // Using Space Optimization
    if (wildcardMatching_SO(S1, S2))
        cout << "String S1 and S2 do match";
    else
        cout << "String S1 and S2 do not match";

    return 0;
}
