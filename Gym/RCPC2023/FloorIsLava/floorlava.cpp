#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include "include/common.h"

using namespace std;
int get_highest_step(pair<int, int> &pos, int n, int m, int r, vector<vector<vector<int>>> &row_memo,
                     vector<vector<vector<int>>> &col_memo, vector<vector<int>> &room_rot);

vector<int> lava_wait_room_brute_force(vector<vector<int>> &room, vector<pair<int, int>> &positions)
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
        cout << k << endl;
        /* make positions 0-indexed*/
        int kpos_x = positions[k].first - 1;
        int kpos_y = positions[k].second - 1;
        /* prev_d records the fastest time to get to a cell of height h, since we are
        iterating largest h to smallest h, it means we can use prev_d for the current h */
        int prev_d = -1;
        for (int l = m * n; l >= 0; l++)
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

vector<int> lava_wait_room_rmq(vector<vector<int>> &room, vector<pair<int, int>> &participants)
{
    int n = room.size();
    int m = room[0].size();
    int K = participants.size();
    vector<int> time_wait(n + m, -1);
    vector<int> res(n * m, -1);

    /* room rotated 45 degree right*/
    vector<vector<int>> room_rot(n + m - 1, vector<int>());
    /* Contains the RMQ for all rows */
    vector<vector<vector<int>>> row_memo;
    /* Contains the RMQ for all cols */
    vector<vector<vector<int>>> col_memo;

    int vertOffset = n - 1;
    /* fill in all the offsets */
    for (int i = 0; i < m + n - 1; i++)
    {
        if (i < n)
        {
            for (int k = 0; k < n - 1 - i; k++)
            {
                room_rot[i].push_back(0);
            }
        }
        else
        {
            for (int k = 0; k < i - n + 1; k++)
            {
                room_rot[i].push_back(0);
            }
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j < m; j++)
        {
            room_rot[vertOffset + j].push_back(room[i][j]);
            room_rot[vertOffset + j].push_back(0);
        }
        vertOffset -= 1;
    }

    /* fill all the 0 in the end */
    for (int i = 0; i < n + m - 1; i++)
    {
        room_rot[i].pop_back();
        if (i < m)
        {
            for (int k = 0; k < m - 1 - i; k++)
            {
                room_rot[i].push_back(0);
            }
        }
        else
        {
            for (int k = 0; k < i - m + 1; k++)
            {
                room_rot[i].push_back(0);
            }
        }
    }
    /* generate all RMQ on the rows and column
    where row_memo[i][j][k] is the ith rows maximum from [k, 2^j] */
    int max_row = (int)log(n + m - 1);
    for (int i = 0; i < row_memo.size(); i++)
    {
        vector<vector<int>> memo;

        for (int j = 0; j < max_row; j++)
        {
            for (int k = 0; k < n + m - 1; k++)
            {
                // TODO
            }
        }
    }

    /* find the highest height for each steps for each pariticpant */
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < n + m - 1; r++)
        {
            int highest_step = get_highest_step(participants[k], n, m, r, row_memo, col_memo, room_rot);
            /* record the slowest person */
            if (time_wait[r] > highest_step)
            {
                time_wait[r] = highest_step;
            }
        }
    }

    /* resolve the time waited to maximum heigh reachable when waiting r */
    int lava_height = 1;
    for (int i = 0; i < time_wait.size(); i++)
    {
        while (time_wait[i] >= lava_height)
        {
            res[lava_height] = i;
            lava_height += 1;
        }
    }

    return res;
}

pair<int, int> get_diag_position(pair<int, int> &pos, int n, int m)
{
    int x = pos.first;
    int y = pos.second;
    /* offset then move */
    pair<int, int> dpos = {x + y, n - 1 - x + y};
    return dpos;
}

int get_max_value_rmq(vector<vector<int>> &memo, int start, int end, vector<vector<int>> &room_rot)
{
    // TODO
    int j = (int)log(end - start + 1);
    return 0;
}

int get_highest_step(pair<int, int> &pos, int n, int m, int r, vector<vector<vector<int>>> &row_memo,
                     vector<vector<vector<int>>> &col_memo, vector<vector<int>> &room_rot)
{
    // TODO
    // Iterator through all the diagonal positions
}

int _main()
{
    int n;
    int m;
    int k;
    cin >> n >> m >> k;
    vector<vector<int>> room(n, vector<int>());
    vector<pair<int, int>> positions;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int val;
            cin >> val;
            room[i].push_back(val);
        }
    }

    for (int i = 0; i < k; i++)
    {
        int posx;
        int posy;
        cin >> posx >> posy;
        positions.push_back({posx, posy});
    }

    vector<int> res = lava_wait_room_rmq(room, positions);

    for (int i = 1; i <= n * m; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please supply test file name with test" << endl;
        return 0;
    }
    int n;
    int m;
    int k;
    ifstream infile(argv[1]);
    /* Read in file*/
    infile >> n >> m >> k;
    vector<vector<int>> room(n, vector<int>());
    vector<pair<int, int>> positions;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int val;
            infile >> val;
            room[i].push_back(val);
        }
    }

    for (int i = 0; i < k; i++)
    {
        int posx;
        int posy;
        infile >> posx >> posy;
        positions.push_back({posx, posy});
    }

    vector<int> res = lava_wait_room_rmq(room, positions);

    for (int i = 1; i <= n * m; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
