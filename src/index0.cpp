#include <string>
#include <iostream>
#include <map>
#include <regex>
#include <fstream>
//#include <pair>
#include "utility.hpp"

using namespace std;

// trim functions
const std::string WHITESPACE = " \n\r\t\f\v";

void assign(string name, string val, map<string, string> &symbols)
{
    pair<string, string> p(name, val);
    symbols.insert(p);
}

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

// read all, (default read function)
string ifs_read_all(string path)
{
    std::ifstream ifstrm(path);
    std::string output((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
    return output;
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

int main(int argc, char *argv[])
{
    cout << "content-type: text/html" << endl
         << endl;

    string path = "./test/templates/index_test.tpl";
    map<string, string> tags;
    assign("headers", "", tags);
    assign("page_title", "CGI CPP Test Page", tags);
    assign("body", "The Body", tags);
    assign("admin_email", "admin@something.com", tags);
    assign("version", "0.1", tags);
    assign("version_date", "Feb, 14 2022", tags);
    display(path, tags);

    return 0;
}
