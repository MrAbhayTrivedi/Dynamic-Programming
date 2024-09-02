/*
Palindrome Partitioning - II | Front Partition

Problem Statement: Given a string s, partition s such that every substring of the partition is a palindrome. Return the minimum cuts needed for a palindrome partitioning of s.


Example 1:
Input:s = “bababcbadcede”
Output: 4
Explanation:If we do 4 partitions in the following way, each substring of the partition will be a palindrome.
bab | abcba | d | c | ede

Input: s = "aab"
Output: 1
Explanation: If we do 1 partition in the following way, each substring of the partition will be a palindrome.
aa | b

Recursive Approach
Algorithm / Intuition
In order to solve this problem, we need to partition the given string in such a way that every substring of the partition becomes a palindrome. For example, if the string “aabb” is given, one of the valid partitions will be “aa | b | b”. 

Now, one key point to notice here is that we can make every substring of any string a palindrome, by partitioning it n-1 times(where n = size of the string). For example, if the given string is “abcd” and if we partition it n-1 i.e. (4-1 = 3) times, it will be like the following:
a | b | c | d. Here, every single substring of the partitions is a palindrome.

So, we can conclude that it is very much possible all the time to partition a string in such a way that every substring becomes a palindrome and we can also assure that the answer always exists. 

Here, in this question, it is clearly mentioned that we need to figure out the minimum number of such partitions. Consider the example given below:

The string "aabb" can be partitioned in many ways like :
         a|a|bb(2 partitions needed)
         aa|bb (1 partition needed)
         aa|b|b(2 partitions needed)
         a|a|b|b(3 partitions needed)...
Among all these cases, in the second one we need the minimum partitions i.e. 1 partition . So our answer will be 1.

Intuition:
This type of problem is generally solved using the front partition. Following the front partition technique, we will start checking from the first index of the given string and will check if we can make a partition between the first and the second index. Similarly, then we will include the second index in the account and check if we can make a partition between the second and the third index. This process will continue to the last index. 

The condition for a partition to be valid is that the left part of the partition must be a palindromic substring. 

The following illustration will depict the process of partitioning:

                f(bababcbadcede)
                /         \      \
    b|ababcbadcede bab|abcbadcede babab|cbadcede
    1+f(ababcbadcede) 1+f(abcbadcede) 1+f(cbadcede)
    /  \ ..               /  \ ..         / \..

We have found the right approach so far. Now, let us quickly discuss the rules to solve this problem:

    -> Express everything(i.e. the given string) in terms of the index.
    -> Try all partitions.
    -> Return the best possible answer of all partitions (the answer that comes after dividing the problem into subproblems and solving them recursively).

Derive the base case as well.
Express everything(i.e. the given string) in terms of the index:

We are given a string. Now, following the front partition rules we will place i to index 0 i.e. the first index. The function will look like the following:

bababcbadcede    => f(i){}
i

Try all partitions:
As we have figured out the logic for marking the pointer, i, we will move to the partitioning loop. We can simply write a for loop(say j) starting from i to n-1(n = size of the string), The problem is being broken in the following manner:

                f(bababcbadcede)
                /         \      \
    b|ababcbadcede bab|abcbadcede babab|cbadcede
    1+f(ababcbadcede) 1+f(abcbadcede) 1+f(cbadcede)
    /  \ ..               /  \ ..         / \..

Base case: When the index i will be equal to the size of the string(i.e. i == n), we can say there are no more characters left to be partitioned. So, this is the base case and in this case, the function will return 0.

f(i){
    if(i == n)
        return 0;//Base case
    for(j = i; j < n; j++){
        //Check if the partition is possible
    }
}

Return the best possible answer of all partitions:
A partition is possible when the left substring of that partition is a palindrome. Now, inside the partitioning loop, we will check if the partition can be done at index j(i.e. We will check if the substring starts from index i and ends at index j is a palindrome or not). If it is done, we will add 1 to our answer, and then we will again follow the same method for the left-over substring.

Here, in the question, it is clearly mentioned that we need the minimum number of partitions. So, calculating all possible answers using the above method, we will take the minimum into our consideration.

The recurrence logic will be the following:

f(i,s){
    if(i == n)
        return 0;//Base case
    int minCost = INT_MAX;//minimum partition
    for(j = i; j < n; j++){
        //Check if the partition is possible
        if(isPalindrome(s,i, j)){
            int cost = 1 + f(j+1, s);
            minCost = min(minCost, cost);
        }
    }
    return minCost;
}

Note about the final answer:
If we carefully observe, we can notice that our function is actually counting an extra partition at the end of the string in each case. For example, the given string is “abcd”. After doing a partition after ‘c’ the function will check if a partition can be done after ‘d’ to check if the last substring i.e. ‘d’ itself is a palindrome. Consider the following illustration:

a|b|c|d|
       ^---Extra partition

For that our function will return 4 as the answer, instead of the actual answer is 3. 

So, our actual answer will be (number of partitions returned by the function - 1).

Approach: 

The recursive algorithm steps are as follows:

    -> Convert the problem to a recursive function marked by the pointer i.
    -> Use a loop to check all possible partitions of the string and calculate the number of partitions.
    -> Return the minimum number of partitions counted.
    -> Base case: When the index i will be equal to the size of the string(i.e. i == n), we can say there are no more characters left to be partitioned. So, this is the base case and in this case, the function will return 0.

Complexity Analysis
Time Complexity: Exponential

Memoization Approach
Algorithm / Intuition
Steps to memoize the recursive solution:

    -> Create a 1D dp array of size [n] i can range from 0 to n-1. So we take the size n.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to a particular parameter (say f(i)), we first check whether the answer is already calculated using the dp array(i.e dp[i] != -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[i] to the solution we get.

Complexity Analysis
Time Complexity: O(N2)
Reason: There are a total of N states and inside each state, a loop of size N(apparently) is running.

Space Complexity: O(N) + Auxiliary stack space O(N)
Reason: The first O(N) is for the dp array of size N.

Tabulation Approach
Algorithm / Intuition
Tabulation:

    -> First of all, we handle the base case. If (i == n) we return 0. To cover this case we can initialize the entire dp array with 0.
    -> Here, as we are checking dp[j+1]  every time, the function will give a runtime error if j = n-1. To avoid this, we will take the array size as n+1 instead of n.
    -> Next, memoization is a top-down approach, whereas tabulation is bottom-up. Our changing parameter i will change in opposite directions, i.e i will change from n-1→0.
    -> Next, we copy down the recursive logic(recurrence) inside the loop.

Complexity Analysis
Time Complexity: O(N2)
Reason: There are a total of N states and inside each state a loop of size N(apparently) is running.

Space Complexity: O(N)
Reason: O(N) is for the dp array we have used.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to check if a substring is a palindrome.
bool isPalindrome(int i, int j, string &s) {
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++;
        j--;
    }
    return true;
}

// Recursive function to find the minimum number of partitions to make palindromes.
int minPartitions(int i, int n, string &str) {
    // Base case: If we've reached the end of the string.
    if (i == n) return 0;

    int minCost = INT_MAX;
    // Consider all possible substrings starting from the current index.
    for (int j = i; j < n; j++) {
        if (isPalindrome(i, j, str)) {
            // If the substring is a palindrome, calculate the cost and minimize it.
            int cost = 1 + minPartitions(j + 1, n, str);
            minCost = min(minCost, cost);
        }
    }
    return minCost;
}


//Using Recursion
// Main function to find the minimum number of partitions for palindrome partitioning.
int palindromePartitioning(string str) {
    int n = str.size();
    // Calling the recursive function and subtracting 1 as it counts partitions, not cuts.
    return minPartitions(0, n, str) - 1;
}

// Recursive function to find the minimum number of partitions to make palindromes.
int minPartitions(int i, int n, string &str, vector<int> &dp) {
    // Base case: If we've reached the end of the string.
    if (i == n) return 0;

    if (dp[i] != -1) return dp[i];
    int minCost = INT_MAX;
    // Consider all possible substrings starting from the current index.
    for (int j = i; j < n; j++) {
        if (isPalindrome(i, j, str)) {
            // If the substring is a palindrome, calculate the cost and minimize it.
            int cost = 1 + minPartitions(j + 1, n, str, dp);
            minCost = min(minCost, cost);
        }
    }
    return dp[i] = minCost;
}

//Using Memoization
// Main function to find the minimum number of partitions for palindrome partitioning.
int palindromePartitioning_Memo(string str) {
    int n = str.size();
    vector<int> dp(n, -1);
    // Calling the recursive function and subtracting 1 as it counts partitions, not cuts.
    return minPartitions(0, n, str, dp) - 1;
}

//USing Tabulation
// Function to find the minimum number of partitions for palindrome partitioning.
int palindromePartitioning_Tab(string str) {
    int n = str.size();
    // Create a DP array to store the minimum number of partitions.
    vector<int> dp(n + 1, 0);
    dp[n] = 0; // Initialize the last element to 0.

    // Loop through the string in reverse order.
    for (int i = n - 1; i >= 0; i--) {
        int minCost = INT_MAX;
        // Consider all possible substrings starting from the current index.
        for (int j = i; j < n; j++) {
            if (isPalindrome(i, j, str)) {
                // If the substring is a palindrome, calculate the cost and minimize it.
                int cost = 1 + dp[j + 1];
                minCost = min(minCost, cost);
            }
        }
        dp[i] = minCost;
    }
    // Subtract 1 as it counts partitions, not cuts.
    return dp[0] - 1;
}

int main() {
    string str = "BABABCBADCEDE";
    cout << "The minimum number of partitions: " <<palindromePartitioning(str)<< "\n";//Using Recursion
    cout << "The minimum number of partitions: " <<palindromePartitioning_Memo(str)<< "\n";//Using Memoization
    cout << "The minimum number of partitions: " <<palindromePartitioning_Tab(str) << "\n";//Using Tabulation
    
    return 0;
}

