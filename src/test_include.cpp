#include <iostream>
#include <string>
//#include "../../streamy-cpp/src/streamy.hpp"
#include "utility.hpp"
#include "fileio.hpp"

using namespace std;

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
