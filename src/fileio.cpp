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
            string name = trim(line.substr(0, pos - 1));
            string value = trim(line.substr(pos + 1));
            pair<string, string> p(name, value);
            config.insert(p);
        }
        file.close();
    }
    return config;
}

// trim functions
const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

std::string &_ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(s.begin(), it);
    return s;
}

std::string &_rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                           [](char c)
                           {
                               return !std::isspace<char>(c, std::locale::classic());
                           });
    s.erase(it.base(), s.end());
    return s;
}

std::string &_trim(std::string &s)
{
    return _ltrim(_rtrim(s));
}
