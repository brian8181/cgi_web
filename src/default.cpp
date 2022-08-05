#include <iostream>
#include <string>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "../../smarty-cpp/src/smarty.hpp"
#include "utility.hpp"

using namespace std;
using namespace cgicc;

int main(int argc, char* argv[])
{ 
    Cgicc  cgi;
    cout << HTTPHTMLHeader();

    const string template_name = "default.tpl";
    const string project_folder = "/home/brian/src/cgi_web";
    const string conf_path = project_folder + "/test/conf_test.txt";

    smarty sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache"); 
    sm.load_config(conf_path);
    sm.assign("headers", "HEADERS");
    sm.assign("page_title", "SmartyCPP Test Page");
    sm.assign("body", "The Body");
    sm.assign("admin_email", "admin@something.com");
    sm.assign("version", "0.1");
    sm.assign("version_date", "Feb, 14 2022");
    sm.display("default.tpl");

    return 0;
}
