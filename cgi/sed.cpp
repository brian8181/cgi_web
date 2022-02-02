// get not params
#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{

    if(argc == 4)
    {
        string path = argv[1];
        regex pattern(argv[2]);
        string replace = argv[3];

        string input;
        fstream file;
        file.open(path, ios::in); //open a file to perform read operation using file object
        if (file.is_open())
        {   
            //checking whether the file is open
            string tp;
            while(getline(file, tp))
            { 
                //read data from file object and put it into string.
                //cout << tp << "\n"; //print the data of the string
                input += tp += "\n";
            }
            file.close(); //close the file object.
        }

        //cout << input;

        // write the results to an output iterator
        std::regex_replace(std::ostreambuf_iterator<char>(std::cout), input.begin(), input.end(), pattern, replace);
    }
    else
    {
        cout << "content-type: text/html" << endl << endl;
        cout << "<h1>CGI C++ example</h1>" << endl;
    }
}