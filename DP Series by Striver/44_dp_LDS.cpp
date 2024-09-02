/*
Longest Divisible Subset

Prerequisite:

Longest Increasing Subsequence
Printing longest increasing subsequence

Let us first understand the difference between subset and subsequence.
Array:[1,16,7,8,4]

In a subsequence, the elements need to follow the order of the original array whereas in a subset there is no constraint on the order of the elements.

Divisible Subset

A divisible subset is the one in which if we pick two elements i and j from the subset, then either arr[i]%arr[j] == 0 or arr[j] % arr[i] == 0. For example, [16,8,4] is a divisible subset.

Subset {16,8,4}
Divisble Pairs: {16,8},{16,4},{8,4}
Either arr[i]%arr[j] == 0 or arr[j] % arr[i] == 0

Given an array with distinct elements, we need to print its longest divisible subset. We can print any answer.

Array: [1,16,7,8,4]
Longest Divisible Subset: [1,8,16,4]

Solution:

Intuition:

As here we are finding the subsets, we can change the order of the original array. Let us sort it out first.
Array:[1,4,7,8,16]

Now, we can start thinking in terms of subsequences questions solved earlier.

Let us pick the first index element in an array (say temp) and move to the next index.
Array:[1,4,7,8,16]
      i=0
Temp:[1]

Now, i = 1 and arr[i] = 4. We can again push this into the array as 4%1 == 0.
Array:[1,4,7,8,16]
        i=1
Temp:[1,4]

For i=2, arr[i] = 7. We can’t push it in the temp array as 7%4 != 0 . Now, i = 3 and arr[i] = 8. We can again push this into the array as 8%4 == 0.
Array:[1,4,7,8,16]
            i=3
Temp:[1,4,8]

Now as the elements in the temp array were sorted, we only checked that element 8 was divisible by the last element of the tamp array i.e 4. But we know that 4 is divisible by the first element of the temp array i.e 4%1 == 0. As the array is sorted and 8%4 == 0. And 4%1==0. We can automatically imply that 8%1==0. Hence this temp array formed is a divisible subsequence.

Let us take another case to make it more clear.

As i = 4, arr[i] = 16. Now 16 is divisible by the last element of the temp array which is 8, so we can push 16 into the temp array.
Array:[1,4,7,8,16]
              i=4
Temp:[1,4,8,16]

To summarize:

    -> Whenever the current index element (arr[i]) is divisible by the last element of the temp array(say temp[last]), we can push that element to the temp array.
    -> As the temp array formed will always be sorted, and arr[i] is divisible by the temp[last], we can say that arr[i] will be divisible by every element before the temp[last] of the temp array.
    -> Therefore, this temp array will be a divisible subsequence and we just need to find the longest divisible subsequence of the array.
Approach

The algorithm approach is stated as follows:

    -> First of all sort the array,
    -> Then find the longest divisible subsequence of the array.
    -> In order to find the longest divisible subsequence, we will follow the algorithm used to find the longest increasing subsequence discussed in thedp-42.
    -> The distinguishing factor between longest increasing subsequence and longest divisible subsequence is that we used to insert the element if arr[i] > arr[prev] but here we will insert the element when arr[i] % arr[prev] == 0.
    -> At last return the hash array as the answer.

for(int i = 0; i < n; i++) {
    for(int prev_index = 0; prev_index < i; prev_index++) {
        if(arr[i] % arr[prev_index] == 0 && 1 + dp[prev_index] > dp[i]) {
            dp[i] = 1 + dp[prev_index];
        }
    }
}

Time Complexity: O(N*N)

Reason: There are two nested loops.

Space Complexity: O(N)

Reason: We are only using two rows of size n.
*/

#include <bits/stdc++.h>
using namespace std;

// Function to find the longest divisible subset
vector<int> divisibleSet(vector<int> &arr)
{
    int n = arr.size();

    // Sort the array in ascending order
    sort(arr.begin(), arr.end());

    vector<int> dp(n, 1);   // dp[i] stores the length of the divisible subset ending at arr[i]
    vector<int> hash(n, 0); // hash[i] stores the previous index in the divisible subset ending at arr[i]

    for (int i = 0; i < n; i++)
    {
        hash[i] = i; // Initialize with the current index
        for (int prev_index = 0; prev_index < i; prev_index++)
        {
            if (arr[i] % arr[prev_index] == 0 && 1 + dp[prev_index] > dp[i])
            {
                dp[i] = 1 + dp[prev_index];
                hash[i] = prev_index;
            }
        }
    }

    int ans = -1;
    int lastIndex = -1;

    for (int i = 0; i < n; i++)
    {
        if (dp[i] > ans)
        {
            ans = dp[i];
            lastIndex = i;
        }
    }

    vector<int> temp;
    temp.push_back(arr[lastIndex]);

    // Reconstruct the divisible subset using the hash table
    while (hash[lastIndex] != lastIndex)
    {
        lastIndex = hash[lastIndex];
        temp.push_back(arr[lastIndex]);
    }

    // Reverse the array to get the correct order
    reverse(temp.begin(), temp.end());

    return temp;
}

int main()
{
    vector<int> arr = {1, 16, 7, 8, 4};

    vector<int> ans = divisibleSet(arr);

    cout << "The longest divisible subset elements are: ";

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }

    return 0;
}