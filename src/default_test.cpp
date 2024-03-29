// Mon Oct 30 11:55:47 AM CDT 2023

#include <iostream>
#include <string>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "fileio.hpp"
#include "utility.hpp"
#include "/usr/local/include/streamy.hpp"
//#include "../src/conf.hpp"

using namespace std;
using namespace cgicc;

int main(int argc, char *argv[])
{
    Cgicc cgi;
    cout << HTTPHTMLHeader();

    // const string template_name = "default_test.tpl";
    const string template_name = "test1.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";

    streamy sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");
    string s_out;
    sm.load_config(conf_path);

    // configure testing ...
    // string a = sm.get_conf("AAA");
    // string b = sm.get_conf("BBB");
    // string c = sm.get_conf("CCC");
    // cout << "AAA=" << a << endl;
    // cout << "BBB=" << b << endl;
    // cout << "CCC=" << c << endl;

    sm.assign("headers", "HEADERS");
    sm.assign("page_title", "streamyCPP Test Page");
    sm.assign("body", "The Body");
    sm.assign("admin_email", "admin@something.com");
    sm.assign("version", "0.1");
    sm.assign("version_date", "Feb, 14 2022");
    sm.assign(".test", "TESTING DOT");
    sm.assign("_test", "TESTING UNDERSCORE");
    sm.assign("~test", "TESTING TILDE");
    sm.display(template_name);

    return 0;
}
