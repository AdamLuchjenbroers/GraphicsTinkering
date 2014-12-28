#include "TextureRef.h"

TextureRef::TextureRef() {
    _texture = NULL;
}

TextureRef::TextureRef(Texture &texture) {
    _texture = &texture;
    _texture->_refCount++;
}

TextureRef::TextureRef(const TextureRef &ref) {
    _texture = ref._texture;
    _texture->_refCount++;
}

TextureRef::~TextureRef() {
    if (_texture != NULL) {
        _texture->_refCount--;
    
        if (_texture->_refCount < 1) {
            delete _texture;
        }
    }
}

TextureRef &TextureRef::operator=(const TextureRef &copy) {
    if (copy._texture == _texture) {
        //No change in referenced texture, so no need to update refcounts.
        return *this;
    }

    if ( _texture != NULL ) {
        _texture->_refCount--;

        if (_texture->_refCount < 1) {
            delete _texture;
        }
    }

    _texture = copy._texture;
    if (_texture != NULL) {
        _texture->_refCount++;
    }
    
    return *this;
}

bool TextureRef::activate(GLenum texUnit) {
    if (!isValid()) {
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, _texture->_GLtexture);
    glActiveTexture(texUnit);

    return true;
}

bool TextureRef::isValid() {
    if (_texture == NULL) {
        return false;
    }

    return _texture->isLoaded();
}
