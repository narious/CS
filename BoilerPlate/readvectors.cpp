
#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int> &vec_a, vector<int> &vec_b)
{
    return -1;
}

int main()
{
    int nProblems;
    int length;
    vector<int> vec_a;
    vector<int> vec_b;
    int val;
    int res;
    cin >> nProblems;
    for (int i = 0; i < nProblems; i++)
    {
        cin >> length;
        for (int j = 0; j < length; j++)
        {
            cin >> val;
            vec_a.push_back(val);
        }
        for (int k = 0; k < length; k++)
        {
            cin >> val;
            vec_b.push_back(val);
        }
        res = solve(vec_a, vec_b);
    }
}