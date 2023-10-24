#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

void assign(string name, string val, map<string, string>& symbols); 
void display(string path, const std::map<string, string>& tags);
string lex(const string& src);
string lex_tag(const string& src);
bool load_config(string path, std::map<string, string>& config);
void find_tags(string path);
void replace_tags(string path);
string match_replace_tags(string path, const std::map<string, string>& tags);

const string project_folder = "/home/brian/src/cgi_web";
const string template_dir = project_folder + "/www/templates";

#endif
