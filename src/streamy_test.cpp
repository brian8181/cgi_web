#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "utility.hpp"
#include "../../streamy-cpp/src/streamy.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    streamy sm("test1", "test2", "test3", "test4");
    sm.assign("x", "5");
    sm.display("no_name");
}
