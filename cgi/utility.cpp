#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

using namespace std;

string file_readall(string path)
{
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
            input += tp += "\n";
        }
        file.close(); //close the file object.
    }
}