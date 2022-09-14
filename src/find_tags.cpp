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
        string path = argv[1];
        string src = ifs_read_all(path);

        string cmd = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)";
        string cmds = "\\{\\s*" + cmd + "\\s*\\}";
        string variable = "\\{\\s*\\$([A-Za-z]\\w*)\\s*\\}";               // {$ABC}
        string config =  "\\{\\s*#([A-Aa-z]\\w*)#\\s*\\}";                 // {#ABC#}
        string comment =  "\\{\\s*\\*[\\w\\s\\p]*\\*\\s*\\}";              // {*ABC*}
        string string_literal1 = "(\\\"[\\w\\.]*\\\")";                    // "ABC"
        string string_literal2 = "(\\'[\\w*\\.]*\\')";                     // 'ABC'
        string string_literal = string_literal1 + "|" + string_literal2;

        // cmd params
        string cmd_variable = "\\{(" + cmds + "\\=(" + variable + "|" + string_literal + "))\\}"; // {include=("ABC.cgi")} // {config_load=("ABC.conf")}
        string file = "file=(" + string_literal + ")";
        string array = "\\{\\s*\\$([A-Za-z]+)\\[([0-9]+)\\]\\s*\\}";           // {$abc[0]}
        string tag_with_vairable_modifier = "\\{\\$([A-Za-z]+\\w*|\\w+)\\}";   // {$ABC|abc}
        string vairable_modifier = "\\w+(\\|\\w)*";
                
        std::ostringstream exprs; 
        exprs << cmds << "|" << variable << "|" << array << "|" << config << "|" << file << "|" << string_literal << "|" << comment;
        regex src_exp = regex(exprs.str(), regex::ECMAScript);
              
        sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_exp);
        auto end = sregex_iterator(); 
        for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            cout << match.str() <<  " --> " << match[1] << match[2] << match[3] << match[4] << match[5] << match[6] << match[7] << match[8] << match[9] << match[10] << endl; 
        }
    }
}
