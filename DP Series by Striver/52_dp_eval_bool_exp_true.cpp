/*
Evaluate Boolean Expression to True

Problem Statement: Given an expression, A, with operands and operators (OR, AND, XOR), in how many ways can you evaluate the expression to be true, by grouping it in different ways?

Operands are only true and false.

Return the number of ways to evaluate the expression modulo 103 + 3.

Pre-requisite: DP-48, DP-49, DP-50, DP-51

Example 1:
Input:expression = “T|T&F”
Output: 1
Explanation: The only way to get the result as true is:(T) | (T&F) = T|F = T 
Example 2:
Input: expression = “F|T^F”
Output: 2
Explanation: There are 2 possible ways to get the result as true:
		i) (F|T) ^ F = T ^ F = T
		ii) F | (T^F) = F | T = T

Recursive Approach
Algorithm / Intuition
In the question, it is clearly stated, that the operands are only ‘true’ and ‘false’, and the operators are AND(&), OR(|), and XOR(^).

If we carefully observe, we can easily understand that the given expression can be solved in several ways. And through several ways, we can achieve different results. For example, if the expression, “T|T&F” is given, we can solve it in two different ways like the following:

    -> (T | T) & F = T & F = F. This method gives the result false.
    -> (T) | (T & F) = T | F = T. This method gives the result true.

But here, we are concerned only with the ways, through which we can achieve the result of the expression as true. So, for the above example, we will only consider the second approach. Now, in order to solve the problem, we have to figure out the total no. of such ways through which we can get ‘true’ as our answer.

Observation:
Let’s consider the following expression:

T^F|T&F^T|F

If we carefully observe, we can easily notice that the given expression both starts and ends with an operand and the expression also follows a certain pattern i.e. an operand followed by an operator.

Now, this expression can be primarily partitioned in the following possible ways:

(T)^(F|T&F^T|F)          (T^F)|(T&F^T|F)
(T^F|T)&(F^T|F)          (T^F|T&F)^(T|F)
              (T^F|T&F^T)|(F)

From this illustration, we can easily conclude that the number of partitions we can make equals the number of operators that the expression contains. And we can also assume the left side of each operator is the left subproblem and the right side signifies the right subproblem.
Now, each subproblem can be again divided into multiple subproblems in similar ways. For example, the given expression can be divided into subproblems like the following:
                T^F|T&F^T|F
 Left subproblem/       \Right subproblem
              (T)^(F|T&F^T|F)
                    /  \
                      .
                      .
                      .  More subproblems

Now, we are getting a pattern of dividing the whole expression into smaller subproblems. If we continue to divide the expression, at some point we will get a single operand left.

Intuition: 
The intuition is to divide the expression into subproblems and we will break the expression at the position of the operators. 

We have found the right approach until now. Now, let us quickly revise the rules to solve a problem on partition dp.

    -> Start with the entire block/array/expression and mark it with i, j.
    -> Try all partitions.
    -> Return the best possible answer of the two partitions (the answer that comes after dividing the problem into two subproblems and solving them recursively).

Now let us go through these rules and apply them to this problem.

Marking the expression with i, j:

We are given a string or an expression. The entire expression basically represents the range. So, we will place i and j at both ends of the expression.

        T^F|T&F^T|F
        i         j

Try all partitions:
As we have figured out the logic for marking the i, and j pointers, we will move to the partitioning loop. We can simply write a for loop(say ind) starting from i+1 to j-1, The problem is being broken in the following manner:

        T ^ F | T & F ^ T | F
             /    |   \
left subproblem  ind   right subproblem
f(i,ind-1)             f(ind+1,j)

Note: Here f(i, ind-1) is the left sub-problem, and f(ind+1, j) is the right sub-problem. And the ind variable will start from i+1 and runs up to j-1 and it will move 2 steps in each iteration to select each operator at a time like the following:

f(i,j){
    if(i>j) return 0; //base case 1
    for(int ind=i+1;ind<j;ind+=2){
        //partitioning logic
    }
}

Base Case 1: We can say that when i > j this is not a valid partition and so we will return 0.
The other base case is discussed later.

Return the best possible answer:

Here, in this problem, we are trying to figure out the total number of ways through which we can get the result true for the given expression. So, the final answer will be the summation of all the answers obtained from the subproblems.

Observation 1:

Now, if we want the result true for the whole expression, we can easily observe the following three cases:

Case 1 (If the partition is made at the ‘AND(&)’ operator): 

The structure will look like the following:
                Whole expression
        left subproblem  &  right subproblem
        /                               \
Yeilds true=x1 ways                      Yields true= x3 ways
Yeilds false=x2 ways                     Yields false= x4 ways

Now, the whole expression will yield true when the subproblem1 and subproblem2 both will yield true. So, the total number of ways will be = (x1 * x3).

Case 2 (If the partition is made at the ‘OR(|)’ operator):

The structure will look like the following:

                Whole expression
        left subproblem  |  right subproblem
        /                               \
Yeilds true=x1 ways                      Yields true= x3 ways
Yeilds false=x2 ways                     Yields false= x4 ways

Now, the whole expression will yield true in three possible ways:

    -> Subproblem1 yields true, and subproblem2 yields true i.e. (x1 * x3) ways.
    -> Subproblem1 yields false and subproblem2 yields true i.e. (x2 * x3) ways.
    -> Subproblem1 yields true and subproblem2 yields false i.e. (x1 * x4) ways.
So, total number of ways = (x1 * x3) + (x2 * x3) + (x1 * x4).

Case 3 (If the partition is made at the ‘XOR(^)’ operator):

The structure will look like the following:

                Whole expression
        left subproblem  ^  right subproblem
        /                               \
Yeilds true=x1 ways                      Yields true= x3 ways
Yeilds false=x2 ways                     Yields false= x4 ways

Now, the whole expression will yield true in two cases:

    -> Subproblem1 yields false and subproblem2 yields true i.e. (x2 * x3) ways.
    -> Subproblem1 yields true and subproblem2 yields false i.e. (x1 * x4) ways.
So, total number of ways = (x2 * x3) + (x1 * x4).

Observation 2:

Now, we have found that in order to solve the problem, we need to figure out the number of cases the subproblems yield true and the number of cases the subproblems yield false(i.e. The values of x1, x2, x3, and x4).

In order to do so, we will carry a third variable(let’s say isTrue) to indicate for which result we are trying to calculate the number of ways. If isTrue is 1, we will calculate the number of ways that provide the result true and if isTrue is 0, we will calculate the number of ways that give the result false.

So, the modified function structure will be the following:

f(i,j,isTrue){
    if(i>j) return 0; //base case 1
    for(int ind=i+1;ind<j;ind+=2){
        //partitioning logic
    }
}

Observation 3:
Now, if we continue to break down the expression into smaller subproblems, at some point we will get such a subproblem that contains only a single operand. Let’s understand it considering the following illustration:
                    T|F^T
                    /    \
                   /\     .
                (T)  (F^T) .
                /\
                i j
                this subproblem will return 1 way through which it gives the result true.

From the example, we can clearly notice that a subproblem that contains only a single operand(i.e. when i and j are equal, i == j) returns either 1 or 0 ways for true and similarly 1 or 0 ways for false. And this will be the 2nd base case.

Base case 2:

If i and j become equal, we will observe two different cases:

    -> Case 1 (If we want the number of ways for true(i.e. isTrue = 1)):
        If the single operand left, is T(true), it will return 1 way and if it is F(false), it will return 0 ways.
    -> Case 2 (If we want the number of ways for false(i.e. isTrue = 0)):
        If the single operand left, is T(true), it will return 0 ways and if it is F(false), it will return 1 way.
So, the base case 2 will be the following:

if(i==j){//base case 2
    if(isTrue==1){
        //returns 1 if single operand is T
        return a[i]=='T';
    }
    else{
        //returns 1 if single operand is F
        return a[i]=='F';
    }
}


Now let’s move on to the calculation of the no. of ways:
Inside the partitioning loop we will calculate the total no. of ways for the subproblems to be true and false like the following:

for(int ind=i+1;ind<=j-1;ind++){
    //calculate the no. of ways
    int lT=f(i,ind-1,1)// no. of ways left subproblem being true
    int lF=f(i,ind-1,0)// no. of ways left subproblem being false
    int rT=f(ind+1,j,1)// no. of ways right subproblem being true
    int rF=f(ind+1,j,0)// no. of ways right subproblem being false
}

Note: Since the number of ways can be a large number, we are doing a modulo of 1000000007.

Let’s discuss the approach and the implementation part:

Approach: 

The recursive algorithm steps are as follows:

    -> Convert the problem to a recursive function marked by the pointers i and j and the isTrue variable discussed above.
    -> Use a loop to check all possible partitions of the expression and calculate the total number of ways.
    -> Return the total number of ways calculated.
    -> Base case 1: If i > j, we will return 0.
       Base case 2: If i and j become equal, we will observe two different cases:
    -> Case 1 (If we want the number of ways of true(i.e. isTrue = 1)):
        If the single operand left is T(true), it will return 1 way and if it is F(false), it will return 0 ways.
    -> Case 2 (If we want the number of ways of false(i.e. isTrue = 0)):
        If the single operand left is T(true), it will return 0 ways and if it is F(false), it will return 1 way.

Complexity Analysis
Time Complexity: Exponential

Memoization Approach
Algorithm / Intuition
Steps to memoize the recursive solution:

    -> Create a 3D dp array of size [n][n][2]. i and j can range from 1 to n and isTrue can range from 0 to 1 so we take the size n X n X 2.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to particular parameters (say f(i,j, isTrue)), we first check whether the answer is already calculated using the dp array(i.e dp[i][j][isTrue] != -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[i][j][isTrue] to the solution we get.

Complexity Analysis
Time Complexity: O(N*N*2 * N) ~ O(N3) There are a total of 2*N2 no. of states. And for each state, we are running a partitioning loop roughly for N times.

Space Complexity: O(2*N2) + Auxiliary stack space of O(N), 2*N2 for the dp array we are using.

Tabulation Approach
Algorithm / Intuition
Tabulation:

    -> First of all, we handle the base case. If (i > j) we return 0. To cover this case we can initialize the entire dp array with 0.
    -> Next, memoization is a top-down approach, whereas tabulation is bottom-up. Our changing parameters i and j will change in opposite directions, i.e i will change from n→1 and j will change from 1→ n. isTrue will change from 0→1.
    -> Next, we copy down the recursive logic(recurrence) inside the nested loops.

Complexity Analysis
Time Complexity: O(N*N*2 * N) ~ O(N3) There are a total of 2*N2 no. of states. And for each state, we are running a partitioning loop roughly for N times.

Space Complexity: O(2*N2), 2*N2 for the dp array we are using.
*/

