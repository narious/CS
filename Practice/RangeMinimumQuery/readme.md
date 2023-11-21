# [Range Minimum Queries](https://en.wikipedia.org/wiki/Range_minimum_query)

A range minimum query is the problem of finding the smallest value within a subarray of compatitable items.

## Naive approach
The naive approach involves building a n * n array that computes the minimum for every index `arr[i:j]` this will take time and space complexity of $O(n^2)$ and $O(1)$ processing time 

## The sparse table