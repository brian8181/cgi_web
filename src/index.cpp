//Mon Oct 30 11:55:47 AM CDT 2023

#include <iostream>
#include <string>
#include <filesystem>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "streamy.hpp"
#include "fileio.hpp"
#include "utility.hpp"

using std::cout;
using std::endl;
using std::string;
using namespace cgicc;

int main(int argc, char *argv[])
{
    Cgicc cgi;
    cout << HTTPHTMLHeader();

    filesystem::path fs_path(argv[0]);
    string project_path = fs_path.parent_path();

    const string template_name = project_path + "/default.tpl";
    const string project_folder = project_path + "/cgi_web";
    const string conf_path = project_path + "/test/conf_test.txt";

    streamy sm(project_folder + "/www/templates", project_folder + "/www/compile", project_folder + "/www/config", project_folder + "/www/cache");
    sm.load_config(conf_path);
    sm.assign("headers", "HEADERS");
    sm.assign("page_title", "streamyCPP Test Page");
    sm.assign("body", "The Body");
    sm.assign("admin_email", "admin@something.com");
    sm.assign("version", "0.1");
    sm.assign("version_date", "Feb, 14 2022");
    sm.display("default.tpl");

    return 0;
}
