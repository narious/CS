#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <algorithm>
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

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;

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

    cout << "rot_room" << endl;
    print_2d_vector(room_rot);

    /* generate all RMQ on the rows and column
    where row_memo[i][j][k] is the ith rows maximum from [k, 2^j] */
    int rot_dim = room_rot.size();
    int max_pow = (int)log2(rot_dim) + 1;

    /* iterator for each row in the rot room */
    for (int rowMode = 0; rowMode <= 1; rowMode++)
    {
        for (int i = 0; i < rot_dim; i++)
        {
            vector<vector<int>> memo(rot_dim, vector<int>(max_pow, 0));

            for (int j = 0; j < max_pow; j++)
            {
                for (int k = 0; k < rot_dim; k++)
                {
                    if (j == 0)
                    {
                        memo[k][j] = k;
                    }
                    else
                    {
                        int span = k + (int)pow(2, j - 1);
                        span = span < rot_dim ? span : rot_dim - (int)pow(2, j - 1);

                        if (rowMode == 1)
                        {
                            x1 = i;
                            x2 = i;
                            y1 = memo[k][j - 1];
                            y2 = memo[span][j - 1];
                        }
                        else
                        {
                            x1 = memo[k][j - 1];
                            x2 = memo[span][j - 1];
                            y1 = i;
                            y2 = i;
                        }

                        int a = room_rot[x1][y1];
                        int b = room_rot[x2][y2];

                        if (rowMode == 0)
                        {
                            memo[k][j] = a < b ? x2 : x1;
                        }
                        else
                        {
                            memo[k][j] = a < b ? y2 : y1;
                        }
                    }
                }
            }

            if (rowMode == 0)
            {
                col_memo.push_back(memo);
            }
            else
            {
                row_memo.push_back(memo);
            }
        }
    }

    /* find the highest height for each steps for each pariticpant */
    for (int k = 0; k < K; k++)
    {
        for (int r = 0; r < n + m - 1; r++)
        {
            int highest_step = get_highest_step(participants[k], n, m, r, row_memo, col_memo, room_rot);
            cout << "r=" << r << " highest step " << highest_step << endl;
            if (time_wait[r] > highest_step)
            {
                time_wait[r] = highest_step;
            }
        }
    }

    /* resolve the time waited to maximum heigh reachable when waiting r */

    /*
    int lava_height = 1;
    for (int i = 0; i < time_wait.size(); i++)
    {
        while (time_wait[i] >= lava_height)
        {
            res[lava_height] = i;
            lava_height += 1;
        }
    }
    */

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

// returns the value
int get_max_value_rmq(vector<vector<int>> &memo, int start, int end, vector<vector<int>> &room_rot, bool isRow, int index)
{
    int j = (int)log(end - start + 1);
    int vala = 0;
    int valb = 0;

    int a = memo[start][j];

    if (j == 0)
    {
        return isRow ? room_rot[index][a] : room_rot[a][index];
    }

    int b = memo[end - pow(2, j - 1)][j - 1];
    if (isRow)
    {
        vala = room_rot[index][a];
        valb = room_rot[index][b];
    }
    else
    {
        vala = room_rot[a][index];
        valb = room_rot[b][index];
    }
    return vala > valb ? vala : valb;
}

int get_highest_step(pair<int, int> &pos, int n, int m, int r, vector<vector<vector<int>>> &row_memo,
                     vector<vector<vector<int>>> &col_memo, vector<vector<int>> &room_rot)
{
    int max = 0;
    int temp = 0;
    int start = 0;
    int end = 0;
    cout << r << endl;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (abs(i) == abs(j))
            {
                continue;
            }
            cout << i << "," << j << endl;
            cout << "normal: " << pos.first << " " << pos.second << endl;
            pair<int, int> kpos(pos.first + i * r, pos.second + j * r);
            cout << "shifted: " << kpos.first << " " << kpos.second << endl;

            if (kpos.first < 0 || kpos.first >= n || kpos.second < 0 || kpos.second >= m)
            {
                continue;
            }

            pair<int, int> newPos = get_diag_position(kpos, n, m);
            cout << "diagpos: " << newPos.first << " " << newPos.second << endl;

            bool isRow = abs(i) > abs(j);
            /* determining the range room_rot */
            int pivot = isRow ? newPos.second : newPos.first; // pivot is the index within that row or column to be used
            int index = isRow ? newPos.first : newPos.second; // index is the row or column we are focusing on
            if (i < 0 || j > 0)
            {
                start = std::max(pivot - r * 2, 0); // 2 * r Since after 45 deg rotate the matrix "expands"
                end = pivot;
            }
            else
            {
                start = pivot;
                end = min(pivot + r * 2, m + n - 1);
            }
            cout << "start: " << start << " end: " << end << endl;

            temp = get_max_value_rmq(isRow ? row_memo[index] : col_memo[index], start, end, room_rot, isRow, index);
            cout << "rmq: " << temp << endl;
            if (temp > max)
            {
                max = temp;
            }
        }
    }
    return max;
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
