#ifndef _FILEIO_HPP
#define _FILEIO_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

string ifs_read_all(string path);
vector<string> getlines(string path);
map<string, string> get_config(string path);

void ltrim(string &s);
void rtrim(string &s);
void trim(string &s);

#endif
