#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>

#include "shader.h"

Shader::Shader(const std::string scriptfile, GLenum shadertype) {
  std::ifstream script;
  std::string scriptline;

  script.open(scriptfile.c_str());

  if ( script.fail() ) {
    printf("FAILURE: Unable to open shader %s (%s)\n", scriptfile.c_str(), strerror(errno));
  }

  while ( getline(script, scriptline) ) {
    this->shaderscript.push_back( scriptline );
  }

  this->prepareSource();

  this->shader = glCreateShader(shadertype);
  glShaderSource(this->shader, this->shaderlines, this->shadersource, NULL);
  glCompileShader(this->shader);

};

Shader::~Shader() {
};

void Shader::printScript() {
  int line = 0;

  while (line < this->shaderlines) {
    std::cout << this->shadersource[line];
    line++;
  }
};

GLuint Shader::getShader() {
  return this->shader;
}

void Shader::prepareSource() {
  std::list<std::string>::iterator line;
  char **sourceline;

  this->shaderlines = this->shaderscript.size();
  this->shadersource = new char*[this->shaderlines];

  sourceline = this->shadersource;


  line = this->shaderscript.begin();

  while ( line != this->shaderscript.end() ) {
	int length = line->size();
    *sourceline = new char[length+2]; //Add space for newline and terminator.

    snprintf(*sourceline, length+2, "%s\n", line->c_str());

    line++;
    sourceline++;
  }
};

