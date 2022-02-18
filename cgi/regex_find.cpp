#include <iostream>
#include <iterator>
#include <regex>
#include <iostream>
#include <algorithm>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 3)
    {
        string file_path = argv[1];
        string expr_path = argv[2];
        string src = fstream_readlines(file_path);
        string expr = fstream_readlines(expr_path);
              
        regex src_exp = regex(expr, regex::ECMAScript);
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_default);
        auto end = sregex_iterator(); 
        for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            //remove newline from match
            string m = match.str();
            m.erase(std::remove(m.begin(), m.end(), '\n'), m.end());
            cout << "\"" << m << "\"" << " @ pos (" << match.position() << ", " << match.length() << ")" << endl; 
        }
    }
}


