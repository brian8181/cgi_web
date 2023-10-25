# cgi_web
CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -DDEBUG
LDFLAGS = -static -lcgicc -L/usr/lib64/
INCLUDES = -I/usr/include/cgicc/
EXT = cpp
SRC = ./src
BLD = ./build
OBJ = ./build

all: lex fileio_trim find_tags.cgi test_if_sequence.cgi

lex: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/lex.cpp -o $(BLD)/lex.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/lex.o -o $(BLD)/lex
	cp $(SRC)/lex.conf $(BLD)/lex.conf  

# NOT LINKING!
index.cgi: streamy.o utility.o index.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/streamy.o $(BLD)/utility.o $(BLD)/index.o $(LDFLAGS) -lstdc++ -o $(BLD)/index.cgi

fileio_trim: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio_trim.cpp -o $(BLD)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/fileio_trim.o -o $(BLD)/fileio_trim

default_test.$(EXE): streamy.o utility.o
	$(CXX) $(CXXFLAGS) $(SRC)/default_test.cpp $(BLD)/streamy.o $(BLD)/utility.o $(LDFLAGS) -o $(BLD)/default_test.$(EXE)

find_tags.cgi: find_tags.o utility.o fileio.o
	$(CXX) $(CXXFLAGS) $(BLD)/find_tags.o $(BLD)/fileio.o $(BLD)/utility.o -o $(BLD)/find_tags.cgi

test_if_sequence.cgi: fileio.o utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.cgi.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.cgi

test_foreach_sequence.cgi: utility.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio_trim.o $(BLD)/utility.o $(SRC)/test_foreach_sequence.o $(LDFLAGS) -o $(BLD)/test_foreach_sequence.cgi

dump_matches.cgi: utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/dump_matches.cpp -o $(BLD)/dump_matches.o
	$(CXX) $(CXXFLAGS) $(BLD)/dump_matches.o $(BLD)/utility.o -o $(BLD)/dump_matches.cgi

# test_sequence.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_sequence.cpp -o $(BLD)/test_sequence.cgi

# test_comment.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_comment.cpp -o $(BLD)/test_comment.cgi

# test_include.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_include.cpp -o $(BLD)/test_include.cgi

# test_get_conf.cgi: utility.o
# 	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_get_conf.cpp -o $(BLD)/test_get_conf.cgi

# test_variable.cgi: streamy.o
# 	$(CXX) $(CXXFLAGS) $(BLD)/utility.o $(SRC)/test_variable.cpp -o $(BLD)/test_variable.cgi

fileio.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o	

find_tags.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/find_tags.cpp -o $(BLD)/find_tags.o

index.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/index.cpp -o $(BLD)/index.o

load_conf.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/load_conf.cpp -o $(BLD)/load_conf.o

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BLD)/utility.o

streamy.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/streamy.cpp -o $(BLD)/streamy.o

.PHONY: upload
upload:
	cp -rf $(BLD)/*.$(EXE) /var/www/html/cgi
	
.PHONY: clean_upload
clean_upload:
	rm $(BLD)/*.$(EXE)
	
.PHONY: clean
clean:
	-rm $(BLD)/*