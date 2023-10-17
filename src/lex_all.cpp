#include <iostream>
#include <string>
#include <fstream>
#include "utility.hpp"
#include "fileio.hpp"

// const unsigned int DEFAULT_TEMPLATE = 1;
// const unsigned int PROJECT_FOLDER = 2;

using namespace std;

string fstream_read(string path);

int main(int argc, char *argv[])
{
    string root_path = "./src/lex_all.conf";
    map<string, string> pairs = get_config(root_path);

    const string project_folder = pairs["project_folder"];
    const string template_folder = pairs["template_folder"];
    const string default_template = pairs["default_template"];
    
    // check for input or use default
    string template_name = default_template;
    if (argc == 2)
    {
        template_name.clear();
        template_name = argv[1];
    }

    const string path = template_folder + template_name;
    string output;
    try
    {
        std::ifstream ifile_strm(path);
        std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());
        if (src == "")
        {
            cout << "Error reading file, path (" + path + ") ..." << endl;
            return 0;
        }
        output = lex_all(src);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading file ... " << e.what() << endl;
    }

    cout << output;
}