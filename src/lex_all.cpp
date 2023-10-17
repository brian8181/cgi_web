#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "utility.hpp"
#include "fileio.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    std::filesystem::path path(argv[0]);
    string root_path = path.replace_extension("conf");
    map<string, string> pairs = get_config(root_path);

    const string project_folder = pairs["project_folder"];
    const string template_folder = pairs["template_folder"];
    const string default_template = pairs["default_template"];
    
    // check for input or use default
    string template_name = default_template;
    if (argc > 1)
    {
        template_name.clear();
        template_name = argv[1];
    }

    const string file_path = template_folder + template_name;
    string output;
    try
    {
        string src = ifs_read_all(file_path);
        if (src == "")
        {
            cout << "Error reading file, path (" + file_path + ") ..." << endl;
            return -1;
        }
        output = lex_all(src);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading file ... " << e.what() << endl;
    }

    cout << output;
}