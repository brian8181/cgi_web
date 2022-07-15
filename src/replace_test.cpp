#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "../src/utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        replace_tags(path);
    }
}