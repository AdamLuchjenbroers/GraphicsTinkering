#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <SDL2/SDL.h>

#include "TextureRef.h"
#include "Logger.h"

class TextureRef;

class Texture {
friend class TextureRef;
public:
    /** Loads an OpenGL texture from an image file, mapping it to the requested
      * texture unit
      * @param filename The filename of the image file to load.
      * @param texUnit The texture unit to load this texture to.
      */
    static TextureRef loadImage(const char *filename, GLenum texUnit);
    /** Loads an OpenGL texture from an image file, mapping it to the "default"
      * texture unit (GL_TEXTURE_0).
      * @param filename The filename of the image file to load.
      */
    static TextureRef loadImage(const char *filename);

    bool isLoaded();
private:
    Texture(SDL_Surface &surface, GLenum texUnit);
    ~Texture();

    bool checkGLError(const char *errfmt, Logger::Level loglevel);
    int _refCount;

    bool _loaded;

    GLuint _GLtexture;
};
