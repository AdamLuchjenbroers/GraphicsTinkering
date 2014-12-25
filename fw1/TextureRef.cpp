#include "TextureRef.h"

TextureRef::TextureRef(Texture &texture) {
    _texture = &texture;
    _texture->_refCount++;
}

TextureRef::TextureRef(const TextureRef &ref) {
    _texture = ref._texture;
    _texture->_refCount++;
}

TextureRef::~TextureRef() {
    _texture->_refCount--;

    if (_texture->_refCount < 1) {
        delete _texture;
    }
}
