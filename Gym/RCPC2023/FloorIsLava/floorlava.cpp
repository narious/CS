#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

void print_vector(vector<int> &vec);
void print_vector(vector<pair<int, int>> &vec);
void print_2d_vector(vector<vector<int>> &map);
int binary_search_lower(vector<int> &array, int start, int end, int target);

vector<int> lava_wait_room_brute_force(vector<vector<int>> &room, vector<pair<int, int>> &positions)
{
    int n = room.size();
    int m = room[0].size();
    vector<int> max_wait(n * m + 1, -1);
    /*
    for (int i = 0; i < n; i++)
    {
        print_vector(room[i]);
    }
    print_vector(positions);
    */

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
    vector<int> res(n * m, -1);

    /* room rotated 45 degree right*/
    vector<vector<int>> room_rot(n + m - 1, vector<int>());
    /* Contains the RMQ for all rows */
    vector<vector<vector<int>>> row_memo;
    /* Contains the RMQ for all cols */
    vector<vector<vector<int>>> col_memo;

    /* rotate the room (left side) */
    for (int i = 0; i < n; i++)
    {
        int offset = n - i - 1;
        for (int k = 0; k < offset; k++)
        {
            room_rot[i].push_back(0);
        }

        for (int j = 0; j < m; j++)
        {
            if (i - j < 0)
            {
                break;
            }
            room_rot[i].push_back(room[i - j][j]);
            room_rot[i].push_back(0);
        }

        room_rot[i].pop_back();
        int padding = n + m - room_rot[i].size() - 1;
        for (int k = 0; k < padding; k++)
        {
            room_rot[i].push_back(0);
        }
    }
    /* rotate the room (bottom side) */
    for (int i = 1; i < m; i++)
    {
        /* add the offset */
        for (int k = 0; k < i; k++)
        {
            room_rot[i + n - 1].push_back(0);
        }

        for (int j = 0; j < m; j++)
        {
            if (i + j >= m || n - j - 1 < 0)
            {
                break;
            }
            room_rot[i + n - 1].push_back(room[n - j - 1][i + j]);
            room_rot[i + n - 1].push_back(0);
        }

        room_rot[i + n - 1].pop_back();

        int padding = n + m - room_rot[i + n - 1].size() - 1;
        for (int k = 0; k < padding; k++)
        {
            room_rot[i + n - 1].push_back(0);
        }
    }
    /* generate all RMQ on the rows and column*/
    return res;
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

/* To export to common */
void print_vector(vector<int> &vec)
{
    for (auto val : vec)
    {
        cout << val << " ";
    }
    cout << endl;
}

void print_vector(vector<pair<int, int>> &vec)
{
    for (auto val : vec)
    {
        cout << val.first << " , " << val.second << endl;
    }
    cout << endl;
}

void print_2d_vector(vector<vector<int>> &map)
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

// Any lower
int binary_search_lower(vector<int> &array, int start, int end, int target)
{
    int mid = 0;
    while (start < end)
    {
        mid = start / 2 + end / 2;
        // cout << start << " " << end << " " << mid << endl;
        if (array[mid] <= target)
        {
            // Do this to get the lower target
            end = mid;
        }
        else if (array[mid] > target)
        {
            start = mid + 1;
        }
    }
    if (array[start] == target)
    {
        return start - 1;
    }
    else if (array[start] < target)
    {
        return start;
    }

    return -1;
}