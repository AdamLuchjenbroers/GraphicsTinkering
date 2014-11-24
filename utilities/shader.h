#pragma once

#include <GL/gl.h>
#include <list>
#include <string>

class Shader {
public:
  Shader(char *scriptfile);
  ~Shader();

  void printScript();
private:
  std::list<std::string> shader;
  // OpenGL expects an array of chars
  char **shadersource;	
};
