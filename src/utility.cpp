#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <list>
#include <regex>
#include <algorithm>
#include <exception>
#include "patterns.hpp"
#include "utility.hpp"

// template <typename T1, typename T2>
// class pairz
// {
//     T1 t1;
//     T2 t2;
// };

// // open file
// ifstream open(string path)
// {
//     pairz<string, string> pz;
//     string src;
//     ifstream file;
//     file.open(path, ios::in);
//     return file;
// }

class myexception : public exception
{
    virtual const char *what() const throw()
    {
        return "My exception happened";
    }
} myex;

// read all
// string fstream_read(string path)
// {
//     string str;
//     fstream file;
//     file.open(path, ios::in);
//     if (file.is_open())
//     {
//         char c[256];
//         while (file.read(c, 256))
//         {
//             if (file.eof())
//             {
//                 throw myex;
//             }
//             // read data from file
//             str.append(c);
//         }
//         file.close();
//     }
//     return str;
// }

// get file lines as vector
vector<string> getlines(string path)
{
    ifstream file;
    file.open(path, ios::in);

    vector<string> lines;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

// read all, (default read function)
string ifs_read_all(string path)
{
    std::ifstream ifstrm(path);
    std::string output((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
    return output;
}

// get test configuration map
map<string, string> get_config(string path)
{
    ifstream file;
    file.open(path, ios::in);

    map<string, string> config;
    pair<string, string> config_pair;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find('=');
            string name = trim(line.substr(0, pos - 1));
            string value = trim(line.substr(pos + 1));
            pair<string, string> p(name, value);
            config.insert(p);
        }
        file.close();
    }
    return config;
}

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
        string tag = trim(sub.str());

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

// display template
void display(string tmpl)
{
    cout << include(tmpl);
}

// find & process includes
std::string include(const string &tmpl)
{
    // set up constants
    const string path = template_dir + "/" + tmpl;

    // read file
    std::ifstream in(path);
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    // iter all includes
    regex exp = regex(INCLUDE, regex::ECMAScript);
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string tag = trim(s);

        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos - beg_pos);
        // call include recursively
        output += include(tag);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    return output;
}

// find & process variables
string variable(const string &src, map<string, string> &vars)
{
    const string DEFAULT_FUNCTION = "\\|default:'(.*)'";
    const string VARIABLE = "\\{\\s*\\$(" + SYMBOL_NAME + ")\\s*(" + DEFAULT_FUNCTION + ")?\\s*\\}";

    regex exp = regex(VARIABLE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string tag = trim(s);

        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos - beg_pos);
        map<string, string>::const_iterator find_iter = vars.find(tag);
        if (find_iter != vars.end())
        {

            output += find_iter->second;
        }
        else if (match[3].matched) // default sub match!
        {
            output += match[3].str();
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string sequence(const string &src, const string &sequence)
{
    regex exp = regex(sequence, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int len = match.size();

        for (int i = 0; i < len; ++i)
        {
            if (match[i].matched)
            {
                cout << "match[" << i << "] = " << match[i].str() << endl;
            }
        }
    }
    return output;
}

// find if sequence
string if_sequence(const string &src)
{
    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
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

// find foreach sequence
string foreach_sequence(const string &src)
{
    regex exp = regex(FOREACH_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
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

// find text & tags
string lex_all(const string &src)
{
    const string ESCAPE = "\\{[\\w\\s]+\\}";
    //const string TEXT = "[\\}]([.]+)[\\{]";
    //const string TEXT = "^[\\s\\w\\p<>/\\]*[^{][\\s\\w/\\<>]*$";
    //const string TEXT = ".*[^{}].*";
    //const string TEXT = "\\w*";

    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int match_beg_pos = match.position();
        // get from end of last match (src_beg_pos) to begin of current
        string pre_match_src = src.substr(src_beg_pos, match_beg_pos - src_beg_pos);
        output += "TEXT: " + trim(pre_match_src) + "\n";

        string tokens = lex_tag(match.str());
        output += "TAG: " + tokens;
        src_beg_pos = match_beg_pos + match.length()+1;

    }

    // get TEXT after last match
    if (src_beg_pos < src.size())
    {
        // trim white space / newline
        output += trim(src.substr(src_beg_pos, src.size() - src_beg_pos)) + "\n";
    }
    return output;
}

// find tag (no text)
string lex(const string &src)
{
    const string ESCAPE = "\\{.*?\\}";
    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string tokens = lex_tag(match.str());
        output += tokens;
    }
    return output;
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
        output += trim(match.str()) + "\n";
    }
    return output;
}

// lex into list
list<string> lex_all_list(const string &src)
{
    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    list<string> output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int match_beg_pos = match.position();
        // outout begin -> match
        string pre_match_src = src.substr(src_beg_pos, match_beg_pos - src_beg_pos);

        output.push_back("TEXT -> " + pre_match_src + "\n");
        output.push_back("ESCAPE -> " + match.str() + "\n");

        src_beg_pos = match_beg_pos + match.length();
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
        string tag = trim(sub.str());

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

// trim functions
const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

std::string &_ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(s.begin(), it);
    return s;
}

std::string &_rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(it.base(), s.end());
    return s;
}

std::string &_trim(std::string &s)
{
    return _ltrim(_rtrim(s));
}
