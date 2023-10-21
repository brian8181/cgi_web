#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <regex>
#include "fileio.hpp"

using namespace std;

string lex_all(const string &src);
map<string, string> get_config(string path);

void test_smatch();
void lex();
void  lex_tmpl(string& s);

int main(int argc, char *argv[])
{
    std::filesystem::path path(argv[0]);
    string root_path = path.replace_extension("conf");
    map<string, string> pairs = get_config(root_path);

    const string project_folder = pairs["project_folder"];
    const string template_folder = pairs["template_folder"];
    const string default_template = pairs["default_template"];
    
    // check for input or use default
    string template_name = default_template;
    if (argc > 1)
    {
        template_name.clear();
        template_name = argv[1];
    }

    const string file_path = template_folder + template_name;
    string output;
    try
    {
        string src = ifs_read_all(file_path);
        output = lex_all(src);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading file ... " << e.what() << endl;
    }
    cout << output;
    test_smatch();

    //lex();

    string s = "AAAA {TAG1}\nBBB {TAG2}\n{TAG3}ZZZ";
    lex_tmpl(s);
    return 0;
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
            string name = line.substr(0, pos - 1);
            string value = line.substr(pos + 1);
            pair<string, string> p(trim(name), trim(value));
            config.insert(p);
        }
        file.close();
    }
    return config;
}

void lex()
{
    cout << "Lexing..." << endl;
    string s = "for a good time, call 867-5309 aaa 231-5555  ddd 8555-9999 444-7777";
    regex rexp("\\d{3}-\\d{4}");
    // const string ESCAPE = "\\{[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,]*\\}";
    // regex exp = regex(ESCAPE, regex::ECMAScript); // match
    smatch phone_match;

    while(std::regex_search(s, phone_match, rexp, std::regex_constants::match_default))
    {
        //std::string match_beg = phone_match.format("$`");
        std::string match = phone_match.format("$`{$&}");
        s = phone_match.format("$'");
        //std::cout << match_beg;
        std::cout << match;
        //std::cout << match_end << '\n';
    }
  

    cout << "End Lexing..." << endl;
}

void  lex_tmpl(string& s)
{
    cout << "Lexing..." << endl;

    const string ESCAPE = "\\{[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,]*\\}";
    regex exp = regex(ESCAPE, regex::ECMAScript); // match
    smatch match;

    while(std::regex_search(s, match, exp, std::regex_constants::match_default))
    {
        std::string fmt_match_beg = match.format("$`");
        std::string fmt_match = match.format("$&");
        s = match.format("$'");
        std::cout << fmt_match_beg << endl;
        std::cout << fmt_match << endl;
    }
    cout << s << endl;

    cout << "End Lexing..." << endl;
}

// find text & tags
string lex_all(const string &src)
{
    const string ESCAPE = "\\{[\\w\\s\\[\\]+-=|$><^/#@~&*.%!~`_:;\"'\\\\,]*\\}";
    regex exp = regex(ESCAPE, regex::ECMAScript); // match

    const string s = "for a good time, call 867-5309 aaa 231-5555";
    smatch phone_match;
    regex phone_regex("\\d{3}-\\d{4}");
    //bool mathed = regex_match(s.end(), s.begin(), s_match, exp, std::regex_constants::match_default);
    if (std::regex_search(s, phone_match, phone_regex, std::regex_constants::match_default))
    {
        // std::string fmt_s = phone_match.format(
        //     "$`"   // $` means characters before the match
        //     "[$&]"); // $& means the matched characters
        //     //"$'"); // $' means characters following the match
        // std::cout << fmt_s << '\n';

        // std::string fmt_s = phone_match.format("$`$&$'"); // $& means the matched characters
        // std::cout << fmt_s << '\n';

        if (std::regex_search(s, phone_match, phone_regex, std::regex_constants::match_default))
        {
            std::string match_beg = phone_match.format("$`");
            std::string match = phone_match.format("$&");
            std::string match_end = phone_match.format("$'");
            std::cout << match_beg << '\n';
            std::cout << match << '\n';
            std::cout << match_end << '\n';
        }
        
        // if (std::regex_search(fmt_s, phone_match, phone_regex, std::regex_constants::match_default))
        // {
        //     std::string fmt_s_end = phone_match.format("$`$&");
        //     std::cout << fmt_s_end << '\n';
        // }
    }

    //while(regex_match(s.end(), s.begin(), phone_match, phone_regex, std::regex_constants::match_default))
    // while(std::regex_search(s, phone_match, phone_regex, std::regex_constants::match_default))
    // {
    //     std::string fmt_s = phone_match.format(
    //         "$`"   // $` means characters before the match
    //         "[$&]" // $& means the matched characters
    //         "$'"); // $' means characters following the match
    //     std::cout << fmt_s << '\n';
    // }

    sregex_iterator begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    sregex_iterator end = sregex_iterator(src.end(), src.end(), exp, std::regex_constants::match_default);

    int matches = 0;
    string output;
    sregex_iterator prev_iter = end;

    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        // smatch pmatch = *prev_iter;

        // int match_beg_pos = match.position();
        // int match_end_pos = 0;
         
        // if(prev_iter != end)
        // {
        //     match_end_pos = prev_iter->position() + prev_iter->length();
        // }
        // // get from end of last match (src_beg_pos) to begin of current
        // string text = src.substr(match_end_pos, match_beg_pos);
        // if(src[match_beg_pos] == '\n')
        //     text += '\n';

        // string t = "testing";
        // t += '\n';
        // t += "new_line";
        // cout << t << endl;

        // output += "TEXT:" + text;

        string token = match.str();
        output += "TAG:" + token + '\n';

        // prev_iter = iter;
    }
    return output;
}

void test_smatch()
{
    std::string s = "for a good time, call 867-5309";
    std::regex phone_regex("\\d{3}-\\d{4}");
    std::smatch phone_match;
 
    if (std::regex_search(s, phone_match, phone_regex))
    {
        std::string fmt_s = phone_match.format(
            "$`"   // $` means characters before the match
            "[$&]" // $& means the matched characters
            "$'"); // $' means characters following the match
        std::cout << fmt_s << '\n';
    }   
}
