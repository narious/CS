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