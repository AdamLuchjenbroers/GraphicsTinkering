#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#include "../Matrix4.h"

class Matrix4Tests : public CppUnit::TestFixture {
    protected:

    public:
        //void setUp();
        //void tearDown();

        void testConstructors();
        void testMatrixMultiplication();

        static CppUnit::Test *suite() {
            CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Matrix4 Unit Tests");

            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testConstructors", &Matrix4Tests::testConstructors));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testMatrixMultiplication", &Matrix4Tests::testMatrixMultiplication));

            return allTests;
        }
    private:
        bool matchMatrixToBuffer(const Matrix4 &matrix, const GLfloat *buffer);
};
