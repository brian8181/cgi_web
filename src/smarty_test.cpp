#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include "../src/utility.hpp"
#include "../../smarty-cpp/src/smarty.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    smarty sm("test1", "test2", "test3", "test4");
    sm.assign("x", "5");
    sm.display("no_name");
}
