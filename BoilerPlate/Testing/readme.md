# Testing Boilerplate code

Testmain.cpp is the main wrapper for running tests.
The only argument it needs is a file that has the following format e.g., <b>args.txt </b>
- <Full/Relative path to TEST ARGUMENT file>
- <Full/Relative path to PROGRAM for testing> i.e., .exe or binary
- <Full/Relative path to TEST SOLUTION file>


 It basically does the following:
- Reads the input test argument file 
- Creates a process running the test program
- Pipes the test arguments into the test program
- Reads and compares the programs output with the solution file

### Setup and Running
1. modify the args.txt file to contain the full paths to test args, program and test solution
2. Check that the piping function is suitable for the program and test (may require tweaking depeding on the how the tests are ran) 

[The processing of input and comparing with arguments could/should be refactored into the PROGRAM]


### Basic runner code for testings
```C++
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

```