#include <bits/stdc++.h>
using namespace std;

#define ll long long
const int mod = 1000000007;

int f(int i, int j, int isTrue, string &exp) {
    // Base case 1: If i > j, it's an invalid expression, return 0.
    if (i > j) return 0;
    
    // Base case 2: If i and j are the same, evaluate the single character.
    if (i == j) {
        if (isTrue == 1) return exp[i] == 'T' ? 1 : 0;
        else return exp[i] == 'F' ? 1 : 0;
    }
    
    ll ways = 0;
    
    // Iterate through the expression.
    for (int ind = i + 1; ind <= j - 1; ind += 2) {
        ll lT = f(i, ind - 1, 1, exp);  // Number of ways to make the left expression true.
        ll lF = f(i, ind - 1, 0, exp);  // Number of ways to make the left expression false.
        ll rT = f(ind + 1, j, 1, exp);  // Number of ways to make the right expression true.
        ll rF = f(ind + 1, j, 0, exp);  // Number of ways to make the right expression false.

        // Check the operator at the current index and update ways accordingly.
        if (exp[ind] == '&') {
            if (isTrue) ways = (ways + (lT * rT) % mod) % mod;
            else ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lF * rF) % mod) % mod;
        }
        else if (exp[ind] == '|') {
            if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lT * rT) % mod) % mod;
            else ways = (ways + (lF * rF) % mod) % mod;
        }
        else {  // XOR operator
            if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod) % mod;
            else ways = (ways + (lF * rF) % mod + (lT * rT) % mod) % mod;
        }
    }
    return ways;
}

