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
OBJDIR = $(ROOTDIR)/src
SMARTYDIR = /home/brian/src/smarty-cpp

# compile & link for debug
# debug: 
# 	#$(CXXFLAGS) += -DDEBUG -g
# debug: all

# # compile & link for debug GDBversion variable
# debuggdb: 
# 	#$(CXXFLAGS) += -DDEBUG -ggdb # compile & link

world: all dump_matches.o find_tags.o smarty_test.$(EXE) index_test.$(EXE) smarty.a test.cgi bash_test.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.$(EXE)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump_matches.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump_matches.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/display_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/display_test.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test.$(EXE)
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test2.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test2.$(EXE)
	
	
all: utility.o load_conf.o dump.o find_tags.$(EXE) regex_find.$(EXE)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/load_conf.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/load_conf.$(EXE)
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.$(EXE)


index_test.$(EXE): smarty.o utility.o
	$(CXX) $(CXXFLAGS) $(SRCDIR)/index.cpp $(BUILDDIR)/smarty.o $(BUILDDIR)/utility.o $(LDFLAGS) -o $(BUILDDIR)/index_test.$(EXE)

# index.01.$(EXE): 
#   	$(CXX) $(CXXFLAGS) $(SRCDIR)/index.01.cpp -o $(BUILDDIR)/index.01.$(EXE)

regex_find.$(EXE): utility.o main.o regex_find.o 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/utility.o $(BUILDDIR)/main.o $(BUILDDIR)/regex_find.o -o $(BUILDDIR)/regex_find.$(EXE)

find_tags.$(EXE): utility.o find_tags.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/find_tags.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/find_tags.$(EXE)

smarty_test.$(EXE): smarty.o
# 	$(CXX) $(CXXFLAGS) $(SRCDIR)/smarty_test.cpp $(BUILDDIR)/smarty.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/smarty_test.$(EXE)

smarty.a: smarty.o
	ar rvs $(BUILDDIR)/smarty.a $(BUILDDIR)/smarty.o

smarty.o: 
	$(CXX) $(CXXFLAGS) -c $(SMARTYDIR)/src/smarty.cpp -o $(BUILDDIR)/smarty.o

main.o:
	$(CXX) $(CXXFLAGS) -c $(ROOTDIR)/src/main.$(EXT) -o $(BUILDDIR)/main.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/load_conf.cpp -o $(BUILDDIR)/load_conf.o

dump.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump.cpp -o $(BUILDDIR)/dump.o

test.cgi: 
	$(CXX) $(CXXFLAGS) $(SRCDIR)/test.cpp $(LDFLAGS) -o $(BUILDDIR)/test.cgi

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
	cp -rf bash_test.sh $(BUILDDIR)/bash_test.cgi

.PHONY: upload
upload:
	cp -rf $(BUILDDIR)/*.$(EXE) /var/www/html/cgi
	cp -rf $(SRCDIR)/* /var/www/html/cgi

.PHONY: clean_upload
clean_upload:
	rm $(BUILDDIR)/*.$(EXE)
	
.PHONY: clean
clean:
	rm $(BUILDDIR)/*.$(EXE) $(BUILDDIR)/*.[oa]
