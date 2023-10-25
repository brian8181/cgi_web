#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <algorithm>
#include <exception>
#include "patterns.hpp"
#include "fileio.hpp"
#include "utility.hpp"

void assign(string name, string val, map<string, string> &symbols)
{
    pair<string, string> p(name, val);
    symbols.insert(p);
}

void display(string path, const map<string, string> &tags)
{
    string src = ifs_read_all(path);
    regex exp = regex("\\{\\$(.*?)\\}", regex::ECMAScript);

    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), exp);
    auto end = sregex_iterator();

    int beg_pos = 0;
    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        string sm = sub.str();
        string tag = trim(sm);

        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos - beg_pos);
        map<string, string>::const_iterator find_iter = tags.find(tag);
        if (find_iter != tags.end())
        {
            output += find_iter->second;
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    cout << output << endl;
}

// lex the tag (inside curly braces), "{(.*)}"
string lex_tag(const string &src)
{
    regex exp = regex(TOKENS, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string match_str = match.str();
        output += trim(match_str) + "\n";
    }
    return output;
}

// load / create streamy style config
bool load_config(string path, map<string, string> &config)
{
    string src = ifs_read_all(path);

    string name_exp = "([A-Za-z]+\\w*)";
    string value_exp = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
    regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp);

    auto begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_not_null);
    auto end = sregex_iterator();

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string name = match[1].str();
        string value = match[3].str() + match[5].str() + match[7].str();
        cout << "Match: --> " << match.str() << "; Name: --> " << match[1].str() << "; Value: --> " << value << endl;
        pair<string, string> p(name, value);
        config.insert(p);
    }
    return true;
}

void find_tags(string path)
{
    string src = ifs_read_all(path);
    regex src_epx = regex("\\{(.*?)\\}", regex::ECMAScript);

    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_epx, std::regex_constants::match_not_null);
    auto end = sregex_iterator();

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        cout << match.str() << " --> " << sub.str() << endl;
    }
}

// test function replace all tags with "<!-- TEST -->"
void replace_tags(string path)
{
    string src = ifs_read_all(path);
    regex pattern = regex("\\{(.*?)\\}", regex::ECMAScript);
    std::regex_replace(std::ostreambuf_iterator<char>(std::cout), src.begin(), src.end(), pattern, "<!-- TEST -->");
}

string match_replace_tags(string path, const map<string, string> &tags)
{
    string src = ifs_read_all(path);
    regex src_epx = regex("\\{\\$(.*?)\\}", regex::ECMAScript);

    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_epx);
    auto end = sregex_iterator();

    int sbeg = 0;
    int send = 0;
    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        string sm_str = sub.str();
        string tag = trim(sm_str);

        send = match.position();
        int len = send - sbeg;
        output += src.substr(sbeg, len);
        map<string, string>::const_iterator it = tags.find(tag);
        if (it != tags.end())
        {
            output += it->second;
        }
        sbeg = send + match.length();
    }
    output += src.substr(sbeg);
    return output;
}
