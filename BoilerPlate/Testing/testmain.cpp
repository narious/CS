#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

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
    for (int i = 0; i < nCases; i++)
    {
        int vec_len;
        vector<int> vec_a;
        vector<int> vec_b;
    }

    /* Compare the output and check if passes */
    return 0;
}
