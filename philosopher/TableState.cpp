
#include "TableState.h"
#include <stdio.h>
#include <unistd.h>

TableState::TableState(int diners) {
  _diners = diners;
  _running = true;

  _philosophers = new Philosopher[_diners];
  for(int i=0;i<_diners;i++) {
     _philosophers[i].setup(this, i);
  }

  _chopsticks = new Chopstick[_diners];
}


TableState::~TableState() {
  delete[] _philosophers;
  delete[] _chopsticks;
}

void TableState::write_state(GLvoid *target) {
  GLint *buf = (GLint *)target;

  for(int i = 0;i < _diners;i++) {
    buf[2*i]     = _philosophers[i].get_state(); 
    buf[(2*i)+1] = _chopsticks[i].get_state();
  }
}

void TableState::start_dinner() {
  for(int i=0;i<_diners;i++) {
     _philosophers[i].start();
  }
}

bool TableState::is_running() {
  return _running;
}

bool TableState::stop_running() {
  _running = false;
  return _running;
}
