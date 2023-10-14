#include <iostream>
#include <fstream>
#include <algorithm>
#include "fileio.hpp"

// get file lines as vector
vector<string> getlines(string path)
{
    ifstream file;
    file.open(path, ios::in);

    vector<string> lines;
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

// read all, (default read function)
string ifs_read_all(string path)
{
    std::ifstream ifstrm(path);
    std::string output((std::istreambuf_iterator<char>(ifstrm)), std::istreambuf_iterator<char>());
    return output;
}

void ltrim(std::string &s)
{
    int len = s.size();
    int i = 0;
    for(; i < len; ++i)
    {
        if(!std::isspace(s[i]))
            break;
    }

    string::iterator beg = s.begin(); 
    s.erase(beg, beg+i);
}

void rtrim(std::string &s)
{
    int len = s.size();
    int i = len;
    for(;i > 0; --i)
    {
        if(!std::isspace(s[i-1]))
            break;
    }

    string::iterator end = s.end(); 
    s.erase(end-i, end);
}

void trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
}