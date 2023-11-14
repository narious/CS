#include <iostream>
#include <vector>
#include <fstream>

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
/*
int solve_brute_force(vector<int> &vec_a, vector<int> &vec_b)
{
    int k = vec_a.size();
    for (int i = 0; i < vec_a.size(); i++)
    {

    }
}
*/

int Solution()
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
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please pass in the name of the argument file" << endl;
        cout << "Argument file format:\n"
             << "<PathTestArgumentFile>\n<PathTestArgAnswers>";
        return 0;
    }
    /* Read the args file */
    ifstream args(argv[1]);
    vector<string> arg_lines;
    vector<string> output;
    string line;
    while (getline(args, line))
    {
        arg_lines.push_back(line);
    }

    /* Start piping the test arg file into the program process */
    ifstream infile(arg_lines[0]);

    // Send total number of test cases
    int nCases;
    vector<int> results;
    infile >> nCases;
    int vec_len;
    vector<int> vec_a;
    vector<int> vec_b;
    for (int i = 0; i < nCases; i++)
    {

        infile >> vec_len;
        int temp;
        for (int j = 0; j < vec_len; j++)
        {
            infile >> temp;
            vec_a.push_back(temp);
        }
        for (int j = 0; j < vec_len; j++)
        {
            infile >> temp;
            vec_b.push_back(temp);
        }

        // Read in the vector then run the test
        int res = solve_maximum_distance(vec_a, vec_b);
        results.push_back(res);
        vec_a.clear();
        vec_b.clear();
    }

    /* Compare the output and check if passes */
    ifstream solfile(arg_lines[1]);
    int sol;
    int nPass = 0;
    for (int i = 0; i < nCases; i++)
    {
        solfile >> sol;
        if (sol == results[i])
        {
            cout << "Pass: " << sol << endl;
            nPass += 1;
        }
        else
        {
            cout << "Fail: " << sol << "!=" << results[i] << endl;
        }
    }
    cout << nPass << "/" << nCases << endl;
    return 0;
}
