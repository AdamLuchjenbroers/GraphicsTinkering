#include <cppunit/TestSuite.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/ui/text/TestRunner.h>

#include "fw1/tests.h"
#include "math/tests.h"

int main() {
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestResult controller;
    CppUnit::TestResultCollector collector;
    CppUnit::BriefTestProgressListener progress;

    controller.addListener(&collector);
    controller.addListener(&progress);

    runner.addTest(FrameworkOneTestSuite::suite());
    runner.addTest(MathTestSuite::suite());

    runner.run(controller);

    return 0;
}
