#include <iostream>
#include <string>
#include <fstream>
#include "../../smarty-cpp/src/smarty.hpp"
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
    const string default_template =  "test_variable.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";
    
    // check for input or use default
    string template_name = default_template;
    if(argc == 2)
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

    // smarty sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");
    // sm.assign("headers", "HEADERS");
    // sm.assign("page_title", "SmartyCPP Test Page");
    // sm.assign("body", "The Body");
    // sm.assign("admin_email", "admin@something.com");
    // sm.assign("version", "0.1");
    // sm.assign("version_date", "Feb, 14 2022");

    map<string, string> tags;
    assign("headers", "", tags);
    assign("page_title", "SmartyCPP Test Page", tags);
    assign("body", "The Body", tags);
    assign("admin_email", "admin@something.com", tags);
    assign("version", "0.1", tags);
    assign("version_date", "Feb, 14 2022", tags);
    //display(path, tags);
    
    assign("foo", "Big Foo", tags);
    assign("bar", "Bar", tags);
    // test default
    //assign("boo", "Little Boo!", tags);

    // call variable --
    //string html = sm.variable(src);
    string html = variable(src, tags);
    cout << html << endl;
}
