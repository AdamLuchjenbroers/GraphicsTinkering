
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

void TableState::seatDiners() {
  for(int i=0;i<_diners;i++) {
     Philosopher *p = new Philosopher(this, i);
     _philosophers[i].set_reference(p);
  }
}

Chopstick *TableState::left_of(int seat) {
  return &_chopsticks[seat];
}

Chopstick *TableState::right_of(int seat) {
  int idx;

  if (seat > 0) {
    idx = seat - 1;
  } else {
    idx = _diners - 1;
  }

  return &_chopsticks[idx];
}


void TableState::writeState(GLvoid *target) {
  GLint *buf = (GLint *)target;

  for(int i = 0;i < _diners;i++) {
    buf[2*i]     = _philosophers[i].get_state(); 
    buf[(2*i)+1] = _chopsticks[i].get_state();
  }
}

void TableState::startDinner() {
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Starting Dinner: \n");

  for(int i=0;i<_diners;i++) { 
     _philosophers[i].start();
  }
}

bool TableState::isRunning() {
  return _running;
}

bool TableState::stopRunning() {
  _running = false;
  return _running;
}
