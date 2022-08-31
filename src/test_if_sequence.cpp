#include <iostream>
#include <unistd.h>
#include <string>
#include <fstream>
#include "utility.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;

int main(int argc, char* argv[])
{  
    //int d  = chdir("/home/brian/src");
    // get pairs / configuration
    string root_path = "./src/test_if_sequence.conf";
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
    const string path = project_folder + "/test/templates/" + template_name;

    // read file
    std::ifstream in(path);
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        
    string s = if_sequence(src);
    cout << s;
}
