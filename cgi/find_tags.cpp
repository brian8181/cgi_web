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
        string src = readlines(path);

        // string start = "\\{\\s*";
        // string cmd1 = "\\{\\s*[*#$]\\s*[\\w\\s\\p]*\\}";
        // string cmd2 = "[\\*#]?";
        // string ending = "\\s*\\}";
        // string name = "\\s*[$*#](.*)[*#]?\\s*";
        // string whole_tag = start + cmd1 + name + cmd2 + ending;
      
        string cmds = "\\{\\s*(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)\\s*\\}";
        string param = "\\{\\s*\\$([A-Za-z]+\\w*)\\b\\s*\\}"; // {$ABC}
        string config =  "\\{\\s*#([^\\}]+)#\\s*\\}";         // {#ABC#}
        string comment = "\\{\\s*\\*([^\\}]+)\\*\\s*\\}";     // {*ABC*}
        string string_literal1 = "\\\"(.*)\\\""; // "ABC"
        string string_literal2 = "\\'(.*)\\'";   // 'ABC'
        string string_literal = string_literal1 + "|" + string_literal2;

        // cmd params
        string cmd = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)";
        string cmd_params = "\\{(" + cmds + "\\=(" + param + "|" + string_literal + "))\\}"; // {include=("ABC.cgi")} // {config_load=("ABC.conf")}
        string file = "file=(" + string_literal + ")";
        
        //regex src_exp =  regex(param, regex::ECMAScript);
        //regex src_exp =  regex(config, regex::ECMAScript);
        //regex src_exp =  regex(comment, regex::ECMAScript);
        //regex src_exp =  regex(cmds, regex::ECMAScript);

        std::ostringstream exprs; 
        exprs << cmds << "|" << param << "|" << config << "|" << comment;
        regex src_exp = regex(exprs.str(), regex::ECMAScript);
              
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 
        for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            cout << match.str() <<  " --> " << match[1] << " : " << match[2] << " : " << match[3] << " : " << match[4] << endl; 
        }
    }
}


