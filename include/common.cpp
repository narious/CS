#include <vector>
#include <iostream>
#include "common.h"
using namespace std;

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

/* todo fix */
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