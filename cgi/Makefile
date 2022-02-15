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
ROOTDIR  = /home/brian/src/cgi_web
BUILDDIR = $(ROOTDIR)/build
SRCDIR = $(ROOTDIR)/cgi
OBJDIR = $(ROOTDIR)/cgi
SMARTYDIR = /home/brian/src/smartycpp

# compile & link for debug
# debug: 
# 	#$(CXXFLAGS) += -DDEBUG -g
# debug: all

# # compile & link for debug GDBversion variable
# debuggdb: 
# 	#$(CXXFLAGS) += -DDEBUG -ggdb # compile & link

world: all dump_matches.o find_tags.o 
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump_matches.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump_matches.cgi
	$(CXX) $(CXXFLAGS) $(SRCDIR)/display_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/display_test.cgi
	$(CXX) $(CXXFLAGS) $(SRCDIR)/replace_test.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/replace_test.cgi
	
	
all: utility.o load_conf.o dump.o index.cgi index2.cgi find_tags.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/load_conf.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/load_conf.cgi
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/dump.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/dump.cgi
	
index.cgi:
	$(CXX) $(CXXFLAGS) $(SRCDIR)/index.cpp $(BUILDDIR)/utility.o -o $(BUILDDIR)/index.cgi

index2.cgi:
	$(CXX) $(CXXFLAGS) $(SRCDIR)/index2.cpp $(BUILDDIR)/smarty.o $(LDFLAGS) -o $(BUILDDIR)/index2.cgi

find_tags.cgi: utility.o find_tags.o
	$(CXX) $(CXXFLAGS) $(BUILDDIR)/find_tags.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/find_tags.cgi

# smarty_test.cgi: smarty.o
# 	$(CXX) $(CXXFLAGS) $(SRCDIR)/smarty_test.cpp $(BUILDDIR)/smarty.o $(BUILDDIR)/utility.o -o $(BUILDDIR)/smarty_test.cgi

smarty.o: 
	$(CXX) $(CXXFLAGS) -c $(SMARTYDIR)/src/smarty.cpp -o $(BUILDDIR)/smarty.o

# # smarty.a:
# # 	$(CXX) $(CXXFLAGS) -c $(SMARTYDIR)/src/smarty.cpp -o $(BUILDDIR)/smarty.o
# # 	ar rvs smarty.a smarty.o
	
# # main.o:
# # 	$(CXX) $(CXXFLAGS) -c $(ROOTDIR)/src/main.cpp -o $(BUILDDIR)/main.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/load_conf.cpp -o $(BUILDDIR)/load_conf.o

dump.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump.cpp -o $(BUILDDIR)/dump.o

dump_matches.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/dump_matches.cpp -o $(BUILDDIR)/dump_matches.o

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/find_tags.cpp -o $(BUILDDIR)/find_tags.o

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRCDIR)/utility.cpp -o $(BUILDDIR)/utility.o

.PHONY: upload
upload:
	cp -rf $(BUILDDIR)/*.cgi /var/www/html/cgi
	cp -rf $(SRCDIR)/* /var/www/html/cgi
	
.PHONY: clean
clean:
	rm $(BUILDDIR)/*.cgi $(BUILDDIR)/*.o