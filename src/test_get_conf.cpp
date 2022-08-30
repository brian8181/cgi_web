#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    string path = "../test/test_get_conf.txt";
    map<string, string> pairs = get_config(path);

    map<string, string>::iterator end = pairs.end();
    for(map<string, string>::iterator iter = pairs.begin(); iter != end; ++iter)
    {
        cout << iter->first << " = " << iter->second << endl;
    }
}
