# [B. The floor is lava!](https://codeforces.com/gym/104782/problem/B)

## Interpetation
Problem Statement: <br>
K people in the room of size n by m. Each position has a number a that represents the height of the cell. A person moves up,down,left,right one unit in one second. The maximum height of the cell is n * m. L ranges from 0 to n * m
Find the minimum time for all L from 0 to n * m.

Main Points:
- Must find shortest distance to cell of height L for any starting point. 
- The shortest distance from two points is given by their manhattan distance

## Approach
### Brute Force
- First sort all the cells from heightest to lowest 
- Globally Maintain a vector that is size n * m where vec[i] is the <b>maximum</b> time required to wait for lava level i
- Iterate for every k in K participants and measure the manhattan distance for every cell (n * m) FROM heighest to lowest cell (since we sorted it) in a seperate vector vec_k (which will be merged afterwards)
- Maitain a minimum manhattan distance prev_d
- If the cell height h is reached with manhattan distance d, check to see if `d < prev_d then min_d = d otherwise min_d = prev_d`. In the vec_k set the best distance to level h is min_d i.e., `vec_k[h] = min_d`
- When we finish iterating through all cells we will be left with vec_k that has the shortest time required to wait for lava of height l. vec_k[l] = shortest distance to wait for laval height l
- Merge vec_k with vec taking the maximum of element i to give the min weight time

Time complexity: O(K * n * m)

Space Complexity: O(n * m)

In terms of time:
K <= 10,000 and m,n <= 700 thus atleast 1,400,000,000 operations, assuming 3 Ghz CPU then 3 operations/1ns  1,400,000,000 operations <= 0.5 seconds 

In terms of memory Total Memory >= 700 * 700 * 32 = 4480000 bits = 5mb

Meeting the requirements

## Implementation


## Results and FullCode



### Non Brute Force