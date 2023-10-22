# cgi scripts
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++17 -DDEBUG -g

# lib settings
LDFLAGS = -static -lcgicc -L/usr/lib/
INCLUDES = -I/usr/include/cgicc/
# add addtional libs here

# Makefile settings - Can be customized.
EXT = cpp
EXE = cgi
BUILDDIR = ./build
SRCDIR = ./src
OBJDIR = ./build

all: lex fileio_trim test_include.$(EXE) test_variable.$(EXE) test_if_sequence.$(EXE) test_foreach_sequence.$(EXE) test_get_conf.$(EXE) test_get_conf.$(EXE) test_sequence.$(EXE)

lex:
	$(CXX) $(CXXFLAGS) -c ./src/fileio.cpp -o $(BUILDDIR)/fileio.o	
	$(CXX) $(CXXFLAGS) -c ./src/lex.cpp -o $(BUILDDIR)/lex.o	
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/fileio.o $(BUILDDIR)/lex.o -o $(BUILDDIR)/lex
	cp $(SRCDIR)/lex.conf $(BUILDDIR)/lex.conf  

fileio_trim: 
	$(CXX) $(CXXFLAGS) -c ./src/fileio_trim.cpp -o $(BUILDDIR)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) -c ./src/fileio.cpp -o $(BUILDDIR)/fileio.o	
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/fileio_trim.o $(BUILDDIR)/fileio.o -o $(BUILDDIR)/fileio_trim

default_test.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/default_test.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/default_test.$(EXE)

find_tags.$(EXE): utility.o find_tags.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/find_tags.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/find_tags.$(EXE)

test_if_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_if_sequence.cpp -o $(BUILDDIR)/test_if_sequence.cgi

test_foreach_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_foreach_sequence.cpp -o $(BUILDDIR)/test_foreach_sequence.cgi

dump_matches.$(EXE):
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump_matches.cpp -o $(BUILDDIR)/dump_matches.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump_matches.o $(BUILDDIR)/utility.o -o $(BUIL/DDIR)/dump_matches.$(EXE)

test_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_sequence.cpp -o $(BUILDDIR)/test_sequence.cgi

test_comment.cgi:
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_comment.cpp -o $(BUILDDIR)/test_comment.cgi

test_include.cgi: 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_include.cpp -o $(BUILDDIR)/test_include.cgi

test_get_conf.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_get_conf.cpp -o $(BUILDDIR)/test_get_conf.cgi

test_variable.cgi: 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_variable.cpp -o $(BUILDDIR)/test_variable.cgi

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/load_conf.cpp -o $(BUILDDIR)/load_conf.o

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/find_tags.cpp -o $(BUILDDIR)/find_tags.o
	$(CXX) $(CXXFLAGS)  $(BUILDDIR)/find_tags.o -o $(BUILDDIR)/find_tags.cgi

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/utility.cpp -o $(BUILDDIR)/utility.o

# just copy & change extension to "cgi"
bash_test.cgi:
	cp -rf $(SRCDIR)/cgi_test_script.sh $(BUILDDIR)/bash_test.cgi

.PHONY: upload
upload:
	cp -rf $(BUILDDIR)/*.$(EXE) /var/www/html/cgi
	
.PHONY: clean_upload
clean_upload:
	rm $(BUILDDIR)/*.$(EXE)
	
.PHONY: clean
clean:
	-rm -f $(BUILDDIR)/*.$(EXE) $(BUILDDIR)/*.[oa]
	