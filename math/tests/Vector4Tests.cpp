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
