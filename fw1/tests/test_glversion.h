#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../GLVersion.h"

class GLVersionComparisonTest : public CppUnit::TestFixture {
public:
    void setUp();
    void tearDown();

    void testLessThan();
    void testGreaterThan();
    //void testLessThanEqual();
    //void testGreaterThanEqual();
    void testEquality();

    static CppUnit::Test *suite() {
        CppUnit::TestSuite *allTests = new CppUnit::TestSuite("GL Version Comparison Tests");

        allTests->addTest(new CppUnit::TestCaller<GLVersionComparisonTest>("testLessThan", &GLVersionComparisonTest::testLessThan));
        allTests->addTest(new CppUnit::TestCaller<GLVersionComparisonTest>("testGreaterThan", &GLVersionComparisonTest::testGreaterThan));
        allTests->addTest(new CppUnit::TestCaller<GLVersionComparisonTest>("testEquality", &GLVersionComparisonTest::testEquality));

        return allTests;
    }
};

class GLVersionParsingTest : public CppUnit::TestCase {
public:
    void runTest();
};



