#include <vector>
#include <iostream>
#include "../include/Common.h"
using namespace std;

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
        cout << val.first << " , " << val.second << " ";
    }
    cout << endl;
}

int binary_search_lower(vector<int> &array, int start, int end, int target)
{
    int mid = 0;
    while (start < end)
    {
        mid = start / 2 + end / 2;
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
    return start;
}