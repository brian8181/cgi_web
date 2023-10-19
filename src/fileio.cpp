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

string& ltrim(std::string &s)
{
    int len = s.size();
    int i;
    for(i = 0; i < len; ++i)
    {
        if(!std::isspace(s[i]))
            break;
    }
    string::iterator beg = s.begin(); 
    s.erase(beg, beg+i);
    return s;
}

string& rtrim(std::string &s)
{
    int len = s.size();
    int i = len;
    for(;i > 0; --i)
    {
        if(!std::isspace(s[i-1]))
            break;
    }
    string::iterator end = s.end(); 
    s.erase(end-(len-i), end);
    return s;
}

string& trim(std::string &s)
{
    rtrim(s);
    ltrim(s);
    return s;
}

// get test configuration map
map<string, string> get_config(string path)
{
    ifstream file;
    file.open(path, ios::in);

    map<string, string> config;
    pair<string, string> config_pair;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            size_t pos = line.find('=');
            string name = line.substr(0, pos - 1);
            string value = line.substr(pos + 1);
            pair<string, string> p(trim(name), trim(value));
            config.insert(p);
        }
        file.close();
    }
    return config;
}