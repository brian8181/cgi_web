#include <iostream>
#include <string>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"
#include "../../smartycpp/src/smarty.h"
#include "../src/utility.hpp"
#include "../src/conf.hpp"

using namespace std;
using namespace cgicc;

int main(int argc, char* argv[])
{ 
    Cgicc cgi;
    cout << HTTPHTMLHeader(); // Set up the HTML document

    string project_folder = "/home/brian/src/cgi_web";
    string path = project_folder + "/templates/index_test.tpl";
    smarty sm("./templates", "./complie", "./config", "./cache"); 
    sm.assign("headers", "");
    sm.assign("page_title", "SmartyCPP Test Page");
    sm.assign("body", "The Body");
    sm.assign("admin_email", "admin@something.com");
    sm.assign("version", "0.1");
    sm.assign("version_date", "Feb, 14 2022");
    sm.display(path);
    
    return 0;
}