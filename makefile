# License:    None
# Author:     Brian K Preston
# File Name:  no file name
# Build Date: Thu Apr 11 08:56:43 AM CDT 2024
# Version:    3.6.7

CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -DDEBUG
CXXEXTRA = -Wshadow -fstats -fno-rtti
##CXXFLAGS = -g -Wall -std=c++17 -DDEBUG --sys-root=~/src -Wshadow -02
#LDFLAGS = -lcgicc -lcppunit -L/usr/local/lib/
LDFLAGS = -lcgicc -L/usr/local/lib/
INCLUDES = -I/usr/include/cgicc/
EXT = cpp
SRC = src
BLD = build
OBJ = build
TST = test

all: $(BLD)/lex $(BLD)/index.cgi $(BLD)/cgi_test_script.cgi $(BLD)/fileio_trim $(BLD)/find_tags $(BLD)/dump_matches $(BLD)/load_conf \
	$(BLD)/test_sequence $(BLD)/test_include $(BLD)/test_comment $(BLD)/test_get_conf $(BLD)/test_variable $(BLD)/test_if_sequence $(BLD)/test_foreach_sequence \
	# $(BLD)/default_test.cgi

$(BLD)/lex: $(OBJ)/fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/lex.cpp -o $(OBJ)/lex.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ)/fileio.o $(OBJ)/lex.o -o $(BLD)/lex

$(BLD)/index.cgi: $(OBJ)/fileio.o $(OBJ)/utility.o $(OBJ)/streamy.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(OBJ)/streamy.o $(SRC)/index.cpp -lcgicc -o $(BLD)/index.cgi

$(BLD)/default_test.cgi: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o -I/usr/local/includes -lstreamy $(SRC)/default_test.cpp $(LDFLAGS) -o $(BLD)/default_test.cgi

$(BLD)/cgi_test_script.cgi: $(SRC)/cgi_test_script.cpp
	$(CXX) $(CXXFLAGS) $(SRC)/cgi_test_script.cpp -o $(BLD)/cgi_test_script.cgi

$(BLD)/fileio_trim: $(OBJ)/fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio_trim.cpp -o $(BLD)/fileio_trim.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/fileio_trim.o -o $(BLD)/fileio_trim

$(BLD)/find_tags: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/find_tags.cpp  -o $(BLD)/find_tags

$(BLD)/dump_matches: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/dump_matches.cpp -o $(BLD)/dump_matches

$(BLD)/load_conf: $(OBJ)/fileio.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(SRC)/load_conf.cpp -o $(BLD)/load_conf

$(BLD)/test_sequence: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/test_sequence.cpp -o $(BLD)/test_sequence

$(BLD)/test_comment: $(OBJ)/fileio.o $(OBJ)/utility.o $(BLD)/streamy.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(OBJ)/streamy.o $(SRC)/test_comment.cpp -o $(BLD)/test_comment

$(BLD)/test_include: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/test_include.cpp -o $(BLD)/test_include

$(BLD)/test_get_conf: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/test_get_conf.cpp -o $(BLD)/test_get_conf

$(BLD)/test_variable: $(OBJ)/fileio.o $(OBJ)/utility.o $(OBJ)/streamy.o
	$(CXX) $(CXXFLAGS) $(OBJ)/fileio.o $(OBJ)/utility.o $(OBJ)/streamy.o $(SRC)/test_variable.cpp -o $(BLD)/test_variable

$(BLD)/test_if_sequence: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence

$(BLD)/test_foreach_sequence: $(OBJ)/fileio.o $(OBJ)/utility.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJ)/fileio.o $(OBJ)/utility.o $(SRC)/test_foreach_sequence.cpp $(LDFLAGS) -o $(BLD)/test_foreach_sequence

$(OBJ)/fileio.o: $(SRC)/fileio.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o

$(OBJ)/utility.o: $(SRC)/utility.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BLD)/utility.o

$(OBJ)/streamy.o: $(SRC)/streamy.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/streamy.cpp -o $(BLD)/streamy.o

$(BLD)/unit_test: unit_test.o 000-CatchMain.o
	$(CXX) $(CXXFLAGS) $(OBJ)/unit_test.o $(OBJ)/000-CatchMain.o $(OBJ)/utility.o -o $(BLD)/unit_test

$(OBJ)/unit_test.o: $(SRC)/unit_test.cpp
	$(CXX) $(CXXFLAGS) -lcppunit -I/usr/local/include/cppunit -c $(SRC)/unit_test.cpp -o $(BLD)/unit_test.o

$(BLD)/000-CatchMain.o: $(SRC)/000-CatchMain.cpp
	$(CXX) $(CXXFLAGS) -c $(SRC)/000-CatchMain.cpp -o $(BLD)/000-CatchMain.o

.PHONY: upload_test
upload_test:
	-cp -f $(BLD)/*.cgi $(TST)/www

.PHONY: upload
upload:
	@echo uploading ...
	# alpha only!
	# cp -rf $(BLD)/*.cgi /var/www/cgi-bin
	# sftp 192.168.0.6 # todo
	# echo "lorem ipsum" > foobar.txt
	# curl -T foobar.txt -k sftp://127.0.0.1/~/Downloads/

	# scp $(BLD)/cgi_test_script.cgi brian@1alpha:/vaw/www/html
	@echo uploading complete.

.PHONY: clean_upload
clean_upload:
	@echo cleaning upload ...
	#-rm $(BLD)/index.cgi
	@echo complete.

.PHONY: clean
clean:
	-rm -rf $(BLD)/*
	-rm -f $(TST)/www/*.cgi