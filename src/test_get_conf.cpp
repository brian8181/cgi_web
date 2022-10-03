#include <iostream>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    // get pairs / configuration
    string path = "./test/test_get_conf.txt"; // default
    if(argc == 2)
    {
        path.clear();
        path = argv[1];
    }

    // print pairs / configuration
    map<string, string> pairs = get_config(path);
    map<string, string>::iterator end = pairs.end();
    for(map<string, string>::iterator iter = pairs.begin(); iter != end; ++iter)
    {
        cout << iter->first << " = " << iter->second << endl;
    }
}
