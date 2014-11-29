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
