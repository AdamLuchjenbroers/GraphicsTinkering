#include "Texture.h"
#include "Logger.h"

#include <cstring>
#include <cstdlib>

#include <SDL2/SDL_image.h>
#include <GL/glu.h>

TextureRef Texture::loadImage(const char *filename) {
    SDL_Surface *bitmap = IMG_Load(filename);
 
    if (bitmap == NULL) {
        Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_TEXTURES, "Failed loading texture from file %s - Error: %s\n", filename, SDL_GetError());
        return TextureRef();
    }

    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_TEXTURES, "Successfully loaded texture from file %s\n", filename);
    Texture *texture = new Texture(*bitmap);
    SDL_FreeSurface(bitmap);

    return TextureRef(*texture);
}

Texture::Texture(SDL_Surface &surface) {
    _refCount = 0;

    glGenTextures(1, &_GLtexture);
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_TEXTURES, "Loading SDL Surface 0x%X (Pixel Format %s) to OpenGL name %i\n", &surface,SDL_GetPixelFormatName(surface.format->format), _GLtexture);

    glBindTexture( GL_TEXTURE_2D, _GLtexture);
    _loaded = checkGLError("glBindTexture failed: %s\n", Logger::LOG_ERROR );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, surface.w, surface.h
                , 0, GL_RGBA, GL_UNSIGNED_BYTE, surface.pixels );
    _loaded &= checkGLError("Failed to load texture from SDL Surface: %s\n", Logger::LOG_ERROR);
}

Texture::~Texture() {
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_TEXTURES, "Texture %i released\n", _GLtexture);
    if ( _loaded ) {
         glDeleteTextures(1, &_GLtexture);
    }
}

bool Texture::isLoaded() {
    return (_loaded);
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
