#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        string expr_path = argv[1];
        string file_path = argv[2];

        replace_tags2(expr_path, file_path);
    }
}
