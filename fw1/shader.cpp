#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>

#include "shader.h"
#include <GL/glu.h>

Shader::Shader(const std::string scriptfile, GLenum shadertype) {
  std::ifstream script;
  std::string scriptline;
  GLenum glerror;

  this->shader = 0;
  this->shadersource = NULL;
  this->shaderlines = 0;

  script.open(scriptfile.c_str());

  if ( script.fail() ) {
    printf("FAILURE: Unable to open shader %s (%s)\n", scriptfile.c_str(), strerror(errno));
    return;
  }

  while ( getline(script, scriptline) ) {
    this->shaderscript.push_back( scriptline );
  }

  this->prepareSource();

  this->shader = glCreateShader(shadertype);

  glShaderSource(this->shader, this->shaderlines, this->shadersource, NULL);
  glerror = glGetError();
  if (glerror != GL_NO_ERROR) {
    printf("ERROR: Unable to load shader: %s\n", gluErrorString(glerror));
    return;
  } 

  glCompileShader(this->shader);
  glerror = glGetError();
  if (glerror != GL_NO_ERROR) {
    printf("ERROR: Failed to compile %s: %s\n", scriptfile.c_str(), gluErrorString(glerror));
  } else {
    printf("INFO: Successfully compiled %s\n", scriptfile.c_str());

    this->shaderscript.clear();
    this->releaseSource();
  }

};

Shader::~Shader() {
    if (this->shader >= 0) {
    	glDeleteShader(this->shader);
    }

    if (this->shadersource != NULL) {
        this->releaseSource();
    }
};

void Shader::releaseSource() {
  int i;

  for(i=0;i<this->shaderlines;i++) {
    delete this->shadersource[i];
  }

  delete this->shadersource;

  this->shadersource = NULL;
}

void Shader::printScript() {
  int line = 0;

  if (this->shadersource == NULL) {
      return;
  }

  while (line < this->shaderlines) {
    std::cout << this->shadersource[line];
    line++;
  }
};


void Shader::printShader() {
  GLchar shadersource[1024];

  glGetShaderSource(this->shader, 1024, NULL, shadersource);

  printf("Shader source:\n%s\n------------\n",shadersource);
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

