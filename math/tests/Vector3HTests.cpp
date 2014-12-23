#include "Vector3HTests.h"

#include <math.h>

void Vector3HTests::testConstructors() {

    Vector3H blank = Vector3H();
    CPPUNIT_ASSERT ( blank[0] == 0.0f );
    CPPUNIT_ASSERT ( blank[1] == 0.0f );
    CPPUNIT_ASSERT ( blank[2] == 0.0f );
    CPPUNIT_ASSERT ( blank[3] == 0.0f );

    Vector3H xyzw = Vector3H(1.0f, 2.0f, 3.0f, 4.0f);
    CPPUNIT_ASSERT ( xyzw[0] == 1.0f );
    CPPUNIT_ASSERT ( xyzw[1] == 2.0f );
    CPPUNIT_ASSERT ( xyzw[2] == 3.0f );
    CPPUNIT_ASSERT ( xyzw[3] == 4.0f );

    GLfloat data[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vector3H array = Vector3H(data);
    for(int i = 0; i < 4; i++) {
        CPPUNIT_ASSERT ( array[i] == data[i] );
    }
}

void Vector3HTests::testMagnitude() {

    Vector3H oneAxis = Vector3H(8.0f, 0.0f, 0.0f, 1.0f);
    CPPUNIT_ASSERT ( oneAxis.magnitude() == 8.0f);

    Vector3H twoAxis = Vector3H(4.0f, 3.0f, 0.0f, 1.0f);
    CPPUNIT_ASSERT ( twoAxis.magnitude() == 5.0f);

    Vector3H threeAxis = Vector3H(4.0f, 4.0f, 2.0f, 1.0f);
    CPPUNIT_ASSERT ( threeAxis.magnitude() == 6.0f);
}


void Vector3HTests::testNormalize() {

    Vector3H oneAxis = Vector3H(8.0f, 0.0f, 0.0f, 1.0f);
    oneAxis.normalize();
    CPPUNIT_ASSERT ( oneAxis.magnitude() == 1.0f);

    Vector3H twoAxis = Vector3H(4.0f, 3.0f, 0.0f, 1.0f);
    twoAxis.normalize();
    CPPUNIT_ASSERT ( twoAxis.magnitude() == 1.0f);

    Vector3H threeAxis = Vector3H(4.0f, 4.0f, 2.0f, 1.0f);
    threeAxis.normalize();
    CPPUNIT_ASSERT ( threeAxis.magnitude() == 1.0f);
}

void Vector3HTests::testDivision() {
    Vector3H base = Vector3H(6.0f, 12.0f, 18.0f, 1.0f);
    Vector3H div = base / 3.0f;

    CPPUNIT_ASSERT ( div[0] == 2.0f );
    CPPUNIT_ASSERT ( div[1] == 4.0f );
    CPPUNIT_ASSERT ( div[2] == 6.0f );
    CPPUNIT_ASSERT ( div[3] == 1.0f );

    base /= 2.0f;

    CPPUNIT_ASSERT ( base[0] == 3.0f );
    CPPUNIT_ASSERT ( base[1] == 6.0f );
    CPPUNIT_ASSERT ( base[2] == 9.0f );
    CPPUNIT_ASSERT ( base[3] == 1.0f );
}


void Vector3HTests::testMultiplication() {
    Vector3H base = Vector3H(1.0f, 2.0f, 3.0f, 1.0f);
    Vector3H div = base * 2.0f;

    CPPUNIT_ASSERT ( div[0] == 2.0f );
    CPPUNIT_ASSERT ( div[1] == 4.0f );
    CPPUNIT_ASSERT ( div[2] == 6.0f );
    CPPUNIT_ASSERT ( div[3] == 1.0f );

    base *= 3.0f;

    CPPUNIT_ASSERT ( base[0] == 3.0f );
    CPPUNIT_ASSERT ( base[1] == 6.0f );
    CPPUNIT_ASSERT ( base[2] == 9.0f );
    CPPUNIT_ASSERT ( base[3] == 1.0f );
}

void Vector3HTests::testDotProduct() {
    Vector3H base = Vector3H(1.0f, 0.0f, 0.0f, 0.0f);
    Vector3H perpendicular = Vector3H(0.0f, 1.0f, 0.0f, 0.0f);
    Vector3H angle = Vector3H(1.0f, 1.0f, 0.0f, 0.0f);

    angle.normalize();

    CPPUNIT_ASSERT ( base.dot(base) == 1.0f);
    CPPUNIT_ASSERT ( base.dot(perpendicular) == 0.0f);

    GLfloat cos45 = cos(M_PI/4);
    CPPUNIT_ASSERT_DOUBLES_EQUAL ( base.dot(angle), cos45, 0.0000001f);
}

void Vector3HTests::testCrossProduct() {
    Vector3H a = Vector3H(1.0f, 2.0f, 1.0f, 1.0f);
    Vector3H b = Vector3H(4.0f, 1.0f, 3.0f, 1.0f);

    Vector3H cross = a.cross(b);

    //This vector should be perpendicular to both source vectors.
    CPPUNIT_ASSERT(cross.dot(a) == 0.0f);
    CPPUNIT_ASSERT(cross.dot(b) == 0.0f);

}
