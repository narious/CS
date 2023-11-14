#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> gen_random_vector(int vec_len);
vector<int> permeate_vector(vector<int> &src);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "format: gentest <testfilename> [...<ntest> <generic var>]" << endl;
        return 0;
    }
    int nTest = 1;
    int testLen = 5;
    if (argc > 1)
    {
        nTest = atoi(argv[1]);
    }
    if (argc > 2)
    {
        testLen = atoi(argv[2]);
    }

    ofstream myfile("test.txt");
    if (myfile.is_open())
    {
        /* This part can be modularized i.e., switch out gen function*/
        myfile << nTest << "\n";
        for (int i = 0; i < nTest; i++)
        {
        }
        myfile.close();
    }
    return 0;
}

/* Vector test generation module */
void generate_vector_test(ofstream ostream, int n_vec, int len_vec, bool usePermutation)
{
}

vector<int> gen_random_vector(int vec_len)
{
    vector<int> res;
}

vector<int> permeate_vector(vector<int> &src)
{
}