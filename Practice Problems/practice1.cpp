//Different ways to add parenthesis
/*
Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.

The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.

Example 1:
Input: expression = "2-1-1"
Output: [0,2]
Explanation:
((2-1)-1) = 0 
(2-(1-1)) = 2

Example 2:
Input: expression = "2*3-4*5"
Output: [-34,-14,-10,-10,10]
Explanation:
(2*(3-(4*5))) = -34 
((2*3)-(4*5)) = -14 
((2*(3-4))*5) = -10 
(2*((3-4)*5)) = -10 
(((2*3)-4)*5) = 10

Constraints:

1 <= expression.length <= 20
expression consists of digits and the operator '+', '-', and '*'.
All the integer values in the input expression are in the range [0, 99].
*/

/*
Editorial:

Approach 1: Recursion
Intuition
When we add parentheses to an expression, they group parts of the expression, telling us to evaluate those parts first. To decide where to place these parentheses, we look at each operator in the expression. Each operator offers a chance to split the expression into two smaller parts: everything before the operator and everything after it. These smaller parts are similar to our original problem, so we use recursion to solve them.

We start by defining our base cases, where we can return a result without further recursion:

    -> If the expression is empty, return an empty list.
    -> If the expression is a single digit, return a list with that number.
    -> If the expression has two characters and the first is a digit, the second must also be a digit. We convert the expression to a number and return it in a list.
For longer expressions, we find operators to split the expression. We iterate through each character, and when we find an operator, we recursively evaluate the parts before and after it. We store the results of these evaluations in separate lists. Then, we combine the results from the left and right parts using the operator and store the final values in a list.

Here’s a visual example of how a recursion subtree might look:

                2*3-4*5
                /   \
               2     3-4*5
                     /  \ 
                3-(4*5)  (3-4)*5
                   |       |
                  -17      -5
            Applying operator:
            left: [2]  *  right: [-17, -5]
                        ||
            results: [-34, -10]  

By the end of the process, the results list will contain all possible results from grouping the numbers and operators in the expression.

Algorithm
    -> Initialize a list results to store the possible outcomes.
    -> If the input string is empty, return the empty results list.
    -> Check if expression is a single character:
        -> If so, convert it to an integer and add it to results.
        -> Return results.
    -> Check if expression has only two characters and starts with a digit:
        -> If so, convert the entire string to an integer and add it to results.
        -> Return results.
    -> Iterate through each character of expression:
        -> Set the current character as currentChar.
        -> If currentChar is a digit, continue to the next iteration.
        -> Recursively call diffWaysToCompute for the left part of expression (from indices 0 to i-1) and set it to a list leftResults.
        -> Recursively call diffWaysToCompute for the right part of expression (from indices i+1 to the end) and set it to a list rightResults.
        -> Iterate through leftValue in leftResults:
            -> For each leftValue, iterate through each rightValue in the rightResults:
                -> Initialize a variable computedResult to store the result of the current operation.
                -> Perform the operation (addition, subtraction, or multiplication) based on the current character.
                -> Add the computedResult to the results list.
    -> Return results as our answer.

Complexity Analysis
Let n be the the length of the input string expression.

    -> Time complexity: O(n⋅2^n )

    -> Space complexity: O(2^n )



Approach 2: Memoization
Intuition
When dealing with complex expressions, we often find ourselves repeating the same calculations. Take the expression 2 + 2 - 2 - 2 - 2. You could group it in different ways:

    -> ((2 + 2) - (2 - 2) - 2)
    -> ((2 + 2) - 2 - (2 - 2))
As you can see, the sub-expression (2 + 2) is evaluated more than once.

To avoid this, we can store the results of these sub-calculations. This way, if we hit the same sub-problem again, we can use the stored result instead of recalculating it, which speeds things up.

Another issue with the previous method was that it repeatedly created substrings of the expression. Since creating a substring takes O(n) time, where n is the length of the string, this can be quite slow. Instead, we’ll pass the entire expression to each recursive call and use start and end indices to specify the part we're interested in. This avoids the costly substring operations.

In our updated approach, each state in the recursion is defined by the start and end indices. We use a 2D array for memoization, where each cell memo[i][j] holds the list of possible results for the sub-expression from index i to index j.

Note: There is an alternative way to apply memoization in this problem. Consider the expression "2-2-2". This can be grouped in two ways: (2 - 2) - 2 and 2 - (2 - 2). As you can see, the expression "2 - 2" is being evaluated repeatedly, even though the instances do not share the same indices.

To memoize this, we need to store the substring itself as the state of the sub-problem. This can be achieved by using a map with the substring as the key and the list of results as the value. Whenever we encounter the same substring, we can return the result from the map.

While this approach leads us to identify and cache more sub-problems, it forces us to use substrings in our recursion. In an interview setting, you can highlight both approaches and discuss their advantages and disadvantages for extra credit.

Algorithm
Main method diffWaysToCompute:

    -> Initialize a 2D array memo to store computed results for sub-expressions.
    -> Call the computeResults method with the full expression range and return the result.
Helper method computeResults(expression, memo, start, end):

    -> Check if the result for the range [start, end] is memoized. If so, return the memoized result.
    -> Initialize a list results to store computed values for the current sub-expression.
    -> Check if the current range is a single digit:
        -> If so, convert expression to an integer and add it to results.
        -> Return results.
    -> Check if the current range is a two-digit number:
        -> If so, compute its value and add it to results.
        -> Return results.
    -> Iterate through each character in the current range of the expression:
        -> Skip the current iteration if the character is a digit.
        -> Recursively call computeResults for the left part of the expression up to the current character (from start to i-1). Store the result in leftResults.
        -> Recursively call computeResults for the right part of the expression after the current character (from i+1 to end). Store the result in rightResults.
        -> Iterate through each leftValue in the leftResults:
            -> For each leftValue, iterate through each rightValue in rightResults:
            -> Perform the operation (addition, subtraction, or multiplication) based on the current character.
            -> Add the computed result to the results list.
        -> Store the result in memo for the range [start, end].
    -> Return the results list.

Complexity Analysis
Let n be the the length of the input string expression.

    -> Time complexity: O(n⋅2^n )
    -> Space complexity: O(n^2 ⋅2^n )

Approach 3: Tabulation
Intuition
Recursive solutions can use up a lot of stack space, which might lead to stack overflow errors. To avoid this, we'll switch to an iterative approach and build our solution step by step.

We’ll use a 2-D array, called dp, to keep track of intermediate results. This table will have dimensions n x n, where n is the length of our input expression. Each cell dp[i][j] will store all possible results for the sub-expression starting at index i and ending at index j. For instance, dp[0][2] will hold all possible results for the first three characters of the expression.

First, we need to fill in our base cases. We loop through the expression to identify all single-digit and double-digit numbers.

    -> For single-digit numbers, add the digit's value to dp[i][i].
    -> For double-digit numbers, add the number's value to dp[i][i+1].

Next, we handle longer sub-expressions. We start with lengths of 3 and go up to the length of the expression. For each length, we consider all possible starting points in the expression. This double loop structure ensures we consider all possible substrings of expression. For each sub-expression, we try different ways to split it. We go through each character and, when we find an operator, split the expression at that point. We then combine the results from the left and right parts using the operator.

After we've filled our entire dp table, the cell dp[0][n-1] contains all possible results for the entire expression. We can return this list as our final answer.

Algorithm
Main method diffWaysToCompute:

    -> Initialize a variable n to store the length of the input string expression.
    -> Create a 2D array dp of lists to store the results of sub-problems.
    -> Initialize the base cases using the initializeBaseCases method.
    -> Iterate through all possible sub-expression lengths, starting from 3 up to n.
        -> For each length, iterate through all possible start positions of the sub-expression.
        -> Set end as start + length - 1.
        -> Calculate the results for the sub-expression [start, end] using the processSubexpression method.
    -> Return dp[0][n-1], which contains all possible results for the entire expression.

Helper method initializeBaseCases(expression, dp):

    -> Initialize the dp array.
    -> Handle base cases by iterating through the expression:
        -> For single digits, add the digit value to dp[i][i].
        -> For two-digit numbers, add the number value to dp[i][i+1].
Helper method processSubexpression(expression, dp, start, end):

    -> Try all possible split positions from start to end:
    -> If the character is numeric, continue to the next iteration
    -> If not, retrieve the results of the left sub-expression from dp[start][split-1] and assign it to leftResults.
    -> Retrieve the results of the right sub-expression from dp[split+1][end] and assign it to rightResults.
    -> Call computeResults with leftResults, rightResults, and the operator at the split position.
Helper method computeResults(op, leftResults, rightResults, results):

    -> For each combination of leftResults and rightResults:
        -> Perform the operation specified by op.
        -> Add the result to results.

Complexity Analysis
Let n be the the length of the input string expression.

Time complexity: O(n⋅2^n )
Space complexity: O(n^2 ⋅2^n )
*/
#include<bits/stdc++.h>
using namespace std;

