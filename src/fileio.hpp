
#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

string ifs_read_all(string path);
vector<string> getlines(string path);
map<string, string> get_config(string path);

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

std::string& _ltrim(const std::string &s);
std::string& _rtrim(const std::string &s);
std::string& _trim(const std::string &s);

#endif
