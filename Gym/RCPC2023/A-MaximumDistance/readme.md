# [A. Maximum Distance](https://codeforces.com/gym/104782/problem/A)

### Problem Statement
Before giving you the problem statement, we will define 𝑑𝑖𝑠𝑡([𝑥1,𝑥2,…𝑥𝑘],[𝑦1,𝑦2,…𝑦𝑘])
 as the number of indexes 𝑖
 (1≤𝑖≤𝑘
) such that 𝑥𝑖≠𝑦𝑖
.

You are given 𝑛
 and two arrays 𝑎1,𝑎2,…𝑎𝑛
 and 𝑏1,𝑏2,…𝑏𝑛. <b>Find the maximum 𝑑𝑖𝑠𝑡</b>
 when choosing any two subarrays of your choice (one from 𝑎
 and one from 𝑏
) that have the same length. A subarray of 𝑐
 is a contiguous part of an array 𝑐
, i. e. the array 𝑐𝑖,𝑐𝑖+1,…𝑐𝑗
 for some 1≤𝑖≤𝑗≤𝑛
.

## Approach 
Let s1 be the first array <br>
Let s2 be the second array
#### Brute Force
The brute force method checks each subarray against every other subarray. Start from the largest subarray to smaller

#### Dynamic Programming
Notice in the brute fore method we often retest the same parts over and over again. This suggest the problem we are repeating is a subprolem, and may be able to be stored.

Define the memo such that `memo[i][j]` is the best difference between `s1[:i]` and `s2[:j]` where `s1[i]` is alligned with s[j]. Then `memo[i][j] = memo[i-1][j-1]` + 1 if `s1[i] != s2[j]` and + 0 otherwise. 

The max could be on either of the last column or the last row

## Results and [Full Code](./MaximumDistance.cpp)
![Amaxdist](./a-maxdist_res.png)

