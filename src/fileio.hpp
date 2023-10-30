// Mon Oct 30 11:55:47 AM CDT 2023

#ifndef _FILEIO_HPP
#define _FILEIO_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

vector<string> getlines(string path);
string ifs_read_all(string path);
map<string, string> get_config(string path);

string& ltrim(string &s);
string& rtrim(string &s);
string& trim(string &s);

#endif
