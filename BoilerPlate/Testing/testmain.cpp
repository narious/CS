#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please pass in the name of the argument file" << endl;
        cout << "Argument file format:\n"
             << "<PathTestArgumentFile>\n<PathProgram>\n<PathTestArgAnswers>";
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

    /* Open a process to the program */
    FILE *pipe = popen(arg_lines[1].c_str(), "r+");
    char buffer[128];

    /* Start piping the test arg file into the program process */
    ifstream infile(arg_lines[0]);

    // TODO abstract this out to a seperate module that gets imported since it depends on each test case i.e., two vector
    int count = 0;
    while (getline(infile, line))
    {
        cout << line << endl;
        if (count == 0)
        {
            // number of test cases
            fprintf(pipe, line.c_str());
            count += 1;
        }
        //  send vec_b and read output
        else if (count == 3)
        {
            fprintf(pipe, line.c_str());
            fflush(pipe);

            while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
            {
                output.push_back(buffer);
                cout << buffer << endl;
            }
            count = 1;
        }
        else // sending size and vec_a
        {
            fprintf(pipe, line.c_str());
            count += 1;
        }
    }

    pclose(pipe);

    /* Compare the output and check if passes */
    return 0;
}
