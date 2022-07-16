#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>
#include "../src/utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        string path = argv[1];
        string exp = argv[2];
        int count = atoi(argv[3]);
        
        string src = readlines(path);
        regex src_exp = regex(exp); 
                      
        auto begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 
        
        for (sregex_iterator iter = begin; iter != end; ++iter)
        {
            smatch match = *iter;
            string value = match[3].str() + match[5].str() + match[7].str();
            cout << "Match: --> " << match.str() <<  endl;
            for(int i = 0; i < count; ++i)
            {
               cout << match[i].str() << endl;
            }
        }
    }
}
