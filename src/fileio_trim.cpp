#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>		/* for STDIN_FILENO */
#include <sys/select.h> /* for pselect   */
#include <getopt.h>
#include "fileio.hpp"

using std::cin;
using std::string;

int stdin_ready(int filedes)
{
	fd_set set;
	/* declare/initialize zero timeout */
	struct timespec timeout = {.tv_sec = 0};
	/* Initialize the file descriptor set. */
	FD_ZERO(&set);
	FD_SET(filedes, &set);
	/* check whestdin_ready is ready on filedes */
	return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
}

int main(int argc, char *argv[])
{
	try
	{
		if (stdin_ready(STDIN_FILENO))
		{
			string buffer;
			cin >> buffer;
			// add piped buffer to end of argv
			char *argvtmp[sizeof(char *) * argc + 1];
			memcpy(argvtmp, argv, sizeof(char *) * argc);
			argvtmp[argc] = &buffer[0];
			argv = argvtmp;
			++argc;
		}
		
        int opt = 0;
        //int option_index = 0;
        //bool file_flag = false;
        //bool verbose_flag = false;
        
        while ((opt = getopt (argc, argv, "abc:")) != -1)
        {
            switch (opt)
            {
            case 'h':
                //print_help();
                return 0; 
            case 'v':
                //verbose_flag = true;
                break;
            case 'f':
                //file_flag = true;
                break; 
            default: // unknown option before args
                fprintf(stderr, "Unexpected option, -h for help\n");
                return EXIT_FAILURE;
            }
        }

        string s = argv[1];
        char* cs = argv[1];
        std::cout << &cs << endl;
        std::cout << &(cs[0]) << endl;
        std::cout << &s << endl;

        std::cout << "Before ltrim \"" << s << "\"" << std::endl; 
        s = ltrim(s);
        std::cout << "After ltrim \"" << s << "\"" << std::endl; 
        std::cout << "Before rtrim \"" << s << "\"" << std::endl; 
        s = rtrim(s);
        std::cout << "After rtrim \"" << s << "\"" << std::endl; 
        std::cout << &s << endl;
    }
	catch (std::logic_error &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}