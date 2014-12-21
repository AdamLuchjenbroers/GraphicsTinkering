#include "test_glslversion.h"

void GLSLVersionComparisonTest::setUp() {
};

void GLSLVersionComparisonTest::tearDown() {
}

void GLSLVersionComparisonTest::testLessThan() {
	CPPUNIT_ASSERT ( GLSLVersion(4,0) < GLSLVersion(4,1) );
	CPPUNIT_ASSERT ( GLSLVersion(3,1) < GLSLVersion(4,0) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,1) < GLSLVersion(4,0)) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) < GLSLVersion(3,1)) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) < GLSLVersion(4,0)) );
}

void GLSLVersionComparisonTest::testGreaterThan() {
	CPPUNIT_ASSERT ( GLSLVersion(4,1) > GLSLVersion(4,0) );
	CPPUNIT_ASSERT ( GLSLVersion(4,0) > GLSLVersion(3,1) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) > GLSLVersion(4,1)) );
	CPPUNIT_ASSERT ( !(GLSLVersion(3,1) > GLSLVersion(4,0)) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) < GLSLVersion(4,0)) );
}

void GLSLVersionComparisonTest::testEquality() {
	CPPUNIT_ASSERT ( GLSLVersion(4,0) == GLSLVersion(4,0) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) == GLSLVersion(3,0)) );
	CPPUNIT_ASSERT ( !(GLSLVersion(4,0) == GLSLVersion(4,1)) );
}

void GLSLVersionParsingTest::runTest() {
    char version[4] = "4.1";
    GLSLVersion parsed = GLSLVersion::versionFromText(version);

    CPPUNIT_ASSERT(parsed == GLSLVersion(4,1));
}
