#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "tests/Vector4Tests.h"

namespace MathTestSuite {
    CppUnit::Test *suite() {
        CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Maths Test Cases");

        allTests->addTest(Vector4Tests::suite());

        return allTests;
    }
};

