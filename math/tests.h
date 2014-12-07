#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "tests/Vector3HTests.h"
#include "tests/Matrix4Tests.h"

namespace MathTestSuite {
    CppUnit::Test *suite() {
        CppUnit::TestSuite *allTests = new CppUnit::TestSuite("Maths Test Cases");

        allTests->addTest(Vector3HTests::suite());
        allTests->addTest(Matrix4Tests::suite());

        return allTests;
    }
};

