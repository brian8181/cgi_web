#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <algorithm>
#include "utility.hpp"

string readlines(string path)
{
    string src;
    ifstream file;
    file.open(path, ios::in); //open a file to perform read operation using file object
    if (file.is_open())
    {   
        //checking whether the file is open
        string tp;
        while(getline(file, tp))
        { 
            //read data from file object and put it into string.
            src += tp += "\n";
        }
        file.close(); //close the file object.
    }
    return src;
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

// string ifstream_readlines(string path)
// {
//     string src;
//     ifstream file;
//     file.open(path, ios::in); //open a file to perform read operation using file object
//
//     if (file.is_open())
//     {   
//         //checking whether the file is open
//         string tp;
//         while(getline(file, tp))
//         { 
//             //read data from file object and put it into string.
//             src += tp += "\n";
//         }
//         file.close(); //close the file object.
//     }
//     return src;
// }

// string fstream_read(string path)
// {
//     string str;
//     fstream file;
//     file.open(path, ios::in); //open a file to perform read operation using file object
//     if (file.is_open())
//     {   
//         //checking whether the file is open
//         char c[256];
//         while(file.read(c, 256))
//         { 
//             //read data from file object and put it into string.
//             str.append(c);
//             //str.append("\n");
//         }
//         file.close(); //close the file object.
//     }
//     return str;
// }

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
