// proof of concept

#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>		/* for STDIN_FILENO */
#include <sys/select.h> /* for pselect   */
#include "main.hpp"

using namespace std;

// constants
const int BUFFER_LEN = 0xFF;
const int DEFAULT_ARGC = 2;
const string VERSION_STRING = "cgi proof of concept: 0.0.1";

static struct option long_options[] =
	{
		{"verbose", no_argument, 0, 'v'},
		{"help", no_argument, 0, 'h'},
		{"version", no_argument, 0, 'r'}};

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
		return parse_options(argc, argv);
	}
	catch (std::logic_error &ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

void print_version()
{
	cout << VERSION_STRING << endl;
}

void print_help()
{
	// 	cout << "Usage: "
	// 		 << FMT_BOLD      << "rx"          << FMT_RESET << " "
	// 		 << FMT_UNDERLINE << "[OPTION]..." << FMT_RESET << " "
	// 		 << FMT_UNDERLINE << "PATTERN"     << FMT_RESET << " "
	// 		 << FMT_UNDERLINE << "INPUT..."    << FMT_RESET << endl;
}

int parse_options(int argc, char *argv[])
{
	int opt = 0;
	int option_index = 0;
	optind = 0;
	opt = getopt_long(argc, argv, "hvispPreEo", long_options, &option_index);
	while (opt != -1)
	{
		switch (opt)
		{
		case 'h':
			print_help();
			return 0;
		case 'v':
			// OPTION_FLAGS |= VERBOSE;
			break;
		case 'r':
			print_version();
			return 0;
		default: // unknown option before args
			cerr << "Unexpected option, -h for help" << endl;
			return -1;
		}
		opt = getopt_long(argc, argv, "hvispPreEo", long_options, &option_index);
	}
	return 0;
}
