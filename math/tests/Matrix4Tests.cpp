#include "Matrix4Tests.h"

#include <math.h>

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

    GLfloat buffer[] = {
         1.0f,  2.0f,  3.0f,  4.0f,
         5.0f,  6.0f,  7.0f,  8.0f,
         9.0f, 10.0f, 11.0f, 12.0f,
        13.0f, 14.0f, 15.0f, 16.0f
    };

    Matrix4 fromBuf = Matrix4(buffer);
    matchMatrixToBuffer(fromBuf,buffer);
}

bool Matrix4Tests::matchMatrixToBuffer(const Matrix4 &matrix, const GLfloat *buffer) {
    int i,j;

    for (i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            CPPUNIT_ASSERT(matrix.at(i,j) == buffer[(j*4)+i]);
        }
    }
    return true;
}

void Matrix4Tests::testMatrixMultiplication() {
    GLfloat dataA[] = {
            1.0f, 2.0f, 1.0f, 3.0f
          , 2.0f, 1.0f, 0.0f, 1.0f
          , 4.0f, 2.0f, 1.0f, 2.0f
          , 1.0f, 2.0f, 1.0f, 2.0f
    };
    GLfloat dataB[] = {
            1.0f, 1.0f, 1.0f, 2.0f
          , 1.0f, 2.0f, 1.0f, 1.0f
          , 2.0f, 1.0f, 1.0f, 1.0f
          , 1.0f, 1.0f, 2.0f, 1.0f
    };
    GLfloat result[] = {
             9.0f,  9.0f,  4.0f, 10.0f
          , 10.0f,  8.0f,  3.0f,  9.0f
          ,  9.0f,  9.0f,  4.0f, 11.0f
          , 12.0f,  9.0f,  4.0f, 10.0f
    };

    Matrix4 matA = Matrix4(dataA);
    Matrix4 matB = Matrix4(dataB);
    Matrix4 matResult = matA * matB;

    matchMatrixToBuffer(matResult, result);

    Matrix4 identity = Matrix4();
    Matrix4 testId = matA * identity;

    CPPUNIT_ASSERT(testId == matA);
}

void Matrix4Tests::testVectorMultiplication() {
    Vector3H vec = Vector3H(2.0f, 3.0f, 4.0f, 1.0f);

    GLfloat matData[] = {
            1.0f, 0.0f, 1.0f, 3.0f
          , 2.0f, 1.0f, 0.0f, 1.0f
          , 1.0f, 2.0f, 1.0f, 2.0f
          , 1.0f, 2.0f, 1.0f, 1.0f
    };
    Matrix4 mat = Matrix4(matData);

    Vector3H result = mat * vec;
    Vector3H expected = Vector3H(13.0f, 13.0f, 7.0f, 18.0f);

    CPPUNIT_ASSERT(result == expected);

    Matrix4 identity = Matrix4();
    Vector3H testId = identity * vec;

    CPPUNIT_ASSERT(vec == testId);
}

void Matrix4Tests::testTranslation() {
    Vector3H start = Vector3H(1.0f, 1.0f, 1.0f, 1.0f);
    Matrix4 translate = Matrix4::translate(2.0f, 3.0f, -1.5f);

    Vector3H finish = translate * start;
    Vector3H expected = Vector3H(3.0f, 4.0f, -0.5f, 1.0f);

    CPPUNIT_ASSERT (finish == expected);
}

void Matrix4Tests::testScaling() {
    Vector3H start = Vector3H(1.0f, 1.0f, 1.0f, 1.0f);

    Matrix4 uniformScale = Matrix4::scale(2.0f);
    Vector3H uniformResult = uniformScale * start;
    Vector3H uniformExpect = Vector3H(2.0f, 2.0f, 2.0f, 1.0f);

    CPPUNIT_ASSERT ( uniformResult == uniformExpect );

    Matrix4 variedScale = Matrix4::scale(2.0f, 3.0f, 5.0f);
    Vector3H variedResult = variedScale * start;
    Vector3H variedExpect = Vector3H(2.0f, 3.0f, 5.0f, 1.0f);

    CPPUNIT_ASSERT ( variedResult == variedExpect );
}

