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
  void printShader();

  GLuint getShader();
private:
  void prepareSource();
  void releaseSource();

  std::list<std::string> shaderscript;
  // OpenGL expects an array of chars
  char **shadersource;
  size_t shaderlines;

  GLuint shader;
};

class ShaderLibrary {
public:
    Shader *getShader(const char *name, GLuint stage);

    static ShaderLibrary *getLibrary();
    static void setLibraryPath(char *newpath);
private:
    static ShaderLibrary *library;

    ShaderLibrary(char *basepath);
};
