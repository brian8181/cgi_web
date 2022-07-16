#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "../src/utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    if(argc == 2)
    {
        string path = argv[1];
        string src = readlines(path);

        string start = "\\{\\s*";
        string cmd1 = "\\{\\s*[*#$]\\s*[\\w\\s\\p]*\\}";
        string cmd2 = "[\\*#]?";
        string ending = "\\s*\\}";
        string name = "\\s*[$*#](.*)[*#]?\\s*";
        string whole_tag = start + cmd1 + name + cmd2 + ending;
      
        string cmds = "\\{\\s*(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)\\s*\\}";
        //string variable = "\\{\\s*\\$([A-Za-z]+\\w*)\\b\\s*\\}";         // {$ABC}
        string variable = "\\{\\s*\\$([A-Za-z]\\w*)\\s*\\}";               // {$ABC}
        //string config =  "\\{\\s*#([^\\}]+)#\\s*\\}";                    // {#ABC#}
        string config =  "\\{\\s*#([A-Aa-z]\\w*)#\\s*\\}";                 // {#ABC#}
        //string comment = "\\{\\s*\\*[^\\}]+\\*\\s*\\}";                  // {*ABC*}
        string comment =  "\\{\\s*\\*[\\w\\s\\p]*\\*\\s*\\}";              // {*ABC*}
        string string_literal1 = "(\\\"[\\w\\.]*\\\")";                    // "ABC"
        string string_literal2 = "(\\'[\\w*\\.]*\\')";                     // 'ABC'
        string string_literal = string_literal1 + "|" + string_literal2;

        // cmd params
        string cmd = "(config_load|include|insert|literal|strip|capture|section|assign|debug|eval|fetch|math)";
        string cmd_variable = "\\{(" + cmds + "\\=(" + variable + "|" + string_literal + "))\\}"; // {include=("ABC.cgi")} // {config_load=("ABC.conf")}
        string file = "file=(" + string_literal + ")";
        string array = "\\{\\s*\\$([A-Za-z]+)\\[([0-9]+)\\]\\s*\\}";           // {$abc[0]}
        string tag_with_vairable_modifier = "\\{\\$([A-Za-z]+\\w*|\\w+)\\}";   // {$ABC|abc}
        string vairable_modifier = "\\w+(\\|\\w)*";
                
        //regex src_exp =  regex(variable, regex::ECMAScript);
        //regex src_exp =  regex(config, regex::ECMAScript);
        //regex src_exp =  regex(comment, regex::ECMAScript); 
        //regex src_exp =  regex(cmds, regex::ECMAScript);

        std::ostringstream exprs; 
        //exprs << cmds << "|" << array << "|" << config << "|" << comment;
        //exprs << cmds << "|" << variable << "|" << config << "|" << comment;
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
