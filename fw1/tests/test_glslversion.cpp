#include "test_glslversion.h"

void GLSLVersionComparisonTest::setUp() {
    four_zero = new GLSLVersion(4,0);
    four_zero_dup = new GLSLVersion(4,0);
    four_one = new GLSLVersion(4,1);
    three_zero = new GLSLVersion(3,0);
    three_one = new GLSLVersion(3,1);
};

void GLSLVersionComparisonTest::tearDown() {
    delete four_zero;
    delete four_zero_dup;
    delete four_one;
    delete three_zero;
    delete three_one;
}

void GLSLVersionComparisonTest::testLessThan() {
    CPPUNIT_ASSERT ( *four_zero < *four_one );
    CPPUNIT_ASSERT ( *three_one < *four_zero );
    CPPUNIT_ASSERT ( !(*four_one < *four_zero) );
    CPPUNIT_ASSERT ( !(*four_zero < *three_one) );
    CPPUNIT_ASSERT ( !(*four_zero < *four_zero_dup) );
}

void GLSLVersionComparisonTest::testGreaterThan() {
    CPPUNIT_ASSERT ( *four_one > *four_zero );
    CPPUNIT_ASSERT ( *four_zero > *three_one );
    CPPUNIT_ASSERT ( !(*four_zero > *four_one) );
    CPPUNIT_ASSERT ( !(*three_one > *four_zero) );
    CPPUNIT_ASSERT ( !(*four_zero < *four_zero_dup) );
}

void GLSLVersionComparisonTest::testEquality() {
    CPPUNIT_ASSERT ( *four_zero == *four_zero_dup );
    CPPUNIT_ASSERT ( !(*four_zero == *three_zero) );
    CPPUNIT_ASSERT ( !(*four_zero == *four_one) );
}

void GLSLVersionParsingTest::runTest() {
    GLSLVersion *parsed, *compare;
    char version[4] = "4.1";

    compare = new GLSLVersion(4,1);
    parsed = GLSLVersion::versionFromText(version);

    CPPUNIT_ASSERT(*compare == *parsed);

    delete compare;
    delete parsed;
}
