#include "Texture.h"
#include "Logger.h"

#include <cstring>
#include <cstdlib>

TextureRef Texture::loadBMP(const char *filename) {
    SDL_Surface *bitmap = SDL_LoadBMP(filename);
 
    if (bitmap == NULL) {
        Logger::logprintf(Logger::LOG_WARN, Logger::LOG_TEXTURES, "Failed loading BMP texture from file %s - Error: %s\n", filename, SDL_GetError());
        return TextureRef();
    }

    Texture *texture = new Texture(*bitmap);
    SDL_FreeSurface(bitmap);

    return TextureRef(*texture);
}

Texture::Texture(SDL_Surface &surface) {
    _refCount = 0;

    switch(surface.format->format) {
    case SDL_PIXELFORMAT_RGB888:
        cloneSurface(surface);
        _GLformat = GL_RGB;
        _GLfmtChannels = 3;
        _GLtype = GL_UNSIGNED_BYTE;
        break;
    default:
        //TODO: Perform a conversion then copy.
        cloneSurface(surface);
        _GLformat = GL_RGB;
        _GLfmtChannels = 3;
        _GLtype = GL_UNSIGNED_BYTE;
    }

    glGenTextures(1, &_GLtexture);
    glBindTexture( GL_TEXTURE_2D, _GLtexture);

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
    glTexImage2D( GL_TEXTURE_2D, 0, _GLfmtChannels, surface.w, surface.h
                , 0, _GLformat, _GLtype, _rawData );
    
}

Texture::~Texture() {
    if ( isLoaded() ) {
        free(_rawData);
    }
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
