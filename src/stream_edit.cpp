#include <iostream>
#include <fstream>
using namespace std;

void read_stream(int len, string& out_data)
{
    out_data = "hi";
}

void write_stream(string& data)
{

}

long get_stream_len()
{
    streampos begin,end;
    ifstream myfile ("example.bin", ios::binary);
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    myfile.close();
    return (end-begin);
}