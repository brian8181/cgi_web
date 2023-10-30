# cgi_web
# Mon Oct 30 09:11:47 AM CDT 2023

CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -DDEBUG
LDFLAGS = -lcgicc
INCLUDES = -I/usr/include/cgicc/
EXT = cpp
SRC = src
BLD = build
OBJ = build

all: lex index.cgi fileio_trim default_test.cgi find_tags.cgi dump_matches.cgi \
     test_sequence.cgi test_comment.cgi test_include.cgi test_get_conf.cgi test_variable.cgi test_if_sequence.cgi test_foreach_sequence.cgi

lex: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/lex.cpp -o $(BLD)/lex.o	
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio.o $(BLD)/lex.o -o $(BLD)/lex
	
index.cgi: fileio.o utility.o streamy.o index.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(BLD)/index.o $(LDFLAGS) -o $(BLD)/index.cgi

fileio_trim: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio_trim.cpp -o $(BLD)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/fileio_trim.o -o $(BLD)/fileio_trim

default_test.cgi: fileio.o utility.o streamy.o 
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/default_test.cpp $(LDFLAGS) -o $(BLD)/default_test.cgi

find_tags.cgi: find_tags.o fileio.o utility.o 
	$(CXX) $(CXXFLAGS) $(BLD)/find_tags.o $(BLD)/fileio.o $(BLD)/utility.o -o $(BLD)/find_tags.cgi

dump_matches.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/dump_matches.cpp -o $(BLD)/dump_matches.cgi

test_if_sequence.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.cgi.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.cgi

test_foreach_sequence.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_foreach_sequence.cpp $(LDFLAGS) -o $(BLD)/test_foreach_sequence.cgi

test_sequence.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_sequence.cpp -o $(BLD)/test_sequence.cgi

test_comment.cgi: fileio.o utility.o streamy.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/test_comment.cpp -o $(BLD)/test_comment.cgi

test_include.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_include.cpp -o $(BLD)/test_include.cgi

test_get_conf.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_get_conf.cpp -o $(BLD)/test_get_conf.cgi

test_variable.cgi: fileio.o utility.o streamy.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/test_variable.cpp -o $(BLD)/test_variable.cgi

fileio.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o	

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BLD)/utility.o

streamy.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/streamy.cpp -o $(BLD)/streamy.o

index.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/index.cpp -o $(BLD)/index.o

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/find_tags.cpp -o $(BLD)/find_tags.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/load_conf.cpp -o $(BLD)/load_conf.o

.PHONY: upload
upload:
	cp -rf $(BLD)/*.cgi /var/www/html/cgi
	
.PHONY: clean_upload
clean_upload:
	rm $(BLD)/*.cgi
	
.PHONY: clean
clean:
	-rm $(BLD)/*