#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>

#include "fw1/tests.h"

int main() {
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(FrameworkOneTestSuite::suite());

    runner.run();

    return 0;
}