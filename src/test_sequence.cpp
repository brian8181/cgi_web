#include <iostream>
#include <string>
#include <fstream>
#include "utility.hpp"
#include <regex>
#include "patterns.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;

int main(int argc, char* argv[])
{  
    string path; // source (text to match)
    string exp; // regular expresssion
    if(argc == 3)
    {
        path = argv[1];
        exp = argv[2];    
    }

    cout << path << endl;
    cout << exp << endl << endl;

    // read file
    std::ifstream ifile_strm(path);
    std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());
    
    if(src == "")
    { 
        cout << "Error reading template, path (" + path + ") ..." << endl;
        return 0;
    }
    else
    {
        cout << src;
    }
        
    //sequence(src, seq);
}
