#ifndef _FILEIO_HPP
#define _FILEIO_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

string ifs_read_all(string path);
vector<string> getlines(string path);
map<string, string> get_config(string path);

string ltrim(const string &s);
string rtrim(const string &s);
string trim(const string &s);

string& _ltrim(const string &s);
string& _rtrim(const string &s);
string& _trim(const string &s);

#endif
