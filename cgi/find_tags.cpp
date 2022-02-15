#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"

using namespace std;

string process_match(smatch& match)
{
    bool comment = match[3].matched;
    bool config = match[4].matched;

    if(comment)
        return "";
    if(config)
    {
        // if(config.find(match.str()));
        //     return config.second();
    }

   
    string cmd = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)";
    return "";
}

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        // todo: validate inputs !
        string path = argv[1];
        string src = fstream_readlines(path);

        string cmds = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)?";
        

        string start = "\\{\\s*(";
        string cmd = "((\\*)|(#))?";
        string ending = ")\\s*\\}";
        string name = "\\s*([\\w\\$]*)\\s*";

        string whole_tag = start + cmd + name + cmd + ending;
        //regex src_exp =  regex("\\{\\s*((|(\\*)|(#))?\\s*([\\w\\$]*)\\s*((\\*)|(#))?)\\s*\\}", regex::ECMAScript);
        regex src_exp =  regex(whole_tag, regex::ECMAScript);
              
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


