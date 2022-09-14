#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>
#include "utility.hpp"

using namespace std;

// Usage
// ./load_conf.cgi ../test/conf_test.txt

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        string src = ifs_read_all(path);

        string name_exp = "([A-Za-z]+\\w*)";
        string value_exp = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
        regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp); 
                      
        auto begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 
        
        for (auto iter = begin; iter != end; ++iter)
        {
            smatch match = *iter;
            string value = match[3].str() + match[5].str() + match[7].str();
            cout << "Match: --> " << match.str() <<  "; Name: --> " << match[1].str() << "; Value: --> " << value << endl;
        }
    }
}
