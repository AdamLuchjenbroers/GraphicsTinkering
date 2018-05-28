
#include "TableState.h"
#include <stdio.h>

TableState::TableState(int diners) {
  _diners = diners;
  _running = true;
}


TableState::~TableState() {
}

void TableState::write_state(GLvoid *target) {
  GLint *buf = (GLint *)target;

  for(int i = 0;i < _diners;i++) {
    buf[2*i]     = TableState::PHILOSOPHER_THINKING; 
    buf[(2*i)+1] = TableState::CHOPSTICK_FREE; 
  }
}

bool TableState::is_running() {
  return _running;
}

bool TableState::stop_running() {
  _running = false;
  return _running;
}
