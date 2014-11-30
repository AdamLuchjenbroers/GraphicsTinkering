#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>

#include "shader.h"
#include "logger.h"
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
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "Unable to open shader source file %s (%s)\n", scriptfile.c_str(), strerror(errno));
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
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "glShaderSource failed to load shader: %s\n", gluErrorString(glerror));
    return;
  } 

  glCompileShader(this->shader);
  glerror = glGetError();
  if (glerror != GL_NO_ERROR) {
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_SHADERS, "glCompileShader failed to compile %s: %s\n", scriptfile.c_str(), gluErrorString(glerror));
  } else {
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_SHADERS, "Successfully compiled shader: %s\n", scriptfile.c_str());

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


  Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "----------------");
  while (line < this->shaderlines) {
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, shadersource[line]);
    line++;
  }
  Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "----------------");
};


void Shader::printShader() {
  GLchar shadersource[1024];

  glGetShaderSource(this->shader, 1024, NULL, shadersource);

  Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Shader source:\n%s\n------------\n",shadersource);
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

/*
 * Shader Library 
 */
ShaderLibrary::ShaderLibrary(char *basepath) {
    //TODO: Scan path and build an index of available versions
};

ShaderLibrary *ShaderLibrary::library = NULL;

void ShaderLibrary::setLibraryPath(char *newpath) {
    if (library != NULL) {
        delete library;
    }

    library = new ShaderLibrary(newpath);
};

ShaderLibrary *ShaderLibrary::getLibrary() {
    if (library == NULL) {
        //Initialise with default library path
        char defaultPath[9] = "./shader";
        setLibraryPath(defaultPath);
    }

    return library;
};

Shader *ShaderLibrary::getShader(const char *name, GLuint stage) {
    //TODO: Implement lookup based on supported OpenGL version
};






