#include <iostream>
#include <string>
#include <fstream>
#include "utility.hpp"
#include <regex>
#include "patterns.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;

int main(int argc, char* argv[])
{  
    string ESC = "\\{\\s*<a>\\s*\\}";
    //string str = std::regex_replace(std::back_inserter(ESC), ESC.begin(), ESC.end(), "\\<A\\>", "Foo");
    cout << ESC << endl;

    // run from path ./ !
    string root_path = "../src/test_if_sequence.conf";
    map<string, string> pairs = get_config(root_path);
    const string project_folder = pairs["project_folder"];
    const string default_template =  pairs["default_template"];
    const string conf_path = pairs["conf_path"];
    
    // check for input or use default
    string template_name = default_template;
    if(argc == 2)
    {
        template_name.clear();
        template_name = argv[1];
    }
    const string path = project_folder + "./test/templates/" + template_name;

    // read file
    std::ifstream ifile_strm(path);
    std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());
    
    if(src == "")
    { 
        cout << "Error reading template, path (" + path + ") ..." << endl;
        return 0;
    }
        
    string s = if_sequence(src);
    cout << s;
}
