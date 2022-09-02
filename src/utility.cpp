#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include "utility.hpp"


ifstream open(string path)
{
    string src;
    ifstream file;
    file.open(path, ios::in); //open a file
    return file;
}

vector<string> getlines(string path)
{
    ifstream file;
    file.open(path, ios::in); //open a file

    vector<string> lines;
    if (file.is_open()) 
    {   
        string line;
        while(getline(file, line))
        { 
            lines.push_back(line);
        }
        file.close(); //close the file
    }
    return lines;
}

map<string, string> get_config(string path)
{
    ifstream file;
    file.open(path, ios::in); //open a file

    map<string, string> config;
    pair<string, string> config_pair;

    if (file.is_open()) 
    {   
        string line;
        while(getline(file, line))
        { 
            size_t pos = line.find('=');
            string name = trim(line.substr(0, pos-1));
            string value = trim(line.substr(pos+1));
            pair<string, string> p(name, value);
            config.insert(p);
        }
        file.close(); //close the file
    }
    return config;
}

//string get_all_lines(string path)
string readlines(string path)
{
    string src;
    ifstream file;
    file.open(path, ios::in); //open a file
    if (file.is_open()) 
    {   
        string tp;
        while(getline(file, tp))
        { 
            //read data from file
            src += tp;
        }
        file.close(); //close the file
    }
    return src;
}

string fstream_read(string path)
{
    string str;
    fstream file;
    file.open(path, ios::in); //open a file
    if (file.is_open()) 
    {   
        char c[256];
        while(file.read(c, 256))
        { 
            //read data from file
            str.append(c);
        }
        file.close(); //close the file
    }
    return str;
}

string fread_test(string path)
{
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return contents;
}

void assign(string name, string val, map<string, string>& symbols)
{
    pair<string, string> p(name, val);
    symbols.insert(p);
}

void display(string path, const map<string, string>& tags)
{
    string src = readlines(path);
    regex exp = regex("\\{\\$(.*?)\\}", regex::ECMAScript);
            
    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), exp);
    auto end = sregex_iterator(); 
    
    int beg_pos = 0;
    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        string tag = trim(sub.str());
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        map<string, string>::const_iterator find_iter = tags.find(tag);
        if(find_iter != tags.end())
        {
            output += find_iter->second;
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    cout << output << endl;
}

void display(string tmpl)
{
    cout << include(tmpl);
}

std::string include(const string& tmpl)
{
    // set up constants
    const string INCLUDE = "\\{\\s*\\include file\\s*=\\s*\"(.*?)\"\\s*\\}";
    const string path = template_dir + "/" + tmpl;
    
    // read file
    std::ifstream in(path);
    std::string src((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    
    // iter all includes
    regex exp = regex(INCLUDE, regex::ECMAScript);
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        // call include recursively
        output += include(tag);
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);
    return output;
}

string variable(const string& src, map<string, string>& vars)
{
    const string SYMBOL_NAME = "\\b[_.~]*[A-Za-z][A-Za-z0-9_.-~]*\\b";
    const string DEFAULT_FUNCTION = "\\|default:'(.*)'";
    const string VARIABLE = "\\{\\s*\\$(" + SYMBOL_NAME + ")\\s*(" + DEFAULT_FUNCTION + ")?\\s*\\}";

    regex exp = regex(VARIABLE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 
    string output;
    int beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        std::string s(sub.str());
        string tag = trim(s);
        
        int end_pos = match.position();
        output += src.substr(beg_pos, end_pos-beg_pos);
        map<string, string>::const_iterator find_iter = vars.find(tag);
        if(find_iter != vars.end())
        {
           
            output += find_iter->second;
        }
        else if(match[3].matched) // default sub match!
        {
            output += match[3].str(); 
        }
        beg_pos = end_pos + match.length();
    }
    output += src.substr(beg_pos);

    return output;
}

string if_sequence(const string& src)
{
    const string SYMB_NAME = "\\b[-._~]*[A-Za-z][-._~A-Za-z0-9]*\\b";
    const string IF_KEYWORD = "\\{if\\s+\\$" + SYMB_NAME + "\\s*\\}[\\n]?";
    const string ENDIF_KEYWORD = "\\{/if\\}[\\n]?";
    const string HTML = "([-._~!\\s\\r\\n\\w]*)";
    const string IF_SEQUENCE = IF_KEYWORD + HTML + ENDIF_KEYWORD;

    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int match_beg_pos = match.position();
        
        // outout begin -> match
        string pre_match_src = src.substr(src_beg_pos, match_beg_pos-src_beg_pos);
        output += pre_match_src;

        std::ssub_match sub = match[1];
        string tmp_str = sub.str();
        string tag(tmp_str.substr(1, tmp_str.size()-1));
        // output text
        output += tag;
        
        src_beg_pos = match_beg_pos + match.length();
    }
    return output;
}