// Approach 1: Recursion
class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        vector<int> results;

        // Base case: if the string is empty, return an empty list
        if (expression.length() == 0) return results;

        // Base case: if the string is a single character, treat it as a number
        // and return it
        if (expression.length() == 1) {
            results.push_back(stoi(expression));
            return results;
        }

        // If the string has only two characters and the first character is a
        // digit, parse it as a number
        if (expression.length() == 2 && isdigit(expression[0])) {
            results.push_back(stoi(expression));
            return results;
        }

        // Recursive case: iterate through each character
        for (int i = 0; i < expression.length(); i++) {
            char currentChar = expression[i];

            // Skip if the current character is a digit
            if (isdigit(currentChar)) continue;

            // Split the expression into left and right parts
            vector<int> leftResults =
                diffWaysToCompute(expression.substr(0, i));
            vector<int> rightResults =
                diffWaysToCompute(expression.substr(i + 1));

            // Combine results from left and right parts
            for (int leftValue : leftResults) {
                for (int rightValue : rightResults) {
                    int computedResult = 0;

                    // Perform the operation based on the current character
                    switch (currentChar) {
                        case '+':
                            computedResult = leftValue + rightValue;
                            break;
                        case '-':
                            computedResult = leftValue - rightValue;
                            break;
                        case '*':
                            computedResult = leftValue * rightValue;
                            break;
                    }

                    results.push_back(computedResult);
                }
            }
        }

        return results;
    }
};


