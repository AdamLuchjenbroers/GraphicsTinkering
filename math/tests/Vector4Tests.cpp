#include "Vector4Tests.h"

void Vector4Tests::testConstructors() {

    Vector4 blank = Vector4();
    CPPUNIT_ASSERT ( blank[0] == 0.0f );
    CPPUNIT_ASSERT ( blank[1] == 0.0f );
    CPPUNIT_ASSERT ( blank[2] == 0.0f );
    CPPUNIT_ASSERT ( blank[3] == 0.0f );

    Vector4 xyzw = Vector4(1.0f, 2.0f, 3.0f, 4.0f);
    CPPUNIT_ASSERT ( xyzw[0] == 1.0f );
    CPPUNIT_ASSERT ( xyzw[1] == 2.0f );
    CPPUNIT_ASSERT ( xyzw[2] == 3.0f );
    CPPUNIT_ASSERT ( xyzw[3] == 4.0f );

    GLfloat data[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
    Vector4 array = Vector4(data);
    for(int i = 0; i < 4; i++) {
        CPPUNIT_ASSERT ( array[i] == data[i] );
    }
}

void Vector4Tests::testMagnitude() {

    Vector4 oneAxis = Vector4(8.0f, 0.0f, 0.0f, 1.0f);
    CPPUNIT_ASSERT ( oneAxis.magnitude() == 8.0f);

    Vector4 twoAxis = Vector4(4.0f, 3.0f, 0.0f, 1.0f);
    CPPUNIT_ASSERT ( twoAxis.magnitude() == 5.0f);

    Vector4 threeAxis = Vector4(4.0f, 4.0f, 2.0f, 1.0f);
    CPPUNIT_ASSERT ( threeAxis.magnitude() == 6.0f);
}


void Vector4Tests::testNormalize() {

    Vector4 oneAxis = Vector4(8.0f, 0.0f, 0.0f, 1.0f);
    oneAxis.normalize();
    CPPUNIT_ASSERT ( oneAxis.magnitude() == 1.0f);

    Vector4 twoAxis = Vector4(4.0f, 3.0f, 0.0f, 1.0f);
    twoAxis.normalize();
    CPPUNIT_ASSERT ( twoAxis.magnitude() == 1.0f);

    Vector4 threeAxis = Vector4(4.0f, 4.0f, 2.0f, 1.0f);
    threeAxis.normalize();
    CPPUNIT_ASSERT ( threeAxis.magnitude() == 1.0f);
}

void Vector4Tests::testDivision() {
    Vector4 base = Vector4(6.0f, 12.0f, 18.0f, 1.0f);
    Vector4 div = base / 3.0f;

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


void Vector4Tests::testMultiplication() {
    Vector4 base = Vector4(1.0f, 2.0f, 3.0f, 1.0f);
    Vector4 div = base * 2.0f;

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
