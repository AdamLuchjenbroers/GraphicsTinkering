#include "Texture.h"
#include "Logger.h"

#include <cstring>
#include <cstdlib>

#include <SDL2/SDL_image.h>
#include <GL/glu.h>

TextureRef Texture::loadBMP(const char *filename) {
    SDL_Surface *bitmap = IMG_Load(filename);
 
    if (bitmap == NULL) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_TEXTURES, "Failed loading BMP texture from file %s - Error: %s\n", filename, SDL_GetError());
        return TextureRef();
    }

    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_TEXTURES, "Successfully loaded BMP texture from file %s\n", filename);
    Texture *texture = new Texture(*bitmap);
    SDL_FreeSurface(bitmap);

    return TextureRef(*texture);
}

Texture::Texture(SDL_Surface &surface) {
    _refCount = 0;

    glGenTextures(1, &_GLtexture);
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_TEXTURES, "Texture loaded to name: %i\n", _GLtexture);
    glBindTexture( GL_TEXTURE_2D, _GLtexture);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.w, surface.h
                , 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.pixels );
    checkGLError("Failed to load texture, %s\n", Logger::LOG_ERROR);
}

Texture::~Texture() {
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_TEXTURES, "Texture %i released\n", _GLtexture);
    //if ( isLoaded() ) {
    //    free(_rawData);
    //    glDeleteTextures(1, &_GLtexture);
    //}
}

bool Texture::isLoaded() {
    return (_rawData != NULL);
}

bool Texture::cloneSurface(SDL_Surface &surface) {
    _rawSize = surface.w * surface.h * surface.format->BytesPerPixel;
    _rawData = malloc(_rawSize);

    if (_rawData != NULL) {
        memcpy(_rawData, surface.pixels, _rawSize);
        return true;
    } else {
        return false;
    } 
}

bool Texture::checkGLError(const char *errfmt, Logger::Level loglevel) {
    GLenum glerror;

    glerror = glGetError();

    if (glerror == GL_NO_ERROR) {
       return true;
    } else {
       Logger::logprintf(loglevel, Logger::LOG_APPLICATION, errfmt, gluErrorString(glerror));
       return false;
    }
}
