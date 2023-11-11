#include <iostream>
#include <vector>
using namespace std;

int solve_maximum_distance(vector<int> &vec_a, vector<int> &vec_b)
{
    int maxDistance = 0;
    int n = vec_a.size();
    vector<int> memo_1(1 + n, 0);
    vector<int> memo_2(1 + n, 0);
    vector<int> *temp;
    vector<int> *prev = &memo_1; // pointer to pointer
    vector<int> *current = &memo_2;
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {
            /* cout << vec_a[i - 1] << " , " << vec_b[j - 1] << endl; */
            if (vec_a[i - 1] != vec_b[j - 1])
            {
                (*current)[j] = (*prev)[j - 1] + 1;
            }
            else
            {
                (*current)[j] = (*prev)[j - 1];
            }
        }
        temp = prev;
        prev = current;
        current = temp;
        /*
        for (auto v : *(prev))
        {
            cout << v << " ";
        }
        cout << endl;
        */
    }
    int max = 0;
    for (int i = 0; i < n + 1; i++)
    {
        if ((*prev)[i] > max)
        {
            max = (*prev)[i];
        }
    }
    return max;
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
        res = solve_maximum_distance(vec_a, vec_b);
        cout << res << endl;
        vec_a.clear();
        vec_b.clear();
    }
}