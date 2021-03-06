#include <string>
#include <iostream>
#include <map>

#include "../src/utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
    cout << "content-type: text/html" << endl << endl;

    string path = "./templates/index_test.tpl";
    map<string, string> tags;
    assign("headers", "", tags);
    assign("page_title", "SmartyCPP Test Page", tags);
    assign("body", "The Body", tags);
    assign("admin_email", "admin@something.com", tags);
    assign("version", "0.1", tags);
    assign("version_date", "Feb, 14 2022", tags);
    display(path, tags);
    
	return 0;
}
