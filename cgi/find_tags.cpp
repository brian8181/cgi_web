#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
    if(1)
    //if(argc == 1)
    {
        // todo: validate inputs !
        string path = argv[1];

        string src;
        fstream file;
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

        //cout << src << endl;
        string name_exp = "\\$[A-Za-z]+\\w*";
        regex src_epx = regex("\\{\\s*\\$([A-Za-z]+\\w*)\\s*\\}");
        
        auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
        auto end = sregex_iterator(); 
        
        // for each match
		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            std::ssub_match sub = match[1];
            cout << match.str() <<  " --> " << sub.str() << endl;
        }
    }
}