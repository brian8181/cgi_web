#include <iostream>
#include <string>
#include <fstream>
#include "utility.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;

int main(int argc, char* argv[])
{  
    vector<string> lines = getlines("../src/test_if_sequence.conf");
    vector<string>::iterator end = lines.end();
    for(vector<string>::iterator iter = lines.begin(); iter != end; ++iter)
    {
        cout << *iter << endl;
    }
    cout << endl;

    const string default_template =  "test_if_sequence.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";
    
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
    //string s = lex_all(src);
    cout << s;
}
