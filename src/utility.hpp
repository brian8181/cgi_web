#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <map>

using namespace std;

string readlines(string path);

void assign(string name, string val, map<string, string>& symbols);
void display(string path, const map<string, string>& tags);

bool load_config(string path, map<string, string>& config);
void find_tags(string path);
void replace_tags(string path);
void replace_tags2(string expr_path, string file_path);
string match_replace_tags(string path, const map<string, string>& tags);

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

//string ifstream_readlines(string path);
//string fstream_get(string path);
//string fstream_read(string path);

std::string& _ltrim(const std::string &s);
std::string& _rtrim(const std::string &s);
std::string& _trim(const std::string &s);

#endif
