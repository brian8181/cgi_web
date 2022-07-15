#include <iostream>
#include <iterator>
#include <regex>
#include <iostream>
#include <algorithm>
#include <string>
#include "../src/main.hpp"
#include "../src/utility.hpp"

using namespace std;

int parse_options(int argc, char* argv[])
{
    // todo check params
    if(argc == 3)
    {
        string expr_path = argv[1];
        string file_path = argv[2];
        string expr = readlines(expr_path);
        string src = readlines(file_path);
                        
        regex src_exp = regex(expr, regex::ECMAScript);
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_default);
        sregex_iterator end = sregex_iterator(); 
        for (sregex_iterator iter = begin; iter != end; ++iter)
        {
            smatch match = *iter;
            //remove newline from match
            string m = match.str();
            m.erase(std::remove(m.begin(), m.end(), '\n'), m.end());
            cout << "\"" << m << "\"" << " @ pos (" << match.position() << ", " << match.length() << ")" << endl; 
        }
    }
    return 0;
}
