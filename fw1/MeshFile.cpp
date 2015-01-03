#include "MeshFile.h"
#include "../fw1/Logger.h"

MeshFile::~MeshFile() {
    if (_meshBuffer != NULL) {
        free(_meshBuffer);
    }    
}

bool MeshFile::loadBuffer(GLuint vertArray) {
    if (_meshBuffer == NULL) {
        return false;
    }   
 
    glBindVertexArray(vertArray);

    glGenBuffers(1, &_bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

    glBufferData(GL_ARRAY_BUFFER, meshDataSize(), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, meshDataSize(), _meshBuffer);
}

bool MeshFile::mapAttribute(GLuint attribute, int component, void *offset) {
    glBindBuffer(GL_ARRAY_BUFFER, _bufferID);

    glVertexAttribPointer(attribute, component, GL_FLOAT, GL_FALSE, stride(), offset);
    glEnableVertexAttribArray(attribute);

    _glError = glGetError();
    return (_glError == GL_NO_ERROR);
}

bool MeshFile::mapVertices(GLuint attribute) {
    return mapAttribute(attribute, 4, offsetVertex());
}

bool MeshFile::mapNormals(GLuint attribute) {
    if ( hasNormal() ) {
        return mapAttribute(attribute, 4, offsetNormal());
    } else {
        return false;
    }
}

bool MeshFile::mapTangents(GLuint attribute) {
    if ( hasTangent() ) {
        return mapAttribute(attribute, 4, offsetTangent());
    } else {
        return false;
    }
}

bool MeshFile::mapTexUV(GLuint attribute) {
    if ( hasTexUV() ) {
        return mapAttribute(attribute, 2, offsetTexUV());
    } else {
        return false;
    }
}
