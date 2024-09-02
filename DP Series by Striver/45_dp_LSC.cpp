/*
Longest String Chain

Prerequisite:

Longest Increasing Subsequence
Printing longest increasing subsequence

Problem Statement: We are given an array of strings (sat words[ ]), and we need to return the longest string chain. This longest string chain is defined as:

    -> A subsequence of words[ ] of the string.
    -> Every element of this subsequence ( a string) except the first one can be formed by inserting a single character into the previous element.
    -> The first element of this subsequence can be any string from the words[ ] array.

Example: words[] = {“a”, “b”, “ba”, “bca”, “bda”, “bdca”}
Longest String Chain: {“a”, “ba”, “bda”, “bdca”}

We need to print the length of the longest string chain, in this case: 4.

Two consecutive strings in this string chain need to have an insertion of a single character. The character can be added to any place on the string.

"a"-+b>"ba"-+d>"bda"-+c>"bdca"

Solution: 

This problem can be compared with the already discussed problem of dp-42, the longest increasing subsequence.

There we used to compare two elements of the array and consider the previous element of the array if it was smaller than the current element.

In this problem, we will use the same technique and compare two values of the array and consider the previous element of the array, if it is just one character deletion from the current element.

for(int i = 0; i < n; i++)
{
    for(int prev_ind=0;prev_index<=i-1;prev_index++){
    if(compare(arr[i],arr[j])){
        dp[i]=max(dp[i],1+dp[prev_index])
    }
    }
}

Now, the main task is left to write this compare( ) function.

compare( S1, S2)

It returns true if the first string S1 is just a single character addition with S2 else it returns false. The way we have called the code, we expect S1 to be the larger string of the two. Therefore the length of S1 should be greater than the length of S2 by 1. 

After checking for the length we can do a character matching using a two-pointer approach.

    -> We will declare two pointers first and second, initially set to the first index of S1 and S2 respectively.
    -> Then we set a while loop which will run till the first is less than the length of S1.
    -> In every iteration, if both the characters match, i.e S1[first] == S2[second], we increment both first and second by 1.
    -> Else, we will increment only first by 1.
    -> As S1’s length(say m) is just greater than S2’s length(say n) by 1 using the above pointer approach both the pointers should point to m and n simultaneously. If it happens we return true, else we return false.
For example: 
f->first
s->second
    f
S1:"bda"   S1[first]==S2[second]=>first++;second++;
S2:"ba"
    s

     f
S1:"bda"   S1[first]!=S2[second]=>first++;
S2:"ba"
     s

      f
S1:"bda"   S1[first]==S2[second]=>first++;second++;
S2:"ba"
     s

       f
S1:"bda"   As both S1 and S2 points to the end of string simultaneously, we return true.
S2:"ba"
      s

Note: This question Longest String Chain expects us to find the longest chain subset instead of subsequence, therefore we will first sort the array (on the basis of the length of the string) to get the answer as discussed in dp-44.

Time Complexity: O(N*N * l)

Reason: We are setting up two nested loops and the compare function can be estimated to l, where l is the length of the longest string in the words [ ] array. Also, we are sorting so the time complexity will be (N^2 * l + NlogN)

Space Complexity: O(N)

Reason: We are only using a single array of size n.
*/
#include<bits/stdc++.h>
using namespace std;

bool compare(string& s1, string& s2){
    if(s1.size() != s2.size() + 1) return false;
    
    int first = 0;
    int second = 0;
    
    while(first < s1.size()){
        if(second < s2.size() && s1[first] == s2[second]){
            first ++;
            second ++;
        }
        else first ++;
    }
    if(first == s1.size() && second == s2.size()) return true;
    else return false; 
}

bool comp(string& s1, string& s2){
    return s1.size() < s2.size();
}


int longestStrChain(vector<string>& arr){

    int n = arr.size();
    
    //sort the array
    
    sort(arr.begin(), arr.end(),comp);

    vector<int> dp(n,1);
    
    int maxi = 1;
    
    for(int i=0; i<=n-1; i++){
        
        for(int prev_index = 0; prev_index <=i-1; prev_index ++){
            
            if( compare(arr[i], arr[prev_index]) && 1 + dp[prev_index] > dp[i]){
                dp[i] = 1 + dp[prev_index];
            }
        }
        
        if(dp[i] > maxi)
            maxi = dp[i];
    }
    return maxi;
}
    

int main() {
	
	vector<string> words = {"a","b","ba","bca","bda","bdca"};
	
	cout<<" The length of the longest string chain is : "<<longestStrChain(words);
	
}