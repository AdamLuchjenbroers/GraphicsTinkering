#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../GLSLVersion.h"

class GLSLVersionComparisonTest : public CppUnit::TestFixture {
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

            allTests->addTest(new CppUnit::TestCaller<GLSLVersionComparisonTest>("testLessThan", &GLSLVersionComparisonTest::testLessThan));
            allTests->addTest(new CppUnit::TestCaller<GLSLVersionComparisonTest>("testGreaterThan", &GLSLVersionComparisonTest::testGreaterThan));
            allTests->addTest(new CppUnit::TestCaller<GLSLVersionComparisonTest>("testEquality", &GLSLVersionComparisonTest::testEquality));

            return allTests;
        }
};

class GLSLVersionParsingTest : public CppUnit::TestCase {
public:
    void runTest();
};



