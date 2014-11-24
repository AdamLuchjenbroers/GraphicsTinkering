#include <stdio.h>
#include <iostream>
#include <fstream>

#include "shader.h"

Shader::Shader(char *scriptfile) {
  std::ifstream script;
  std::string scriptline;

  script.open(scriptfile);
  while ( getline(script, scriptline) ) {
    this->shader.push_back( scriptline );
  }

  printf("Lines: %i\n", (int)this->shader.size());
}

Shader::~Shader() {
}

void Shader::printScript() {
  std::list<std::string>::iterator line;

  line = this->shader.begin();

  while ( line != this->shader.end() ) {
    std::cout << *line << "\n";
    line++;
  }  
}

int main() {
  Shader test = Shader("junk.sdr");
  test.printScript();

  return 0;
}
