# Common functions to be used
Compile the file using 

`g++ -c -std=c++17 <filename.cpp>`

Then link to the original binary by having this path as one of the search libary

For including the header file we need to use -I + relative or absolute path

For including the library common.a we need to use -L hence the full common would be (using either full path or relative path)

`g++ -std=c++17 -L/Full/Path/To/library -I./../../../ -o etc etc.cpp`

[For more info GNU docs](https://gcc.gnu.org/onlinedocs/gcc/Directory-Options.html)