string lex_all(const string& src)
{
    // string if_sequence(const string& src)
    const string SYMB_NAME = "\\b[-._~]*[A-Za-z][-._~A-Za-z0-9]*\\b";
    const string IF_KEYWORD = "\\{if\\s+\\$" + SYMB_NAME + "\\s*\\}[\\n]?";
    const string ENDIF_KEYWORD = "\\{/if\\}[\\n]?";
    const string HTML = "([-._~!\\s\\r\\n\\w]*)";
    const string IF_SEQUENCE = IF_KEYWORD + HTML + ENDIF_KEYWORD;

    regex exp = regex(IF_SEQUENCE, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator(); 

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int match_beg_pos = match.position();
        
        // outout begin -> match
        string pre_match_src = src.substr(src_beg_pos, match_beg_pos-src_beg_pos);
        output += pre_match_src;

        std::ssub_match sub = match[1];
        string tmp_str = sub.str();
        string tag(tmp_str.substr(1, tmp_str.size()-1));
        // output text
        output += tag;
        
        src_beg_pos = match_beg_pos + match.length();
    }
    return output;
}

bool load_config(string path, map<string, string>& config)
{
    string src = readlines(path);

    string name_exp = "([A-Za-z]+\\w*)";
    string value_exp = "((\\w+)|('(\\w+)')|(\\\"(\\w+)\\\"))";
    regex src_exp = regex(name_exp + "\\s+=\\s+" + value_exp); 
                    
    auto begin = sregex_iterator(src.begin(), src.end(), src_exp, std::regex_constants::match_not_null);
    auto end = sregex_iterator(); 

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        string name = match[1].str();
        string value = match[3].str() + match[5].str() + match[7].str();
        cout << "Match: --> " << match.str() <<  "; Name: --> " << match[1].str() << "; Value: --> " << value << endl;
        pair<string, string> p(name, value);
        config.insert(p);
    }
    return true;
}

void find_tags(string path)
{
    string src = readlines(path);
    regex src_epx = regex("\\{(.*?)\\}", regex::ECMAScript);
            
    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_epx, std::regex_constants::match_not_null);
    auto end = sregex_iterator(); 
    
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        cout << match.str() <<  " --> " << sub.str() << endl;
    }
}

void replace_tags(string path)
{
    string src = readlines(path);
    regex pattern = regex("\\{(.*?)\\}", regex::ECMAScript);
    std::regex_replace(std::ostreambuf_iterator<char>(std::cout), src.begin(), src.end(), pattern, "<!-- TEST -->");
}

void replace_tags2(string expr_path, string file_path)
{
    string src = readlines(file_path);
    string expr = readlines(expr_path);

    regex pattern = regex(expr, regex::ECMAScript);
    std::regex_replace(std::ostreambuf_iterator<char>(std::cout), src.begin(), src.end(), pattern, "<!-- TEST -->");
}

string match_replace_tags(string path, const map<string, string>& tags)
{
    string src = readlines(path);
    regex src_epx = regex("\\{\\$(.*?)\\}", regex::ECMAScript);
            
    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), src_epx);
    auto end = sregex_iterator(); 
    
    int sbeg = 0;
    int send = 0;
    string output;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        std::ssub_match sub = match[1];
        string tag = trim(sub.str());
        
        send = match.position();
        int len = send-sbeg;
        output += src.substr(sbeg, len);
        map<string, string>::const_iterator it = tags.find(tag);
        if(it != tags.end())
        {
           output += it->second;
        }
        sbeg = send + match.length();
    }
    output += src.substr(sbeg);
    return output;
}

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

std::string& _ltrim(std::string &s)
{
    auto it = std::find_if(s.begin(), s.end(),
                    [](char c) {
                        return !std::isspace<char>(c, std::locale::classic());
                    });
    s.erase(s.begin(), it);
    return s;
}
 
std::string& _rtrim(std::string &s)
{
    auto it = std::find_if(s.rbegin(), s.rend(),
                    [](char c) {
                        return !std::isspace<char>(c, std::locale::classic());
                    });
    s.erase(it.base(), s.end());
    return s;
}
 
std::string& _trim(std::string &s)
{
    return _ltrim(_rtrim(s));
}
