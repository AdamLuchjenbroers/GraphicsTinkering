#include "Matrix4Tests.h"

#include <math.h>
#define PI 3.14159265

#include <cstdio>

void Matrix4Tests::testConstructors() {

    Matrix4 identity = Matrix4();

    CPPUNIT_ASSERT(identity.at(0,0) == 1.0f);
    CPPUNIT_ASSERT(identity.at(1,1) == 1.0f);
    CPPUNIT_ASSERT(identity.at(2,2) == 1.0f);
    CPPUNIT_ASSERT(identity.at(3,3) == 1.0f);

    CPPUNIT_ASSERT(identity.at(0,1) == 0.0f);
    CPPUNIT_ASSERT(identity.at(2,0) == 0.0f);
    CPPUNIT_ASSERT(identity.at(3,1) == 0.0f);
    CPPUNIT_ASSERT(identity.at(2,3) == 0.0f);
}
