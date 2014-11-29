#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "tests/test_glversion.h"

namespace FrameworkOneTestSuite {
    CppUnit::Test *suite() {
        CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Framework One Test Cases");

        allTests->addTest(GLVersionComparisonTest::suite());

        return allTests;
    }
};

