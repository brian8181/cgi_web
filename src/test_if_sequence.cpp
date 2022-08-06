#include <iostream>
#include <string>
#include "utility.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
    const string default_template = "if_sequence.tpl";
    string template_name = default_template;
    if(argc == 2)
    {
        string template_name = argv[1];
    }
        
    string html = if_sequence(template_name);
    cout << html << endl;

}
