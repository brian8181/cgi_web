# cgi scripts
BUILD_VERSION = 0.1.0

prefix = /usr/local
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1

# Compiler settings - Can be customized.
CXX = g++
CXXFLAGS = -std=c++17 -DDEBUG -ggdb

# lib settings
LDFLAGS = -static -lcgicc -L/usr/lib/
INCLUDES = -I/usr/include/cgicc/
# add addtional libs here

# Makefile settings - Can be customized.
APPNAME = cgi_web
EXT = cpp
EXE = cgi
ROOTDIR  = /home/brian/src/cgi_web
BUILDDIR = $(ROOTDIR)/build
SRCDIR = $(ROOTDIR)/src
OBJDIR = $(ROOTDIR)/build
streamyDIR = /home/brian/src/streamy-cpp

# compile & link for debug
# debug: 
# 	#$(CXXFLAGS) += -DDEBUG -g
# debug: all

# # compile & link for debug GDBversion variable
# debuggdb: 
# 	#$(CXXFLAGS) += -DDEBUG -ggdb # compile & link

world: all dump_matches.o find_tags.o streamy_test.$(EXE) default.$(EXE) streamy.a cgi_test_script.cgi bash_test.cgi default_test.cgi lex.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.$(EXE)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump_matches.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump_matches.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/display_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/display_test.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test2.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test2.$(EXE)
	
	
all: utility.o load_conf.o dump.o find_tags.$(EXE) regex_find.$(EXE) test_include.$(EXE) test_variable.$(EXE) \
	test_if_sequence.$(EXE) test_foreach_sequence.$(EXE) test_get_conf.$(EXE) lex_all.$(EXE) test_get_conf.$(EXE) streamy_test.$(EXE) test_sequence.cgi

	$(CXX) $(CXXFLAGS) $(BUILDDIR)/load_conf.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/load_conf.$(EXE)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.$(EXE)
	
default.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/index1.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/default.$(EXE)

fast: default_test.$(EXE)

default_test.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/default_test.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/default_test.$(EXE)

# index_.01.$(EXE): 
#   	$(CXX) $(CXXFLAGS) $(SRCDIR)/index.01.cpp -o $(BUILDDIR)/index.01.$(EXE)

regex_find.$(EXE): utility.o main.o regex_find.o 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(BUILDDIR)/main.o $(BUILDDIR)/regex_find.o -o $(BUILDDIR)/regex_find.$(EXE)

find_tags.$(EXE): utility.o find_tags.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/find_tags.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/find_tags.$(EXE)

streamy_test.$(EXE): streamy.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/streamy_test.cpp $(BUILDDIR)/streamy.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/streamy_test.$(EXE)

# fread.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/fread.cpp -o $(BUILDDIR)/fread.cgi

test_if_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_if_sequence.cpp -o $(BUILDDIR)/test_if_sequence.cgi

test_foreach_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_foreach_sequence.cpp -o $(BUILDDIR)/test_foreach_sequence.cgi

lex.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/lex.cpp -o $(BUILDDIR)/lex.cgi

lex_all.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/lex_all.cpp -o $(BUILDDIR)/lex_all.cgi

test_sequence.cgi:
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_sequence.cpp -o $(BUILDDIR)/test_sequence.cgi

test_comment.cgi:
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_comment.cpp -o $(BUILDDIR)/test_comment.cgi

test_include.cgi: 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_include.cpp -o $(BUILDDIR)/test_include.cgi

test_get_conf.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_get_conf.cpp -o $(BUILDDIR)/test_get_conf.cgi

test_variable.cgi: 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(SRCDIR)/test_variable.cpp -o $(BUILDDIR)/test_variable.cgi

streamy.a: streamy.o
	ar rvs $(BUILDDIR)/streamy.a $(BUILDDIR)/streamy.o

streamy.o: 
	$(CXX) $(CXXFLAGS) -c $(streamyDIR)/src/streamy.cpp -o $(BUILDDIR)/streamy.o

main.o:
	$(CXX) $(CXXFLAGS) -c $(ROOTDIR)/src/main.$(EXT) -o $(BUILDDIR)/main.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/load_conf.cpp -o $(BUILDDIR)/load_conf.o

dump.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump.cpp -o $(BUILDDIR)/dump.o

cgi_test_script.cgi: 
	$(CXX) $(CXXFLAGS) $(SRCDIR)/cgi_test_script.cpp $(LDFLAGS) -o $(BUILDDIR)/cgi_test_script.cgi

dump_matches.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump_matches.cpp -o $(BUILDDIR)/dump_matches.o

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/find_tags.cpp -o $(BUILDDIR)/find_tags.o

regex_find.o: 
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/regex_find.cpp -o $(BUILDDIR)/regex_find.o

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
	rm $(BUILDDIR)/*.$(EXE) $(BUILDDIR)/*.[oa]
	