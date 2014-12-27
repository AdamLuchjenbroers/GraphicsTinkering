#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <SDL2/SDL.h>

#include "TextureRef.h"

class TextureRef;

class Texture {
friend class TextureRef;
public:
    static TextureRef loadBMP(const char *filename);

    bool isLoaded();
private:
    Texture(SDL_Surface &surface);
    ~Texture();

    bool cloneSurface(SDL_Surface &surface);

    int _refCount;
    void *_rawData;
    size_t _rawSize;

    GLenum _GLformat, _GLtype;
    GLuint _GLtexture;
    GLint _GLfmtChannels;
};
