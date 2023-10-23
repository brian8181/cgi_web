# cgi_web

# Compiler settings - Can be customized.
CXX = g++
LDFLAGS = -static -lcgicc -L/usr/lib/
INCLUDES = -I/usr/include/cgicc/
# add addtional libs here

# Makefile settings - Can be customized.
EXT = cpp
EXE = cgi
SRC = ./src
BLD = ./build
OBJ = ./build

all: lex fileio_trim test_include.cgi test_get_conf.cgi test_variable.cgi test_if_sequence.cgi 

obj: load_conf.o find_tags.o utility.o

lex:
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o	
	$(CXX) $(CXXFLAGS) -c $(SRC)/lex.cpp -o $(BLD)/lex.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/lex.o -o $(BLD)/lex
	cp $(SRC)/lex.conf $(BLD)/lex.conf  

fileio_trim: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio_trim.cpp -o $(BLD)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio_trim.o $(BLD)/fileio.o -o $(BLD)/fileio_trim

default_test.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRC)/default_test.cpp $(BLD)/streamy.o $(BLD)/utility.o $(LDFLAGS) -o $(BLD)/default_test.$(EXE)

find_tags.$(EXE): utility.o fileio.o find_tags.o
	$(CXX) $(CXXFLAGS) $(BLD)/find_tags.o $(BLD)/utility.o -o $(BLD)/find_tags.$(EXE)

test_if_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.cgi

test_foreach_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_foreach_sequence.cpp -o $(BLD)/test_foreach_sequence.cgi

dump_matches.$(EXE): utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/dump_matches.cpp -o $(BLD)/dump_matches.o
	$(CXX) $(CXXFLAGS) $(BLD)/dump_matches.o $(BLD)/utility.o -o $(BUIL/DDIR)/dump_matches.$(EXE)

test_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_sequence.cpp -o $(BLD)/test_sequence.cgi

test_comment.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_comment.cpp -o $(BLD)/test_comment.cgi

test_include.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_include.cpp -o $(BLD)/test_include.cgi

test_get_conf.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_get_conf.cpp -o $(BLD)/test_get_conf.cgi

test_variable.cgi: 
	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_variable.cpp -o $(BLD)/test_variable.cgi

fileio.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o	

find_tags.o: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/find_tags.cpp -o $(BLD)/find_tags.o
	$(CXX) $(CXXFLAGS)  $(BLD)/find_tags.o -o $(BLD)/find_tags.cgi

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/load_conf.cpp -o $(BLD)/load_conf.o

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BLD)/utility.o

.PHONY: upload
upload:
	cp -rf $(BLD)/*.$(EXE) /var/www/html/cgi
	
.PHONY: clean_upload
clean_upload:
	rm $(BLD)/*.$(EXE)
	
.PHONY: clean
clean:
	-rm $(BLD)/*