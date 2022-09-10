#include <iostream>
#include <string>
#include "../../streamy-cpp/src/streamy.hpp"
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
    const string template_name = "test_comment.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";

    string path = project_folder + "/www/templates/" + template_name;
    string src = readlines(path);
    cout << src << endl;

    streamy sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");
    sm.assign("headers", "HEADERS");
    sm.assign("page_title", "streamyCPP Test Page");
    sm.assign("body", "The Body");
    sm.assign("admin_email", "admin@something.com");
    sm.assign("version", "0.1");
    sm.assign("version_date", "Feb, 14 2022");
    // call variable --
    //string html = sm.variable(src);
    string html = sm.remove_comments(src);
    cout << html << endl;
}
