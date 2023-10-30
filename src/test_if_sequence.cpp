#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "patterns.hpp"
#include "fileio.hpp"
#include "utility.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;


string if_sequence(const string &src);
string if_sequence_with_text(const string &src);

int main(int argc, char *argv[])
{
    string root_path = "../conf/test_if_sequence.conf";
    map<string, string> pairs = get_config(root_path);
    const string project_folder = pairs["project_folder"];
    const string default_template = pairs["default_template"];
    const string conf_path = pairs["conf_path"];

    // check for input or use default
    string template_name = default_template;
    const string path = project_folder + "./test/templates/" + template_name;
    if (argc == 2)
    {
        template_name.clear();
        template_name = argv[1];
    }

    // read file
    std::ifstream ifile_strm(path);
    std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());

    if (src == "")
    {
        cout << "Error reading template, path (" + path + ") ..." << endl;
        return 0;
    }

    string s = if_sequence(src);
    cout << s;
}

// find if sequence
string if_sequence(const string &src)
{
    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        // output text
        if (match[3].matched)
        {
            // if text
            output += match[3].str() + "\n";
        }
        else
        {
            // if text
            if (match[4].matched)
            {
                output += match[4].str() + "\n";
                // else text
                if (match[5].matched)
                    output += match[5].str() + "\n";
            }
        }
    }
    return output;
}

// find if_sequence with text!
string if_sequence_with_text(const string &src)
{
    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int match_beg_pos = match.position();

        // outout begin -> match
        string pre_match_src = src.substr(src_beg_pos, match_beg_pos - src_beg_pos);
        output += pre_match_src;

        std::ssub_match sub = match[1];
        string tmp_str = sub.str();
        string tag(tmp_str.substr(1, tmp_str.size() - 1));
        // output text
        output += tag;

        src_beg_pos = match_beg_pos + match.length();
    }
    return output;
}
