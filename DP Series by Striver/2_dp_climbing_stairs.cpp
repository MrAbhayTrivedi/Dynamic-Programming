/*
Dynamic Programming : Climbing Stairs

How to write 1-D Recurrence relation / Climbing Stairs

Problem Statement: Given a number of stairs. Starting from the 0th stair we need to climb to the “Nth” stair. At a time we can climb either one or two steps. We need to return the total number of distinct ways to reach from 0th to Nth stair.

            ___3
        ___|
    ___|
___|
0
1st: 0th stair to 1st stair->1st stair to 2nd stair->2nd stair to 3rd stair
2nd: 0th stair to 2nd stair->2nd stair to 3rd stair
3rd: 0th stair to 1st stair->1st stair to 3rd stair
Given N=3, ther are 3 distinct ways to reach from 0th to 3rd stair.

Solution :
How to Identify a DP problem?

When we see a problem, it is very important to identify it as a dynamic programming problem. Generally (but not limited to) if the problem statement asks for the following:

Count the total number of ways
Given multiple ways of doing a task, which way will give the minimum or the maximum output.
We can try to apply recursion. Once we get the recursive solution, we can go ahead to convert it to a dynamic programming one.

Steps To Solve The Problem After Identification

Once the problem has been identified, the following three steps comes handy in solving the problem:

    Try to represent the problem in terms of indexes.
    Try all possible choices/ways at every index according to the problem statement.
    If the question states
        Count all the ways - return sum of all choices/ways.
        Find maximum/minimum- return the choice/way with maximum/minimum output.

Using these steps to solve the problem “Climbing Stairs”

Step 1: We will assume n stairs as indexes from 0 to N.
            ___N
        ___|.
    ___|2
___|1
0
Step 2: At a single time, we have 2 choices: Jump one step or jump two steps. We will try both of these options at every index.

Step 3: As the problem statement asks to count the total number of distinct ways, we will return the sum of all the choices in our recursive function.

The base case will be when we want to go to the 0th stair, then we have only one option.

The basic pseudo-code for the problem will be given as:
f(ind){
    if(ind==0)return 1
    return f(ind-1)+f(ind-2)
}
There will be one more edge-case when n=1, if we call f(n-2) we will reach stair numbered -1 which is not defined, therefore we add an extra test case to return 1 ( the only way) when n=1.
f(ind){
    if(ind==0)return 1
    if(ind==1)return 1
    return f(ind-1)+f(ind-2)
}

If we clearly observe the pseudo-code, we see that it almost matches the problem “fibonacci numbers” discussed in Dynamic Programming Introduction ! So the readers can follow that article to understand the approach used for the dynamic programming solution after the recursive solution.

Steps for the Tabulation approach.

    -> Declare a dp[] array of size n+1.
    -> First initialize the base condition values, i.e i=0 and i=1 of the dp array as 1.
    -> Set an iterative loop that traverses the array( from index 2 to n) and for every index set its value as dp[i-1] + dp[i-2].

Time Complexity: O(N)

Reason: We are running a simple iterative loop

Space Complexity: O(N)

Reason: We are using an external array of size ‘n+1’.

Part 3: Space Optimization

If we closely look the relation,

dp[i] =  dp[i-1] + dp[i-2]

we see that for any i, we do need only the last two values in the array. So is there a need to maintain a whole array for it?

The answer is ‘No’. Let us call dp[i-1] as prev and dp[i-2] as prev2.

Each iteration’s cur_i and prev becomes the next iteration’s prev and prev2 respectively.
Therefore after calculating cur_i, if we update prev and prev2 according to the next step, we will always get the answer.
After the iterative loop has ended we can simply return prev as our answer.

Time Complexity: O(N)

Reason: We are running a simple iterative loop

Space Complexity: O(1)

Reason: We are not using any extra space.
*/
#include <bits/stdc++.h>

using namespace std;

int main()
{
    //Using Tabulation
    int n = 3;
    vector<int> dp(n + 1, -1);

    dp[0] = 1;
    dp[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    cout << dp[n]<<endl;

    //Using Space Optimization
    int prev2 = 1;
    int prev = 1;

    for (int i = 2; i <= n; i++)
    {
        int cur_i = prev2 + prev;
        prev2 = prev;
        prev = cur_i;
    }
    cout << prev<<endl;
    return 0;
}