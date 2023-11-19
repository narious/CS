#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

vector<int> gen_random_vector(int vec_len, int min, int max);
vector<int> permeate_vector(vector<int> &src, int iterations);
int get_random_num(int min, int max);
void generate_vector_test(ofstream &ostream, int n_vec, int len_vec, bool usePermutation);
void generate_grid_test(ofstream &ostream, int n, int m, int val_min, int val_max);
void generate_pairs(ofstream &ostream, int n, pair<int, int> x_range, pair<int, int> y_range);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "format: gentest <testfilename> [...<ntest> <generic var>]" << endl;
        return 0;
    }

    /* initialize random seed: */
    srand(time(NULL));

    ofstream myfile(argv[1]);
    if (myfile.is_open())
    {
        /* This part can be modularized i.e., switch out gen function*/

        myfile << 700 << " " << 700 << " " << 10000 << "\n";
        generate_grid_test(myfile, 700, 700, 1, 140000);
        generate_pairs(myfile, 10000, {1, 700}, {1, 700});
        myfile.close();
    }
    return 0;
}

/* Grid generation module */

void generate_grid_test(ofstream &ostream, int n, int m, int val_min, int val_max)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            ostream << get_random_num(val_min, val_max) << " ";
        }
        ostream << endl;
    }
}

/* Pairs generation module */
void generate_pairs(ofstream &ostream, int n, pair<int, int> x_range, pair<int, int> y_range)
{
    for (int i = 0; i < n; i++)
    {
        int x = get_random_num(x_range.first, x_range.second);
        int y = get_random_num(y_range.first, y_range.second);
        ostream << x << " " << y << endl;
    }
}

/* Vector test generation module */
void generate_vector_test(ofstream &ostream, int n_vec, int len_vec, bool usePermutation)
{
    vector<int> vec;
    ostream << len_vec << "\n";
    for (int i = 0; i < n_vec; i++)
    {
        vec = gen_random_vector(len_vec, 0, 100);
        for (auto v : vec)
        {
            ostream << v << " ";
        }
        ostream << endl;
        if (usePermutation)
        {
            vec = permeate_vector(vec, (int)(len_vec / 2));
            for (auto v : vec)
            {
                ostream << v << " ";
            }
            ostream << endl;
        }
    }
}

vector<int> gen_random_vector(int vec_len, int min, int max)
{
    vector<int> res;
    for (int i = 0; i < vec_len; i++)
    {
        int r_num = rand() % (max - min);
        r_num += min;
        res.push_back(r_num);
    }
    return res;
}

vector<int> permeate_vector(vector<int> &src, int iterations)
{
    vector<int> res(src);
    int temp;
    int len = src.size();
    for (int i = 0; i < iterations; i++)
    {
        int a = rand() % len;
        int b = rand() % len;
        temp = res[a];
        res[a] = res[b];
        res[b] = temp;
    }

    return res;
}

int get_random_num(int min, int max)
{
    return rand() % (max - min + 1) + min;
}