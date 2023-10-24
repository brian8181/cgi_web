#ifndef _UTILITY_HPP
#define _UTILITY_HPP

#include <string>
#include <map>
#include <vector>

using namespace std;

void assign(string name, string val, map<string, string>& symbols); 
void display(string path, const std::map<string, string>& tags);
void display2(string path, const std::map<string, string>& tags);
void display(string tmpl);
string include(const string& tmpl);
string variable(const string& src, std::map<string, string>& vars);
string sequence(const string& src, const string& sequence);
string if_sequence(const string& src);
string if_sequence_with_text(const string& src);
string foreach_sequence(const string& src);
string foreach_sequence_with_test(const string& src);
string lex_all(const string& src);
string lex(const string& src);
string lex_tag(const string& src);

bool load_config(string path, std::map<string, string>& config);
void find_tags(string path);
void replace_tags(string path);
void replace_tags2(string expr_path, string file_path);
string match_replace_tags(string path, const std::map<string, string>& tags);
string ifs_read_all(string path);
ifstream open(string path);
vector<string> getlines(string path);
std::map<string, string> get_config(string path);

string& ltrim(const string &s);
string& rtrim(const string &s);
string& trim(const string &s);

const string project_folder = "/home/brian/src/cgi_web";
const string template_dir = project_folder + "/www/templates";

#endif