void Matrix4Tests::testRotationAroundX() {
    Vector3H basic = Vector3H(1.0f, 1.0f, 1.0f, 1.0f);
    Vector3H result;
    Matrix4 rotate;

    rotate = Matrix4::rotate(180.0f, 0.0f, 0.0f);
    result = rotate * basic;
    std::cout << "\nX Result:\n" << result.printable();
    CPPUNIT_ASSERT (result == Vector3H(1.0f, -1.0f, -1.0f, 1.0f));

    GLfloat rad = (60.0f * M_PI) / 180.0f;
    GLfloat expectData[] = { 1.0f,      0.0f,      0.0f, 0.0f
                           , 0.0f,  cos(rad), -sin(rad), 0.0f
                           , 0.0f,  sin(rad),  cos(rad), 0.0f
                           , 0.0f,      0.0f,      0.0f, 1.0f};
    Matrix4 expect = Matrix4(expectData);
    
    rotate = Matrix4::rotate(60.0f, 0.0f, 0.0f);

    CPPUNIT_ASSERT ( rotate == expect );
}

void Matrix4Tests::testRotationAroundY() {
    Vector3H basic = Vector3H(1.0f, 1.0f, 1.0f, 1.0f);
    Vector3H result;
    Matrix4 rotate;

    rotate = Matrix4::rotate(0.0f, 180.0f, 0.0f);
    result = rotate * basic;
    CPPUNIT_ASSERT (result == Vector3H(-1.0f, 1.0f, -1.0f, 1.0f));

    GLfloat rad = (60.0f * M_PI) / 180.0f;
    GLfloat expectData[] = {  cos(rad), 0.0f,  sin(rad), 0.0f
                           ,      0.0f, 1.0f,      0.0f, 0.0f
                           , -sin(rad), 0.0f,  cos(rad), 0.0f
                           ,      0.0f, 0.0f,      0.0f, 1.0f};
    Matrix4 expect = Matrix4(expectData);
    
    rotate = Matrix4::rotate(0.0f, 60.0f, 0.0f);

    CPPUNIT_ASSERT ( rotate == expect );
}

void Matrix4Tests::testRotationAroundZ() {
    Vector3H basic = Vector3H(1.0f, 1.0f, 1.0f, 1.0f);
    Vector3H result;
    Matrix4 rotate;

    rotate = Matrix4::rotate(0.0f, 0.0f, 180.0f);
    result = rotate * basic;
    CPPUNIT_ASSERT (result == Vector3H(-1.0f, -1.0f, 1.0f, 1.0f));

    GLfloat rad = (60.0f * M_PI) / 180.0f;
    GLfloat expectData[] = { 1.0f,      0.0f,      0.0f, 0.0f
                           , 0.0f,  cos(rad), -sin(rad), 0.0f
                           , 0.0f,  sin(rad),  cos(rad), 0.0f
                           , 0.0f,      0.0f,      0.0f, 1.0f};
    Matrix4 expect = Matrix4(expectData);
    
    rotate = Matrix4::rotate(60.0f, 0.0f, 0.0f);

    CPPUNIT_ASSERT ( rotate == expect );
}

void Matrix4Tests::testCompositeRotation() {
    Matrix4 combined = Matrix4::rotate(45.0f, 60.0f, 120.0f);
    Matrix4 x = Matrix4::rotate(45.0f, 0.0f, 0.0f);
    Matrix4 y = Matrix4::rotate(0.0f, 60.0f, 0.0f);
    Matrix4 z = Matrix4::rotate(0.0f, 0.0f, 120.0f);
    Matrix4 matResult = z * y * x;

    std::cout << "\nComposite expected:\n" << matResult.printable() << "\nActual:\n" << combined.printable();
    CPPUNIT_ASSERT ( matResult == combined );
}