//Using Recursion
int evaluateExp(string &exp) {
    int n = exp.size();
    return f(0, n - 1, 1, exp);  // Start evaluation with isTrue set to true.
}

int f(int i, int j, int isTrue, string &exp, vector<vector<vector<ll>>> &dp) {
    // Base case 1: If i > j, it's an invalid expression, return 0.
    if (i > j) return 0;
    
    // Base case 2: If i and j are the same, evaluate the single character.
    if (i == j) {
        if (isTrue == 1) return exp[i] == 'T' ? 1 : 0;
        else return exp[i] == 'F' ? 1 : 0;
    }

    // If the result for this subproblem has been computed before, return it.
    if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
    
    ll ways = 0;
    
    // Iterate through the expression.
    for (int ind = i + 1; ind <= j - 1; ind += 2) {
        ll lT = f(i, ind - 1, 1, exp, dp);  // Number of ways to make the left expression true.
        ll lF = f(i, ind - 1, 0, exp, dp);  // Number of ways to make the left expression false.
        ll rT = f(ind + 1, j, 1, exp, dp);  // Number of ways to make the right expression true.
        ll rF = f(ind + 1, j, 0, exp, dp);  // Number of ways to make the right expression false.

        // Check the operator at the current index and update ways accordingly.
        if (exp[ind] == '&') {
            if (isTrue) ways = (ways + (lT * rT) % mod) % mod;
            else ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lF * rF) % mod) % mod;
        }
        else if (exp[ind] == '|') {
            if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lT * rT) % mod) % mod;
            else ways = (ways + (lF * rF) % mod) % mod;
        }
        else {  // XOR operator
            if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod) % mod;
            else ways = (ways + (lF * rF) % mod + (lT * rT) % mod) % mod;
        }
    }
    
    // Store the result in the DP table and return it.
    return dp[i][j][isTrue] = ways;
}

