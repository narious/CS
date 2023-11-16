# [B. The floor is lava!](https://codeforces.com/gym/104782/problem/B)

## Interpetation
Problem Statement: <br>
K people in the room of size n by m. Each position has a number a that represents the height of the cell. A person moves up,down,left,right one unit in one second. The maximum height of the cell is n * m. L ranges from 0 to n * m
Find the minimum time for all L from 0 to n * m.

Main Points:
- Must find shortest distance to cell of height L for any starting point. 
- If we have found the shortest distance for person A to a valid cell from i,j node, then if person B reaches node i,j we can use the shortest distance from person A's search from node i,j
- Every node will need to have a list denoting the shortest distance to a node that is > L.
- The list stops searhing when we reach L = n * m. 
- If for any L a valid cell cannot be reached then for all l >= L that l cannot be reach as well and the result is -1


## Approach


## Implementation


## Results and FullCode