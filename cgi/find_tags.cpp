#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        // todo: validate inputs !
        string path = argv[1];
        string src = fstream_readlines(path);
        //regex src_epx = regex(".*", regex::ECMAScript);
        regex src_exp =  regex("\\{\\s*(((\\*)|(#))?\\s*([\\w\\$]*)\\s*((\\*)|(#))?)\\s*\\}", regex::ECMAScript);
              
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_not_null);
        auto end = sregex_iterator(); 
        
		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            
            bool comment = match[3].matched;
            bool config = match[4].matched;

            std::ssub_match sub = match[5];
            cout << match.str() <<  " --> " << trim(sub.str()) << " : " << comment << " : " << config << endl;
        }
    }
}