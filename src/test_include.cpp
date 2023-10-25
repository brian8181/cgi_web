#include <iostream>
#include <fstream>
#include <string>
#include <regex>
//#include "../../streamy-cpp/src/streamy.hpp"
#include "fileio.hpp"
#include "utility.hpp"

using namespace std;

std::string include(const string &tmpl);

int main(int argc, char *argv[])
{
    const string default_template = "INCLUDE_TEST.tpl";
    string template_name = default_template;
    if (argc == 2)
    {
        string template_name = argv[1];
    }

    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "./test/conf_test.txt";

    // sstreamy sm(project_folder + "/www/templates", project_folder + "/www/compile", projec>
    // template_dir = project_folder + "/www/templates";
    string html = include(template_name);
    cout << html << endl;
}

// find & process includes
std::string include(const string &tmpl)
{

    string INCLUDE;
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

