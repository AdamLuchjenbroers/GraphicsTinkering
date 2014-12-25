#pragma once

#include "Texture.h"

class Texture;

class TextureRef {
public:
    TextureRef(Texture &source);
    TextureRef(const TextureRef &ref);
    ~TextureRef();

private:
    Texture *_texture;
};
