#pragma once

#include <GL/gl.h>
#include <list>
#include <string>

class Shader {
public:
  Shader(char *scriptfile);

  void printScript();
private:
  std::list<std::string> shader;	
};