//Using Memoization
int evaluateExp_Memo(string &exp) {
    int n = exp.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, -1)));
    return f(0, n - 1, 1, exp, dp);  // Start evaluation with isTrue set to true.
}

//Using Tabulation
int evaluateExp_Tab(string &exp) {
    int n = exp.size();
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = 0; j <= n - 1; j++) {
            // Base case 1: i > j is an invalid case, so continue.
            if (i > j) continue;
            
            for (int isTrue = 0; isTrue <= 1; isTrue++) {
                // Base case 2: i == j, evaluate the single character.
                if (i == j) {
                    if (isTrue == 1) dp[i][j][isTrue] = exp[i] == 'T';
                    else dp[i][j][isTrue] = exp[i] == 'F';
                    continue;
                }

                // Recurrence logic:
                ll ways = 0;
                for (int ind = i + 1; ind <= j - 1; ind += 2) {
                    ll lT = dp[i][ind - 1][1];
                    ll lF = dp[i][ind - 1][0];
                    ll rT = dp[ind + 1][j][1];
                    ll rF = dp[ind + 1][j][0];

                    if (exp[ind] == '&') {
                        if (isTrue) ways = (ways + (lT * rT) % mod) % mod;
                        else ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lF * rF) % mod) % mod;
                    }
                    else if (exp[ind] == '|') {
                        if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod + (lT * rT) % mod) % mod;
                        else ways = (ways + (lF * rF) % mod) % mod;
                    }
                    else {
                        if (isTrue) ways = (ways + (lF * rT) % mod + (lT * rF) % mod) % mod;
                        else ways = (ways + (lF * rF) % mod + (lT * rT) % mod) % mod;
                    }
                }
                dp[i][j][isTrue] = ways;
            }
        }
    }
    return dp[0][n - 1][1];
}


int main() {
    string exp = "F|T^F";
    int ways = evaluateExp(exp);
    cout << "The total number of ways: " << ways << "\n";//Using Recursion
    int ways_memo = evaluateExp_Memo(exp);
    cout << "The total number of ways: " << ways_memo << "\n";//Using Memoization
    int ways_tab = evaluateExp_Tab(exp);
    cout << "The total number of ways: " << ways_tab << "\n";//Using Tabulation
    return 0;
}

