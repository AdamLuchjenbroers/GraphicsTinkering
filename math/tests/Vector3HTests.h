#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Vector3H.h"

class Vector3HTests : public CppUnit::TestFixture {
    protected:

    public:
        //void setUp();
        //void tearDown();

        void testConstructors();
        void testMagnitude();
        void testNormalize();
        void testDivision();
        void testMultiplication();
        void testDotProduct();
        void testCrossProduct();

        static CppUnit::Test *suite() {
            CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Vector 4 Unit Tests");

            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testConstructors", &Vector3HTests::testConstructors));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testMagnitude", &Vector3HTests::testMagnitude));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testNormalize", &Vector3HTests::testNormalize));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testDivision", &Vector3HTests::testDivision));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testMultiplication", &Vector3HTests::testMultiplication));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testDotProduct", &Vector3HTests::testDotProduct));
            allTests->addTest(new CppUnit::TestCaller<Vector3HTests>("testCrossProduct", &Vector3HTests::testCrossProduct));

            return allTests;
        }
};
