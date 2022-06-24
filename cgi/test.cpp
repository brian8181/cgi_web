#include <iostream>
#include "cgicc/CgiDefs.h"
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

int main()
{
    // Cgicc  cgi;
    // cout << HTTPHTMLHeader(); // Set up the HTML document
    cout << "Content-type: text/html" << endl << endl; // skip a line
    cout << "<html>" << endl;
    cout << "<body>" << endl;
    cout << "<div style=\"width: 100%; font-size: 40px; font-weight: bold; text-align: center;\">" << endl;
    cout << "CGI - CPP Test Page 1.3" << endl;
    cout << "</div>" << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;
}