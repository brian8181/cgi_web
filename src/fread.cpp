#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"

using namespace std;

// Usage
// ./dump <file_path>

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        string src = fread_test(path);
        cout << src;
    }
}