// Mon Oct 30 11:55:47 AM CDT 2023

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include "fileio.hpp"

using namespace std;

//map<string, string> get_config(string path);
void  lex(string& s);

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
        lex(src);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading file ... " << e.what() << endl;
    }
    cout << output;
    return 0;
}

void  lex(string& s)
{
    cout << "Lexing..." << endl;

    const string ESCAPE = "\\{[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,]*\\}";
    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    smatch match;

    while(std::regex_search(s, match, exp, std::regex_constants::match_default))
    {
        std::string fmt_match_beg = match.format("<TEXT>$`</TEXT>");
        std::string fmt_match = match.format("<TAG>$&</TAG>");
        s = match.format("$'");
        std::cout << fmt_match_beg << endl;
        std::cout << fmt_match << endl;
    }
    cout << s << endl;

    cout << "End Lexing..." << endl;
}