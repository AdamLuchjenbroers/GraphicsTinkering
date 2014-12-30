#pragma once

#include "Texture.h"

class Texture;

class TextureRef {
public:
    TextureRef();
    TextureRef(Texture &source);
    TextureRef(const TextureRef &ref);
    ~TextureRef();

    TextureRef &operator=(const TextureRef &copy);

/** Returns true if this reference currently points to a valid texture.
  * @return True if this reference object links to a valid texture
  */
    bool isValid();

/** Maps the texture to an OpenGL Texture Unit.
 *  @param @texUnit The texture unit to activate.
 *  @return True if the texture could be successfully mapped
 */
    bool activate(GLenum texUnit);
private:
    Texture *_texture;
};
