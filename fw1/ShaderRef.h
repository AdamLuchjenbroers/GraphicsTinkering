#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>
#include <map>

#include "Shader.h"

class ShaderRef {
public:
  ShaderRef();
  ShaderRef(const ShaderRef &copy);
  ShaderRef(Shader &ref);
  ~ShaderRef();

  std::string getSource();
  void printShader();
  bool isValid();

  GLuint getShader();

  ShaderRef &operator=(const ShaderRef *source);
  ShaderRef &operator=(const ShaderRef &source);
private:

  Shader *_master;
};
