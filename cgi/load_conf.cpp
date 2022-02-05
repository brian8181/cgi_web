#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(1)
    //if(argc == 1)
    {
        // todo: validate inputs !
        string path = argv[1];
        string src = fstream_readlines(path);

        cout << src << endl;

        string name_exp = "[A-Za-z]+\\w*";
        string value_exp = "\'(\\w+\\)'";
        //regex src_epx = regex("\\{\\s*\\$(" + name_exp + ")\\s*\\}");
        //regex src_exp = regex("^(name_exp)\\s+(value_exp)$");
        regex src_exp = regex("^[\\w_]+\\s+"); 
              
        auto begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 
        
        // for each match
		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            //std::ssub_match sub = match[1];
            //cout << match.str() <<  " --> " << sub.str() << endl;
            cout << match.str() << endl;
        }
    }
}