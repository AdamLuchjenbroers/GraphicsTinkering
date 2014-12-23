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
        void testVectorMultiplication();
        void testTranslation();
        void testScaling();
        void testRotationAroundX();
        void testRotationAroundY();
        void testRotationAroundZ();
        void testCompositeRotation();

        static CppUnit::Test *suite() {
            CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Matrix4 Unit Tests");

            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testConstructors", &Matrix4Tests::testConstructors));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testMatrixMultiplication", &Matrix4Tests::testMatrixMultiplication));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testVectorMultiplication", &Matrix4Tests::testVectorMultiplication));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testTranslation", &Matrix4Tests::testTranslation));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testScaling", &Matrix4Tests::testScaling));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testRotationAroundX", &Matrix4Tests::testRotationAroundX));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testRotationAroundY", &Matrix4Tests::testRotationAroundY));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testRotationAroundZ", &Matrix4Tests::testRotationAroundZ));
            allTests->addTest(new CppUnit::TestCaller<Matrix4Tests>("testCompositeRotation", &Matrix4Tests::testCompositeRotation));

            return allTests;
        }
    private:
        bool matchMatrixToBuffer(const Matrix4 &matrix, const GLfloat *buffer);
};
