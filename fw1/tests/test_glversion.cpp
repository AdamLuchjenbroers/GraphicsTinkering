#include "test_glversion.h"

void GLVersionComparisonTest::setUp() {
    four_zero = new GLVersion(4,0);
    four_zero_dup = new GLVersion(4,0);
    four_one = new GLVersion(4,1);
    three_zero = new GLVersion(3,0);
    three_one = new GLVersion(3,1);
};

void GLVersionComparisonTest::tearDown() {
    delete four_zero;
    delete four_zero_dup;
    delete four_one;
    delete three_zero;
    delete three_one;
}

void GLVersionComparisonTest::testLessThan() {
    CPPUNIT_ASSERT ( *four_zero < *four_one );
    CPPUNIT_ASSERT ( *three_one < *four_zero );
    CPPUNIT_ASSERT ( !(*four_one < *four_zero) );
    CPPUNIT_ASSERT ( !(*four_zero < *three_one) );
    CPPUNIT_ASSERT ( !(*four_zero < *four_zero_dup) );
}

void GLVersionComparisonTest::testGreaterThan() {
    CPPUNIT_ASSERT ( *four_one > *four_zero );
    CPPUNIT_ASSERT ( *four_zero > *three_one );
    CPPUNIT_ASSERT ( !(*four_zero > *four_one) );
    CPPUNIT_ASSERT ( !(*three_one > *four_zero) );
    CPPUNIT_ASSERT ( !(*four_zero < *four_zero_dup) );
}

void GLVersionComparisonTest::testEquality() {
    CPPUNIT_ASSERT ( *four_zero == *four_zero_dup );
    CPPUNIT_ASSERT ( !(*four_zero == *three_zero) );
    CPPUNIT_ASSERT ( !(*four_zero == *four_one) );
}

void GLVersionParsingTest::runTest() {
    GLVersion *parsed, *compare;

    compare = new GLVersion(4,1);
    parsed = GLVersion::versionFromText("4.1");

    CPPUNIT_ASSERT(*compare == *parsed);

    delete compare;
    delete parsed;
}
