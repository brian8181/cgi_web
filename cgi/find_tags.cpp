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
        string path = argv[1];
        string src = fstream_readlines(path);

        // string cmds = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)?";
        
        // string start = "\\{\\s*(";
        // string cmd = "((\\*)|(#))?";
        // string ending = ")\\s*\\}";
        // string name = "\\s*([\\w\\$]*)\\s*";

        // string start = "\\{\\s*";
        // string cmd1 = "\\{\\s*[*#$]\\s*[\\w\\s\\p]*\\}";
        // string cmd2 = "[\\*#]?";
        // string ending = "\\s*\\}";
        // string name = "\\s*[$*#](.*)[*#]?\\s*";
        // //string whole_tag = start + cmd1 + name + cmd2 + ending;

        // string whole_tag = start + cmd + name + cmd + ending;
        std::ostringstream exprs;
        string cmds = "\\{\\s*((config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math))?\\s*\\}";
        string parm = "\\{\\s*\\$([A-Za-z]+\\w*)\\b\\s*\\}";
        string config =  "\\{\\s*(#)([^\\}]+)\\1\\s*\\}";
        string comment = "\\{\\s*(\\*[^\\]+)\\*\\s*\\}";

        //regex src_exp =  regex("\\{\\s*((|(\\*)|(#))?\\s*([\\w\\$]*)\\s*((\\*)|(#))?)\\s*\\}", regex::);
        //regex src_exp =  regex("\\s*(one\\=|two\\=|three\\=|\\$[A-Za-z]+\\w*)\\s*", regex::ECMAScript);
        //regex src_exp = regex(parm + "|" + comment + "|" + config);
        //exprs << start << cmd1 << name << cmd2 << ending;
        exprs << cmds << "|" << parm << "|" << config << "|" << comment << endl;
        regex src_exp =  regex(exprs.str(), regex::ECMAScript);
              
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 

        regex_search(src.begin(), src.end(), src_exp);
        
		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            
            bool comment = match[3].matched;
            bool config = match[4].matched;

            std::ssub_match sub = match[1];
            cout << match.str() <<  " --> " << trim(sub.str()) << " : " << comment << " : " << config << endl;
        }
    }
}


