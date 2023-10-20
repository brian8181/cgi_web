#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include "fileio.hpp"

using namespace std;

string lex_all(const string &src);

int main(int argc, char *argv[])
{
    std::filesystem::path path(argv[0]);
    string root_path = path.replace_extension("conf");
    map<string, string> pairs = get_config(root_path);

    const string project_folder = pairs["project_folder"];
    const string template_folder = pairs["template_folder"];
    const string default_template = pairs["default_template"];
    
    // check for input or use default
    string template_name = default_template;
    if (argc > 1)
    {
        template_name.clear();
        template_name = argv[1];
    }

    const string file_path = template_folder + template_name;
    string output;
    try
    {
        string src = ifs_read_all(file_path);
        output = lex_all(src);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading file ... " << e.what() << endl;
    }
    cout << output;
}

// find text & tags
string lex_all(const string &src)
{
    const string ESCAPE = "\\{[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,]*\\}";
    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    sregex_iterator end = sregex_iterator(src.end(), src.end(), exp, std::regex_constants::match_default);

    int matches = 0;
    string output;
    sregex_iterator prev_iter = end;

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        smatch pmatch = *prev_iter;

        int match_beg_pos = match.position();
        int match_end_pos = 0;
         
        if(prev_iter != end)
        {
            match_end_pos = prev_iter->position() + prev_iter->length();
        }
        // get from end of last match (src_beg_pos) to begin of current
        string text = src.substr(match_end_pos, match_beg_pos);
        if(src[match_beg_pos] == '\n')
            text += '\n';

        string t = "testing";
        t += '\n';
        t += "new_line";
        cout << t << endl;

        output += "TEXT:" + text;

        string token = match.str();
        output += "TAG:" + token;

        prev_iter = iter;
    }
    return output;
}
