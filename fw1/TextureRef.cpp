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

bool TextureRef::isValid() {
    if (_texture == NULL) {
        return false;
    }

    return _texture->isLoaded();
}
