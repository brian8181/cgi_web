#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include "fileio.hpp"
#include "utility.hpp"
#include "patterns.hpp"

const unsigned int DEFAULT_TEMPLATE = 1;
const unsigned int PROJECT_FOLDER = 2;

using namespace std;

string sequence(const string &src, const string &sequence);

int main(int argc, char *argv[])
{
    string path; // source (text to match)
    string exp;  // regular expresssion

    if (argc == 3)
    {
        path = argv[1];
        exp = argv[2];
    }

    // read file
    std::ifstream ifile_strm(path);
    std::string src((std::istreambuf_iterator<char>(ifile_strm)), std::istreambuf_iterator<char>());

    cout << "Source text ..." << endl;
    cout << src;
    cout << endl
         << "End text." << endl;

    sequence(src, exp);
}

string sequence(const string &src, const string &sequence)
{
    regex exp = regex(sequence, regex::ECMAScript); // match
    auto begin = sregex_iterator(src.begin(), src.end(), exp, std::regex_constants::match_default);
    auto end = sregex_iterator();

    string output;
    int src_beg_pos = 0;
    for (sregex_iterator iter = begin; iter != end; ++iter)
    {
        smatch match = *iter;
        int len = match.size();

        for (int i = 0; i < len; ++i)
        {
            if (match[i].matched)
            {
                cout << "match[" << i << "] = " << match[i].str() << endl;
            }
        }
    }
    return output;
}
