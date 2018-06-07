
#include "PhilosopherCore.h"
#include <stdio.h>
#include <unistd.h>

TableState::TableState(int diners)
: _philosophers(diners)
, _chopsticks(diners)
{
  _diners = diners;
  _running = true;
}

TableState::~TableState() {
  for(int i = 0;i < _diners;i++) {   
     _philosophers[i].stop();
  }
}

void TableState::write_state(GLvoid *target) {
  GLint *buf = (GLint *)target;

  for(int i = 0;i < _diners;i++) {
    buf[2*i]     = _philosophers[i].get_state(); 
    buf[(2*i)+1] = _chopsticks[i].get_state();
  }
}

void TableState::start_dinner() {
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Starting Dinner: \n");

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
