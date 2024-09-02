/*
Minimum cost to cut the stick

Problem Description: We are given a stick of length N and a CUTS array of size C. The stick has markings as shown, and the CUTS array depicts the marking at which the stick needs to be cut (shown in red).

Minimum cost to cut the stick
N=7 ,[ | | | | | | ]
     0 1 2 3 4 5 6 7
CUTS=[1,5,3,4]

Note: It is necessary to make cuts at all the red markings.

Whenever we make a cut, we incur a cost. This cost is equal to the length of the stick on which we are making the cut.
         | Length=7
     [ | | | | | | ]  Cost incurred for any cut =length of rod=7
     0 1 2 3 4 5 6 7
         |

         | Length=4
     [ | | | ]  Cost incurred for any cut =length of rod=4
     0 1 2 3 4
         |
We need to find the minimum cost incurred to cut the stick at all the cut points.

Example:N=7, CUTS=[1,5,3,4]
Cuts made in the order :3,5,1,4
           | Length=7
     [ | | | | | | ]  Cost incurred for any cut =length of rod=7
     0 1 2 3 4 5 6 7
           |

  |length=3                       | Length=4
[ | | ]                       [ | | | ]  
0 1 2 3                       3 4 5 6 7
  |                               |
Cost incurred for any cut     Cost incurred for any cut
=length of rod=3              =length of rod=4
                 |Length=2 =>Cost=length=2
[ ]    [ | ]   [ | ]      [ | ]
0 1    1 2 3   3 4 5      5 6 7
                 |
Total cost incured=7+4+3+2=16
Here 16 is the minimum cost that can be incurred for the given CUTS array.

Recursive Approach
Algorithm / Intuition
Intuition:

We need to minimize the cost incurred to cut the stick. Whenever we make a cut, we are changing the length of the stick which in turn decides the cost. Therefore the order in which we make the cuts changes the total cost. As discussed in DP-48 whenever the order of solving the problem comes into play, we can think in terms of Partition DP.

Let us quickly revise the rules to solve a problem on partition dp.

    -> Start with the entire block/array and mark it with i,j.
    -> Try all partitions.
    -> Return the best possible answer of the two partitions (the answer that comes after dividing the problem into two subproblems and solving them recursively).

Now let us go through these rules and apply them one by one to the MCM problem.

Marking the array with i,j

We are given a stick of size N and the CUTS array. Every element of the CUTS array represents the marking at which one cut needs to be made. When we make a cut, we are dividing the stick into two different parts.

Ideally, we would want to place the i, and j pointers at both ends of the CUTS array and try to solve the problem recursively, which we will eventually do. But we need to modify the given array. We will first discuss the need for a modification and then we will learn about the exact modification required.

We have the following example:
             |
N=7 => [ | | | | | | ]             CUTS=>[3 5 1 4]
       0 1 2 3 4 5 6 7                    0 1 2 3
             |                            i     j-pointer

Now, we try to place i and j on both ends of the CUTS array. Suppose we want to cut the stick at CUTS[0], i.e marking 3, then we will divide the bigger problem ( stick of length 7) into two smaller problems ( sticks of length 3 and 4) and solve these sub-problems independently  (as we are looking for a recursive solution). Now the problem which arises is that when we make a cut at marking 3, we also need to think of something to distribute the CUTS array. This means we need to define separate i, and j pointers for each subproblem. We can try breaking the CUTS array in the following way:

                                           |
N=7 => [ | | | | | | ]             CUTS=>[3| 5 1 4]
       0 1 2 3 4 5 6 7                    0| 1 2 3
       /  \ 
[ | | ]  [ | | | ]
0 1 2 3  3 4 5 6 7

[3]       [5 1 4]
0          1 2 3 
i j        i   j

Now the problem that we face here is that the information that marking 1 can be cut is not passed into the correct CUTS array of the left subproblem rather it is lying in the CUTS array of the right subproblem. Therefore these subproblems cannot be solved independently, thus defeating the whole point of a recursive solution. In order to solve this problem, we can initially sort the CUTS array. By sorting the CUTS array, we know that at whatever point we are making the cut, the information on the markings of the left portion will always be present on the left side of the CUTS array partition. Similarly on the right side.

Sorting the CUTS array:
             |
N=7 => [ | | | | | | ]             CUTS=>[1 3 | 4 5]
       0 1 2 3 4 5 6 7                    0 1 | 2 3
       /  \  |
[ | | ]  [ | | | ]
0 1 2 3  3 4 5 6 7

[1]       [4 5]
0          2 3 
i j        i j

Try all Partitions

As we have figured out the logic for marking the i, and j pointers, we will move to the partitioning loop. We can simply write a for loop(say ind) starting from i to j, The problem is being broken in the following manner:

f(i,j){
     for(int ind=i;ind<=j;ind++){
        ans=//execution at current step
        +f(i,ind-1) //left subproblem
        + f(ind+1,j) //right subproblem
    }
}

Note:  We are breaking the left subproblem to f(i,ind-1) rather than f(i,ind) because we have already made a cut at CUTS[ind] and we don't want to consider it twice.

Base Case: As i <=j, we can say that when i>j this is not a valid partition so we can return 0.

Return the best possible answer to the two partitions:

We know that the recursive functions along with the base case will get us the answer to the subproblems, but still, there is some work to do. We need to find the cost incurred to make the cut that is breaking the stick at CUTS[ind]. The cost incurred will be the length of the stick on which the cut is being made. We only have the CUTS array to figure it out, let's see how.

If we push 0 and N to both ends of the CUTS array:
       i     j
    0 [3 5 1 4] 7
    CUTS
Cost incurred = length of stick = CUTS[j+1] - CUTS[i-1]=7-0=7

Then CUTS[j+1] - CUTS[i-1] will always give us the correct length of the stick on which the cut is being made. Readers are advised to dry run with some other examples too to understand this.

Approach:
To summarize:

    -> Sort the CUTS array.
    -> Append 0  and N at both ends of the CUTS array.
    -> Convert the problem to a recursive function marked by two pointers i and j.
    -> Use a partitioning loop to try all partitions.
    -> Return the answer in which the partition gives the minimum cost.

Time Complexity: Exponential

Memoization Approach
Algorithm / Intuition
Steps to memoize the recursive solution:

    -> Create a dp array of size [c+1][c+1]. i and j can range from 0 to c so we take the size c X c.
    -> We initialize the dp array to -1.
    -> Whenever we want to find the answer to particular parameters (say f(i,j)), we first check whether the answer is already calculated using the dp array(i.e dp[i][j]!= -1 ). If yes, simply return the value from the dp array.
    -> If not, then we are finding the answer for the given value for the first time, we will use the recursive relation as usual but before returning from the function, we will set dp[i][j] to the solution we get.

Complexity Analysis
Time Complexity: O(N*N*N)

Reason: There are 2 variables i and j, therefore, N*N states and we explicitly run a loop inside the function which will run for N times, therefore at max ‘N*N*N’ new problems will be solved.

Space Complexity: O(N*N) + O(N)

Reason: We are using an auxiliary recursion stack space(O(N))and a 2D array ( O(N*N)).

Tabulation Approach
Algorithm / Intuition
Tabulation:

    -> First of all, we handle the base case. If (i > j) we return 0. To cover this case we can initialize the entire dp array with 0.
    -> Next, memoization is a top-down approach, whereas tabulation is bottom-up. Our changing parameters i and j will change in opposite directions, i.e i will change from c→1 and j will change from 1→ c.
    -> Next, we copy down the recursive logic inside the nested loops.

Complexity Analysis
Time Complexity: O(N*N*N)

Reason: There are 2 variables i and j, therefore, N*N states and we explicitly run a loop inside the function which will run for N times, therefore at max ‘N*N*N’ new problems will be solved.

Space Complexity: O(N*N) 

Reason: We are using a 2D array ( O(N*N)).
*/
#include <bits/stdc++.h>
using namespace std;

