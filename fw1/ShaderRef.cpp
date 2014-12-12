#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>

#include "ShaderRef.h"
#include "Logger.h"
#include <GL/glu.h>

ShaderRef::ShaderRef() {
    _master = NULL;
}

ShaderRef::ShaderRef(const ShaderRef &copy) {
    _master = copy._master;
};

ShaderRef::ShaderRef(Shader &ref) {
    _master = &ref;
}

ShaderRef::~ShaderRef() {
};

std::string ShaderRef::getSource() {
    if (_master != NULL) {
        return _master->getSource();
    } else {
        return "";
    }
}

bool ShaderRef::isValid() {
    if (_master != NULL) {
        return _master->isValid();
    } else {
        return false;
    }
}

void ShaderRef::printShader() {
    std::string shaderSource = getSource();

  Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_SHADERS, "Shader source:\n%s\n------------\n", shaderSource.c_str());
};

GLuint ShaderRef::getShader() {
    if (_master != NULL) {
        return _master->getShader();
    } else {
        return 0;
    }
}


ShaderRef &ShaderRef::operator=(const ShaderRef &source) {
    _master = source._master;
    return *this;
};

ShaderRef &ShaderRef::operator=(const ShaderRef *source) {
    this->_master = source->_master;
    return *this;
}

