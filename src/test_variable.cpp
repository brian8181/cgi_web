#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "fileio.hpp"
#include "streamy.hpp"
#include "utility.hpp"

using namespace std;

string variable(const string &src, map<string, string> &vars);

int main(int argc, char *argv[])
{
    const string default_template = "test_variable.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";

    // check for input or use default
    string template_name = default_template;
    if (argc == 2)
    {
        template_name.clear();
        template_name = argv[1];
    }
    const string path = project_folder + "/www/templates/" + template_name;

    // read file
    std::ifstream in(path);
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    // string src = readlines(path);
    // cout << src << endl;

    // streamy sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");
    // sm.assign("headers", "HEADERS");
    // sm.assign("page_title", "streamyCPP Test Page");
    // sm.assign("body", "The Body");
    // sm.assign("admin_email", "admin@something.com");
    // sm.assign("version", "0.1");
    // sm.assign("version_date", "Feb, 14 2022");

    map<string, string> tags;
    assign("headers", "", tags);
    assign("page_title", "streamyCPP Test Page", tags);
    assign("body", "The Body", tags);
    assign("admin_email", "admin@something.com", tags);
    assign("version", "0.1", tags);
    assign("version_date", "Feb, 14 2022", tags);
    // display(path, tags);

    assign("foo", "Big Foo", tags);
    assign("bar", "Bar", tags);
    // test default
    // assign("boo", "Little Boo!", tags);

    // call variable --
    // string html = sm.variable(src);
    string html = variable(src, tags);
    cout << html << endl;
}


// find & process variables
string variable(const string &src, map<string, string> &vars)
{
    string SYMBOL_NAME = "";
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