// Function to calculate the minimum cost incurred
int findMinimumCost(int i, int j, vector<int> &cuts) {
    // Base case: If i is greater than j, there are no cuts to consider.
    if (i > j) {
        return 0;
    }

    int mini = INT_MAX;

    for (int ind = i; ind <= j; ind++) {
        // Calculate the cost for making a cut at position 'ind'.
        int ans = cuts[j + 1] - cuts[i - 1] +
                  findMinimumCost(i, ind - 1, cuts) +
                  findMinimumCost(ind + 1, j, cuts);

        mini = min(mini, ans);
    }

    return mini;
}

//Recursive Solution
// Function to compute the minimum cost
int minimumCost(int n, int c, vector<int> &cuts) {
    // Modify the cuts array by adding 0 at the beginning and 'n' at the end.
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    // Call the recursive function to find the minimum cost.
    return findMinimumCost(1, c, cuts);
}

// Function to calculate the minimum cost incurred
int findMinimumCost(int i, int j, vector<int> &cuts, vector<vector<int>> &dp) {
    // Base case: If i is greater than j, there are no cuts to consider.
    if (i > j) {
        return 0;
    }

    if (dp[i][j] != -1) {
        return dp[i][j];
    }

    int mini = INT_MAX;

    for (int ind = i; ind <= j; ind++) {
        // Calculate the cost for making a cut at position 'ind'.
        int ans = cuts[j + 1] - cuts[i - 1] +
                  findMinimumCost(i, ind - 1, cuts, dp) +
                  findMinimumCost(ind + 1, j, cuts, dp);

        mini = min(mini, ans);
    }

    return dp[i][j] = mini;
}

