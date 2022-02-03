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

        regex src_epx;
        try
		{
			//src_epx = regex("^{(.*)}$");
            src_epx = regex("\\{\\$.*\\}");
		}
		catch(regex_error& e)
		{
			cerr << "exception caught: " << e.what() << '\n';
			cerr << "error of type " << e.code() << " was unhandled\n";
		} 

        auto begin = sregex_iterator(src.begin(), src.end(), src_epx);
		auto end = sregex_iterator(); 
		//int match_i = 0;

        // for each match
		for (sregex_iterator iter = begin; iter != end; ++iter)
		{
            smatch match = *iter;
            cout << match.str() << endl;
            //cout << match.size() << endl;
        }
    }
}