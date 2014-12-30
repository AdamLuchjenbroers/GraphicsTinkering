#include "STLMesh.h"
#include "Logger.h"

#include <cstdlib>
#include <iostream>
#include <fstream>	

struct STLVertex {
    GLfloat vertX, vertY, vertZ;
};

struct STLTriangle {
    GLfloat nrmlX, nrmlY, nrmlZ;
    STLVertex verts[3];
    uint16_t attrib;
};

struct STLHeader {
    char comment[80];
    uint32_t triangles;
};

STLMesh::STLMesh() {
    _meshBuffer = NULL;
}

STLMesh::STLMesh(const char *filename) {
    _meshBuffer = NULL;

    loadSTL(filename);
}


bool STLMesh::loadSTL(const char *filename) {
    std::ifstream stlFile;
    unsigned long index;
    STLHeader header;
    GLfloat *_vertData;

    stlFile.open(filename, std::ios::in | std::ios::binary);
    stlFile.seekg(0, std::ios::beg);
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_MESHES, "Loading Mesh data from STL file %s\n", filename);

    if (stlFile.fail()) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_MESHES, "Failed to open STL file %s\n", filename);
        return false;
    }

    stlFile.read((char *)&header,sizeof(header));
    header.comment[80] = '\0';
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_MESHES, "STL file %s - Header Comments %s\n", filename, header.comment);

    _triangles = header.triangles;
    _vertices = _triangles * 3;
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_MESHES, "STL file %s has %i Triangles (%i Vertices)\n", filename, _triangles, _vertices);

    _meshBuffer = (GLfloat *) malloc( _vertices * stride());
    if (_meshBuffer == NULL) {
        //Not enough free memory.
        return false;
    }
    _vertData = _meshBuffer;

    for(index = 0; index < _triangles; index++) {
        STLTriangle tri;

        // Manually specify length of buffer, because byte alignment keeps 
        // adding an extra 2 bytes of padding and breaking the load.
        stlFile.read((char *)&tri, 50);

        for(int vert=0; vert < 3; vert++) {

            _vertData[0] = tri.verts[vert].vertX;
            _vertData[1] = tri.verts[vert].vertY;
            _vertData[2] = tri.verts[vert].vertZ;
            _vertData[3] = 1.0f;
            _vertData[4] = tri.nrmlX;
            _vertData[5] = tri.nrmlY;
            _vertData[6] = tri.nrmlZ;
            _vertData[7] = 0.0f;

            _vertData += 8;
        }
    }
}
