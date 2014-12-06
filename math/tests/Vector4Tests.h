#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Vector4.h"

class Vector4Tests : public CppUnit::TestFixture {
    protected:

    public:
        //void setUp();
        //void tearDown();

        void testConstructors();

        //void testLessThan();
        //void testGreaterThan();
        //void testLessThanEqual();
        //void testGreaterThanEqual();
        //void testEquality();

        static CppUnit::Test *suite() {
            CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Vector 4 Unit Tests");

            allTests->addTest(new CppUnit::TestCaller<Vector4Tests>("testConstructors", &Vector4Tests::testConstructors));

            return allTests;
        }
};
