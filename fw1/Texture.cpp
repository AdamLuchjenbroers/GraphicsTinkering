#include "Texture.h"

#include <cstring>
#include <cstdlib>

TextureRef Texture::loadBMP(const char *filename) {
    SDL_Surface *bitmap = SDL_LoadBMP(filename);
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
        _GLtype = GL_UNSIGNED_BYTE;
        break;
    }
    cloneSurface(surface);
}

Texture::~Texture() {
    if (_rawData != NULL) {
        free(_rawData);
    }
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
