#include <iostream>
#include <string>
#include "../../smarty-cpp/src/smarty.hpp"
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
    const string template_name = "test1.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";

    smarty sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");

    string path = project_folder + "/www/templates" + "/test1.tpl";
    string src = readlines(path);
    cout << src << endl;

    // string html = sm.include(path);
    // cout << html << endl;
}
