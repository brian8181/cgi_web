#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "../src/utility.hpp"

using namespace std;

// Usage
// ./dump <file_path>

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        string src = readlines(path);
        cout << src << endl;
    }
}