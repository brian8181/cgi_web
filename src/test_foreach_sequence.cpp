#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "fileio.hpp"
#include "utility.hpp"

using namespace std;

string FOREACH_SEQUENCE = "";
string foreach_sequence(const string &src);
string foreach_sequence_with_test(const string &src);

int main(int argc, char *argv[])
{
    string root_path = "../conf/test_foreach_sequence.conf";
    map<string, string> pairs = get_config(root_path);
    const string project_folder = pairs["project_folder"];
    const string default_template = pairs["default_template"];
    const string conf_path = pairs["conf_path"];

    // check for input or use default
    string template_name = default_template;
    if (argc == 2)
    {
        template_name.clear();
        template_name = argv[1];
    }
    const string path = project_folder + "./test/templates/" + template_name;

    // read file
    std::ifstream ifile_strm(path);
    std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());

    if (src == "")
    {
        cout << "Error reading template, path (" + path + ") ..." << endl;
        return 0;
    }

    string s1 = foreach_sequence(src);
    cout << s1;

    string s2 = foreach_sequence_with_test(src);
    cout << s2;
}

// find foreach sequence
string foreach_sequence(const string &src)
{
    regex exp = regex(FOREACH_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub1 = match[2];
        std::ssub_match sub2 = match[3];
        // output text
        if (sub1.matched)
            output += sub1.str();
        else if (sub2.matched)
            output += sub2.str();
    }
    return output;
}

// find foreach_sequence with text!
string foreach_sequence_with_test(const string &src)
{
    regex exp = regex(FOREACH_SEQUENCE, regex::ECMAScript); // match
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
