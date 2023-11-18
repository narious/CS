# [B. The floor is lava!](https://codeforces.com/gym/104782/problem/B)

## Interpetation
Problem Statement: <br>
K people in the room of size n by m. Each position has a number a that represents the height of the cell. A person moves up,down,left,right one unit in one second. The maximum height of the cell is n * m. L ranges from 0 to n * m
Find the minimum time for all L from 0 to n * m.

Main Points:
- Must find shortest distance to cell of height L for any starting point. 
- The shortest distance from two points is given by their manhattan distance

# Approach
## Brute Force
- First arrange it so we can iterate from the highest height cells to lowest i.e., using a unordered_map
- Globally Maintain a vector that is size n * m where vec[i] is the <b>maximum</b> time required to wait for lava level i
- Iterate for every k in K participants and measure the manhattan distance for every cell (n * m) FROM heighest to lowest cell (since we sorted it). For each l take the maximum of the time required by contestant or constenstants so far
    - Notes:
    - Maitain a minimum manhattan distance prev_d
    - If the cell height h is reached with manhattan distance d, check to see if `d < prev_d then min_d = d otherwise min_d = prev_d`. In the vec_k set the best distance to level h is min_d i.e., `vec_k[h] = min_d`
    - When we finish iterating through all cells we will be left with vec_k that has the shortest time required to wait for lava of height l. vec_k[l] = shortest distance to wait for laval height l


Time complexity: O(K * n * m)

Space Complexity: O(n * m)

In terms of time:
K <= 10,000 and m,n <= 700 thus atleast 1,400,000,000 operations, assuming 3 Ghz CPU then 3 operations/1ns  1,400,000,000 operations <= 0.5 seconds 

In terms of memory Total Memory >= 700 * 700 * 32 = 4480000 bits = 5mb

## Implementation

```C++

vector<int> lava_wait_room(vector<vector<int>> &room, vector<pair<int, int>> &positions)
{
    int n = room.size();
    int m = room[0].size();
    vector<int> max_wait(n * m + 1, -1);

    int n_participants = positions.size();
    unordered_map<int, vector<pair<int, int>>> map;

    /* Order the room by cells by height */
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            map[room[i][j]].push_back({i, j});
        }
    }

    /* Determine the time to wait for each participant */
    for (int k = 0; k < n_participants; k++)
    {
        /* make positions 0-indexed*/
        int kpos_x = positions[k].first - 1;
        int kpos_y = positions[k].second - 1;
        /* prev_d records the fastest time to get to a cell of height h, since we are
        iterating largest h to smallest h, it means we can use prev_d for the current h */
        int prev_d = -1;

        for (int l = n * m; l >= 0; l--)
        {
            /* small_d is the shortest wait time achievable by person k to get to a cell of
            height it->first */
            int small_d = prev_d;
            if (map.find(l) != map.end())
            {
                for (auto pos : map[l])
                {
                    int dist = abs(pos.first - kpos_x) + abs(pos.second - kpos_y);
                    if (small_d == -1 || dist < small_d)
                    {
                        small_d = dist;
                    }
                }
            }

            prev_d = small_d;

            if (max_wait[l] == -1 || max_wait[l] < small_d)
            {
                max_wait[l] = small_d;
            }
        }
    }
    return max_wait;
}
```

###  Results 
Unfortunately the brute force solution failes on test case 10. Thus we must find a faster solution. Possibly taking advantage of the 256mb given (Only utilizing 21mb)
![brute_force_floor](./brute_force_floor_lava.png)



## Non Brute Force

