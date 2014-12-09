#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>
#include <map>

#include "config.h"
#include "Shader.h"

class ShaderRef {
public:
  ShaderRef();
  ShaderRef(const ShaderRef &copy);
  ShaderRef(const Shader &ref);
  ~ShaderRef();

  std::string getSource();
  bool isValid();

  GLuint getShader();

  ShaderRef &operator=(ShaderRef *source);
  ShaderRef &operator=(ShaderRef &source);
private:


  Shader *_master;
};
