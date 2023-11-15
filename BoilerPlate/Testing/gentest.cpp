#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>

using namespace std;

vector<int> gen_random_vector(int vec_len, int min, int max);
vector<int> permeate_vector(vector<int> &src, int iterations);
void generate_vector_test(ofstream &ostream, int n_vec, int len_vec, bool usePermutation);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "format: gentest <testfilename> [...<ntest> <generic var>]" << endl;
        return 0;
    }

    int nTest = 1;
    int testLen = 10;
    if (argc > 2)
    {
        nTest = atoi(argv[2]);
    }
    if (argc > 3)
    {
        testLen = atoi(argv[3]);
    }

    /* initialize random seed: */
    srand(time(NULL));

    ofstream myfile(argv[1]);
    if (myfile.is_open())
    {
        /* This part can be modularized i.e., switch out gen function*/
        myfile << nTest << "\n";
        for (int i = 0; i < nTest; i++)
        {
            generate_vector_test(myfile, 1, testLen, true);
        }
        myfile.close();
    }
    return 0;
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