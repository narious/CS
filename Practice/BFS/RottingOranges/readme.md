# [Rotting Oranges](https://leetcode.com/problems/rotting-oranges/description/?envType=study-plan-v2&envId=leetcode-75)

### Approach
The rotting oranges problem describes a graph containing rotten oranges. Since each "tick" the rotten aura expands from preexisting rotten oranges we can observe a expanding BFS pattern. This leads to the immediate implemention of BFS.

Some common edgecases to consider are:
- No Fresh oranges then return 0
- No Rotton oranges but some fresh then return -1
- Otherwise run as normal 

### Complexity
- Time complexity O(M + N) : BFS including all edges and nodes
- Space Complexity O(N) : Queue size up to number of nodes

#### Score
- 3ms (87.95%)
- 13.3mb (92.25%)
```C++
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int minutes = -1;
        int nRotten = 0;
        int mRotten = 0;
        int nFresh = 0; // Records number of fresh oranges
        int x;
        int y; 
        int x_size = grid.size();
        int y_size = grid[0].size();
        queue<pair<int, int>> rotten;
        // Add all rotten to the initial queue
        for (x = 0; x < x_size; x++)
        {
            for (y = 0; y < y_size; y++)
            {
                if (grid[x][y] == 2) 
                {
                    rotten.push( {x, y});
                    nRotten += 1;
                }
                else if (grid[x][y] == 1)
                {
                    nFresh += 1;
                }
            }
        }
        // If there are no fresh oranges then zero
        if (nFresh == 0) { return 0; }

        while(rotten.size() > 0)
        {
            pair<int, int> nxt = rotten.front();
            rotten.pop();
            nRotten -= 1;
            x = nxt.first;
            y = nxt.second;
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    // Removes -1,1 1,-1 1,1 -1,-1 0,0 (all diagonal and centre)
                    if (abs(dx) == abs(dy)) { continue; }
                    // Out of bounds
                    if (x + dx < 0 || x + dx >= x_size || y + dy < 0 || y + dy >= y_size)
                    {
                        continue;
                    }

                    if (grid[x + dx][y + dy] == 1) // fresh orange!
                    {
                        rotten.push({x + dx, y + dy});
                        grid[x + dx][y + dy] = 2; // Mark as rotton!! bleh
                        mRotten += 1;
                        nFresh -= 1;
                    }
                }
            }
            if (nRotten == 0) 
            {
                nRotten = mRotten;
                mRotten = 0;
                minutes += 1;
            }
        }

        if (nFresh == 0)
        {
            return minutes;
        }
        // fresh oranges exist
        return -1; 
    }
};
```

