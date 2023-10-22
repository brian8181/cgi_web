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
APPNAME = cgi_web
EXT = cpp
EXE = cgi
ROOTDIR  = ~/src/cgi_web
BUILDDIR = $(ROOTDIR)/build
SRCDIR = $(ROOTDIR)/src
OBJDIR = $(ROOTDIR)/build
streamyDIR = ~/src/streamy-cpp

world: all dump_matches.o bash_test.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump_matches.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump_matches.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/display_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/display_test.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test.$(EXE)
		
all: utility.o load_conf.o test_include.$(EXE) test_variable.$(EXE) \
	test_if_sequence.$(EXE) test_foreach_sequence.$(EXE) test_get_conf.$(EXE) lex_all.$(EXE) test_get_conf.$(EXE) test_sequence.cgi
	
# default.$(EXE): streamy.o utility.o
# 	$(CXX) $(CXXFLAGS) $(SRCDIR)/index1.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/default.$(EXE)

# fast: default_test.$(EXE)

default_test.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/default_test.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/default_test.$(EXE)

# index_.01.$(EXE): 
#   	$(CXX) $(CXXFLAGS) $(SRCDIR)/index.01.cpp -o $(BUILDDIR)/index.01.$(EXE)

# regex_find.$(EXE): utility.o main.o regex_find.o 
# 	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(BUILDDIR)/main.o $(BUILDDIR)/regex_find.o -o $(BUILDDIR)/regex_find.$(EXE)

# find_tags.$(EXE): utility.o find_tags.o
# 	$(CXX) $(CXXFLAGS) $(BUILDDIR)/find_tags.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/find_tags.$(EXE)

# streamy_test.$(EXE): streamy.o
# 	$(CXX) $(CXXFLAGS) $(SRCDIR)/streamy_test.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/streamy_test.$(EXE)

fileio_trim: 
	$(CXX) $(CXXFLAGS) -c ./src/fileio_trim.cpp -o $(BUILDDIR)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) -c ./src/fileio.cpp -o $(BUILDDIR)/fileio.o	
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/fileio_trim.o $(BUILDDIR)/fileio.o -o $(BUILDDIR)/fileio_trim

test_if_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_if_sequence.cpp -o $(BUILDDIR)/test_if_sequence.cgi

test_foreach_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_foreach_sequence.cpp -o $(BUILDDIR)/test_foreach_sequence.cgi

# lex.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/lex.cpp -o $(BUILDDIR)/lex.cgi

lex_all.cgi:
	$(CXX) $(CXXFLAGS) -c ./src/fileio.cpp -o $(BUILDDIR)/fileio.o	
	$(CXX) $(CXXFLAGS) -c ./src/lex_all.cpp -o $(BUILDDIR)/lex_all.o	
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/fileio.o $(BUILDDIR)/lex_all.o -o $(BUILDDIR)/lex_all.$(EXE)
	cp $(SRCDIR)/lex_all.conf $(BUILDDIR)/lex_all.conf  

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

# streamy.a: streamy.o
# 	ar rvs $(BUILDDIR)/streamy.a $(BUILDDIR)/streamy.o

# streamy.o: 
# 	$(CXX) $(CXXFLAGS) -c $(streamyDIR)/src/streamy.cpp -o $(BUILDDIR)/streamy.o

# main.o:
# 	$(CXX) $(CXXFLAGS) -c $(ROOTDIR)/src/main.$(EXT) -o $(BUILDDIR)/main.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/load_conf.cpp -o $(BUILDDIR)/load_conf.o

dump.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump.cpp -o $(BUILDDIR)/dump.o

dump_matches.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump_matches.cpp -o $(BUILDDIR)/dump_matches.o

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/find_tags.cpp -o $(BUILDDIR)/find_tags.o
	$(CXX) $(CXXFLAGS)  $(BUILDDIR)/find_tags.o -o $(BUILDDIR)/find_tags.cgi

# regex_find.o: 
# 	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/regex_find.cpp -o $(BUILDDIR)/regex_find.o

utility.o:
	$(CXX) $(CXXFLAGS) -c $(ROOTDIR)/src/utility.cpp -o $(BUILDDIR)/utility.o

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
	