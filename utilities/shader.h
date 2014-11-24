#pragma once

#define GL_GLEXT_PROTOTYPES

#include <GL/glcorearb.h>
#include <list>
#include <string>

class Shader {
public:
  Shader(const std::string scriptfile, GLenum shadertype);
  ~Shader();

  void printScript();

  GLuint getShader();
private:
  void prepareSource();

  std::list<std::string> shaderscript;
  // OpenGL expects an array of chars
  char **shadersource;
  size_t shaderlines;

  GLuint shader;
};
