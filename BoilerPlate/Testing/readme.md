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