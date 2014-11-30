#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "tests/test_glversion.h"
#include "tests/test_glslversion.h"

namespace FrameworkOneTestSuite {
    CppUnit::Test *suite() {
        CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Framework One Test Cases");

        allTests->addTest(GLVersionComparisonTest::suite());
        allTests->addTest(new GLVersionParsingTest());

        allTests->addTest(GLSLVersionComparisonTest::suite());
        allTests->addTest(new GLSLVersionParsingTest());

        return allTests;
    }
};

