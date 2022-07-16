#ifndef _cgi_web_test_TEST_H
#define _cgi_web_test_TEST_H

#include <cppunit/Test.h> 

class cgi_web_testTest : public CppUnit::TestFixture
{
private:
    CPPUNIT_TEST_SUITE(cgi_web_testTest);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();    

    // agregate test functions
    void execute();
    void execute(int argc, char* argv[]);

protected:
    
private:
    int m_argc;
    char* m_argv[10];
    
};

#endif
