// simple c++ cgi test script

#include <iostream>

using namespace std;

int main()
{
    cout << "Content-type: text/html" << endl << endl; // skip a line
    cout << "<html>" << endl;
    cout << "<body>" << endl;
    cout << "<div style=\"width: 100%; font-size: 40px; font-weight: bold; text-align: center;\">" << endl;
    cout << "CGI - CPP Test Page 1.6" << endl;
    cout << "</div>" << endl;
    cout << "</body>" << endl;
    cout << "</html>" << endl;
}
