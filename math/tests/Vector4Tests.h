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
        void testMagnitude();

        static CppUnit::Test *suite() {
            CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Vector 4 Unit Tests");

            allTests->addTest(new CppUnit::TestCaller<Vector4Tests>("testConstructors", &Vector4Tests::testConstructors));
            allTests->addTest(new CppUnit::TestCaller<Vector4Tests>("testMagnitude", &Vector4Tests::testMagnitude));

            return allTests;
        }
};
