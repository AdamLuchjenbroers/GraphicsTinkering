#pragma once

#define GL_GLEXT_PROTOTYPES
#include <GL/glcorearb.h>

#include <cstdlib>

/** Interface definition for mesh objects 
    @brief Interface definition for mesh objects
*/
class MeshFile {
public:
    virtual ~MeshFile();
    
    /** Does this Mesh include a vertex buffer 
    @return True if this Mesh includes a vertex buffer
    */
    virtual bool hasVertex() { return true; }
    /** What is the offset to the vertex data for this mesh? 
    @return The offset to the vertex buffer for this mesh
    */
    virtual void *offsetVertex() {return 0; };

    /** Does this Mesh include a normal buffer 
    @return True if this Mesh includes a normal buffer
    */
    virtual bool hasNormal() { return false; };
    /** What is the offset to the normal data for this mesh? 
    @return The offset to the normal buffer for this mesh
    */
    virtual void *offsetNormal() {return 0;};
    /** Does this Mesh include a texture UV coordinates buffer 
    @return True if this Mesh includes a texture UV coordinates buffer
    */
    virtual bool hasTexUV() { return false; };
    /** What is the offset to the texture UV coordinates data for this mesh? 
    @return The offset to the texture UV coordinates buffer for this mesh
    */
    virtual void *offsetTexUV() {return 0;};
    /** Does this Mesh include a surface tangent buffer 
    @return True if this Mesh includes a surface tangent buffer
    */
    virtual bool hasTangent() { return false; };
    /** What is the offset to the surface tangent data for this mesh? 
    @return The offset to the surface tangent buffer for this mesh
    */
    virtual void *offsetTangent() {return 0;};

    /** Load the mesh buffer into a Vertex Array Object 
    @param vertArray The OpenGL ArrayID of the buffer to load
    @return True if the buffer was successfully loaded
    */
    virtual bool loadBuffer(GLuint vertArray);
    /** What is the size in bytes of the mesh data buffer.
    @return The size in bytes of the mesh data buffer.
    */
    virtual size_t meshDataSize() { return _vertices * stride(); };

    /** Map an attribute in the currently bound Vertex Array Object
    @param attribute OpenGL Attribute ID to map to
    @param components Number of components per record
    @param offset Memory offset to the first record in the VAO
    @return True if the attribute was successfully mapped
    */
    virtual bool mapAttribute(GLuint attribute, int components, void *offset);
    /** Map the Vertices to the provided OpenGL Attribute
    @param attribute OpenGL Attribute ID to map to
    @return True if the attribute was successfully mapped
    */
    virtual bool mapVertices(GLuint attribute);
    /** Map the Normals to the provided OpenGL Attribute
    @param attribute OpenGL Attribute ID to map to
    @return True if the attribute was successfully mapped
    */
    virtual bool mapNormals(GLuint attribute);
    /** Map the UV Texture Coordinates to the provided OpenGL Attribute
    @param attribute OpenGL Attribute ID to map to
    @return True if the attribute was successfully mapped
    */
    virtual bool mapTexUV(GLuint attribute);
    /** Map the Tangents to the provided OpenGL Attribute
    @param attribute OpenGL Attribute ID to map to
    @return True if the attribute was successfully mapped
    */
    virtual bool mapTangents(GLuint attribute);

    /** Get the OpenGL Stride Length for the mesh buffer 
    @return the OpenGL Stride Length for the mesh buffer 
    */
    virtual size_t stride() = 0; 
    
    /** Get the number of vertices in this mesh
    @return the number of vertices in this mesh
    */
    virtual unsigned long numVertices() { return _vertices; };
protected:
    GLfloat *_meshBuffer;

    unsigned long _triangles;
    unsigned long _vertices;

    GLuint _glError;
    GLuint _bufferID;

};