// Approach 2: Memoization
class Solution2 {
public:
    vector<int> diffWaysToCompute(string expression) {
        // Initialize memoization vector to store results of subproblems
        vector<vector<vector<int>>> memo(
            expression.length(), vector<vector<int>>(expression.length()));
        // Solve for the entire expression
        return computeResults(expression, memo, 0, expression.length() - 1);
    }

private:
    vector<int> computeResults(string& expression,
                               vector<vector<vector<int>>>& memo, int start,
                               int end) {
        // If result is already memoized, return it
        if (!memo[start][end].empty()) {
            return memo[start][end];
        }

        vector<int> results;

        // Base case: single digit
        if (start == end) {
            results.push_back(expression[start] - '0');
            return results;
        }

        // Base case: two-digit number
        if (end - start == 1 && isdigit(expression[start])) {
            int tens = expression[start] - '0';
            int ones = expression[end] - '0';
            results.push_back(10 * tens + ones);
            return results;
        }

        // Recursive case: split the expression at each operator
        for (int i = start; i <= end; i++) {
            char currentChar = expression[i];
            if (isdigit(currentChar)) {
                continue;
            }

            vector<int> leftResults =
                computeResults(expression, memo, start, i - 1);
            vector<int> rightResults =
                computeResults(expression, memo, i + 1, end);

            // Combine results from left and right subexpressions
            for (int leftValue : leftResults) {
                for (int rightValue : rightResults) {
                    switch (currentChar) {
                        case '+':
                            results.push_back(leftValue + rightValue);
                            break;
                        case '-':
                            results.push_back(leftValue - rightValue);
                            break;
                        case '*':
                            results.push_back(leftValue * rightValue);
                            break;
                    }
                }
            }
        }

        // Memoize the result for this subproblem
        memo[start][end] = results;

        return results;
    }
};

// Approach 3: Tabulation
class Solution3 {
public:
    vector<int> diffWaysToCompute(string expression) {
        int n = expression.length();
        // Create a 2D array of lists to store results of subproblems
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));

        initializeBaseCases(expression, dp);

        // Fill the dp table for all possible subexpressions
        for (int length = 3; length <= n; length++) {
            for (int start = 0; start + length - 1 < n; start++) {
                int end = start + length - 1;
                processSubexpression(expression, dp, start, end);
            }
        }

        // Return the results for the entire expression
        return dp[0][n - 1];
    }

private:
    void initializeBaseCases(string& expression,
                             vector<vector<vector<int>>>& dp) {
        int n = expression.length();
        // Handle base cases: single digits and two-digit numbers
        for (int i = 0; i < n; i++) {
            if (isdigit(expression[i])) {
                // Check if it's a two-digit number
                int dig1 = expression[i] - '0';
                if (i + 1 < n && isdigit(expression[i + 1])) {
                    int dig2 = expression[i + 1] - '0';
                    int number = dig1 * 10 + dig2;
                    dp[i][i + 1].push_back(number);
                }
                // Single digit case
                dp[i][i].push_back(dig1);
            }
        }
    }

    void processSubexpression(string& expression,
                              vector<vector<vector<int>>>& dp, int start,
                              int end) {
        // Try all possible positions to split the expression
        for (int split = start; split <= end; split++) {
            if (isdigit(expression[split])) continue;

            vector<int> leftResults = dp[start][split - 1];
            vector<int> rightResults = dp[split + 1][end];

            computeResults(expression[split], leftResults, rightResults,
                           dp[start][end]);
        }
    }

    void computeResults(char op, vector<int>& leftResults,
                        vector<int>& rightResults, vector<int>& results) {
        // Compute results based on the operator at position 'split'
        for (int leftValue : leftResults) {
            for (int rightValue : rightResults) {
                switch (op) {
                    case '+':
                        results.push_back(leftValue + rightValue);
                        break;
                    case '-':
                        results.push_back(leftValue - rightValue);
                        break;
                    case '*':
                        results.push_back(leftValue * rightValue);
                        break;
                }
            }
        }
    }
};

int main() {
    Solution solution;
    string expression = "2*3-4*5";
    vector<int> results = solution.diffWaysToCompute(expression);
    for (int result : results) {
        cout << result << " ";
    }
    cout << endl;
    Solution2 solution2;
    vector<int> results2 = solution2.diffWaysToCompute(expression);
    for (int result : results2) {
        cout << result << " ";
    }
    cout << endl;
    Solution3 solution3;
    vector<int> results3 = solution3.diffWaysToCompute(expression);
    for (int result : results3) {
        cout << result << " ";
    }
    cout << endl;
    return 0;
}