//Memoization Solution
// Function to compute the minimum cost
int minimumCost_Mem(int n, int c, vector<int> &cuts) {
    // Modify the cuts array by adding 0 at the beginning and 'n' at the end.
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    // Create a DP table to store calculated values.
    vector<vector<int>> dp(c + 1, vector<int>(c + 1, -1));

    // Call the recursive function to find the minimum cost.
    return findMinimumCost(1, c, cuts, dp);
}

//Tabulation Solution
// Function to compute the minimum cost incurred
int minimumCost_Tab(int n, int c, vector<int> &cuts) {
    // Modify the cuts array by adding 0 at the beginning and 'n' at the end.
    cuts.push_back(n);
    cuts.insert(cuts.begin(), 0);
    sort(cuts.begin(), cuts.end());

    // Create a DP table to store calculated values.
    vector<vector<int>> dp(c + 2, vector<int>(c + 2, 0));

    for (int i = c; i >= 1; i--) {
        for (int j = 1; j <= c; j++) {
            if (i > j) continue;

            int mini = INT_MAX;

            for (int ind = i; ind <= j; ind++) {
                // Calculate the cost for making a cut at position 'ind'.
                int ans = cuts[j + 1] - cuts[i - 1] + dp[i][ind - 1] + dp[ind + 1][j];

                mini = min(mini, ans);
            }

            dp[i][j] = mini;
        }
    }

    return dp[1][c];
}


int main() {
    vector<int> cuts = {3, 5, 1, 4};
    int c = cuts.size();
    int n = 7;

    //Can't run simultaneously because we arev updating cuts array in evry function call as we giving array by reference
    // cout << "The minimum cost incurred is: " << minimumCost(n, c, cuts) << endl;//Recursive Solution
    // cout << "The minimum cost incurred is: " << minimumCost_Mem(n, c, cuts) << endl;//Memoization Solution
    cout << "The minimum cost incurred is: " << minimumCost_Tab(n, c, cuts) << endl;//Tabulation Solution

    return 0;
}