# cgi_web
# Mon Oct 30 09:11:47 AM CDT 2023
# Mon Oct 30 11:55:47 AM CDT 2023
# Wed Nov  1 09:13:23 AM CDT 2023
# Fri Nov 10 01:42:29 PM CST 2023
# Wed Nov 15 06:43:33 AM CST 2023

CXX = g++
CXXFLAGS = -g -Wall -std=c++17 -DDEBUG
LDFLAGS = -lcgicc -lcppunit -L/usr/local/lib/
INCLUDES = -I/usr/include/cgicc/
EXT = cpp
SRC = src
BLD = build
OBJ = build
TST = test

all: lex index.cgi default_test.cgi cgi_test_script.cgi fileio_trim find_tags dump_matches load_conf \
	test_sequence test_comment test_include test_get_conf test_variable test_if_sequence test_foreach_sequence \
	#000-CatchMain.o


lex: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/lex.cpp -o $(BLD)/lex.o	
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio.o $(BLD)/lex.o -o $(BLD)/lex
	
index.cgi: fileio.o utility.o streamy.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/index.cpp -lcgicc -o $(BLD)/index.cgi

default_test.cgi: fileio.o utility.o streamy.o 
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o -lstreamy $(SRC)/default_test.cpp $(LDFLAGS) -o $(BLD)/default_test.cgi

cgi_test_script.cgi:
	$(CXX) $(CXXFLAGS) $(SRC)/cgi_test_script.cpp -o $(BLD)/cgi_test_script.cgi	

fileio_trim: fileio.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio_trim.cpp -o $(BLD)/fileio_trim.o	
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/fileio_trim.o -o $(BLD)/fileio_trim

find_tags: fileio.o utility.o 
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/find_tags.cpp  -o $(BLD)/find_tags

dump_matches: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/dump_matches.cpp -o $(BLD)/dump_matches

load_conf: fileio.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(SRC)/load_conf.cpp -o $(BLD)/load_conf

test_sequence: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_sequence.cpp -o $(BLD)/test_sequence

test_comment: fileio.o utility.o streamy.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/test_comment.cpp -o $(BLD)/test_comment

test_include: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_include.cpp -o $(BLD)/test_include

test_get_conf: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_get_conf.cpp -o $(BLD)/test_get_conf

test_variable: fileio.o utility.o streamy.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(BLD)/streamy.o $(SRC)/test_variable.cpp -o $(BLD)/test_variable

test_if_sequence: fileio.o utility.o
	$(CXX) $(CXXFLAGS) -c $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence.o
	$(CXX) $(CXXFLAGS) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_if_sequence.cpp -o $(BLD)/test_if_sequence

test_foreach_sequence: fileio.o utility.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(BLD)/fileio.o $(BLD)/utility.o $(SRC)/test_foreach_sequence.cpp $(LDFLAGS) -o $(BLD)/test_foreach_sequence

fileio.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/fileio.cpp -o $(BLD)/fileio.o	

utility.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/utility.cpp -o $(BLD)/utility.o

streamy.o:
	$(CXX) $(CXXFLAGS) -c $(SRC)/streamy.cpp -o $(BLD)/streamy.o

unit_test: unit_test.o 000-CatchMain.o 
	$(CXX) $(CXXFLAGS) $(BLD)/unit_test.o $(BUILD)/000-CatchMain.o $(BLD)/utility.o -o $(BLD)/unit_test

unit_test.o:
	$(CXX) $(CXXFLAGS) -lcppunit -I/usr/local/include/cppunit -c $(SRC)/unit_test.cpp -o $(BLD)/unit_test.o

000-CatchMain.o:
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