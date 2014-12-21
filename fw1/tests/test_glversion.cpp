#include "test_glversion.h"

void GLVersionComparisonTest::setUp() {
};

void GLVersionComparisonTest::tearDown() {
}

void GLVersionComparisonTest::testLessThan() {
    CPPUNIT_ASSERT ( GLVersion(4,0) < GLVersion(4,1) );
    CPPUNIT_ASSERT ( GLVersion(3,1) < GLVersion(4,0) );
    CPPUNIT_ASSERT ( !(GLVersion(4,1) < GLVersion(4,0)) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) < GLVersion(3,1)) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) < GLVersion(4,0)) );
}

void GLVersionComparisonTest::testGreaterThan() {
    CPPUNIT_ASSERT ( GLVersion(4,1) > GLVersion(4,0) );
    CPPUNIT_ASSERT ( GLVersion(4,0) > GLVersion(3,1) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) > GLVersion(4,1)) );
    CPPUNIT_ASSERT ( !(GLVersion(3,1) > GLVersion(4,0)) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) < GLVersion(4,0)) );
}

void GLVersionComparisonTest::testEquality() {
    CPPUNIT_ASSERT ( GLVersion(4,0) == GLVersion(4,0) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) == GLVersion(3,0)) );
    CPPUNIT_ASSERT ( !(GLVersion(4,0) == GLVersion(4,1)) );
}

void GLVersionParsingTest::runTest() {
    char version[4] = "4.1";
    GLVersion parsed = GLVersion::versionFromText(version);

    CPPUNIT_ASSERT(parsed == GLVersion(4,1));
}
