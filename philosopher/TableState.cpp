
#include "PhilosopherCore.h"
#include <stdio.h>
#include <unistd.h>

TableState::TableState(int diners)
: _philosophers(diners)
, _chopsticks(diners)
{
  _diners = diners;
  _running = true;

  pthread_cond_init(&_cond_changed, NULL);
  pthread_mutex_init(&_mtx_changed, NULL);

  tally[ItemState::PHILOSOPHER_THINKING] = 0;
  tally[ItemState::PHILOSOPHER_WAITING]  = 0;
  tally[ItemState::PHILOSOPHER_EATING]   = 0;
  pthread_mutex_init(&_mtx_tally, NULL);
}

TableState::~TableState() {
  for(int i = 0;i < _diners;i++) {   
     _philosophers[i].stop();
  }

  pthread_cond_destroy(&_cond_changed);
  pthread_mutex_destroy(&_mtx_changed);

  pthread_mutex_destroy(&_mtx_tally);
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "====== Final Activity Tally ======\n  Thinking:\t%i\n  Waiting:\t%i\n  Eating:\t%i\n"
    , tally[ItemState::PHILOSOPHER_THINKING]
    , tally[ItemState::PHILOSOPHER_WAITING]
    , tally[ItemState::PHILOSOPHER_EATING]
  ); 

}

void TableState::seatDiners() {
  for(int i=0;i<_diners;i++) {
     Philosopher *p = new Philosopher(this, i, 3.0, 7.0);
     _philosophers[i].setReference(p);
  }
}

Chopstick *TableState::leftOf(int seat) {
  return &_chopsticks[seat];
}

Chopstick *TableState::rightOf(int seat) {
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
    buf[2*i]     = _philosophers[i].getState(); 
    buf[(2*i)+1] = _chopsticks[i].getState();
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

void TableState::awaitChange() {
  pthread_cond_wait(&_cond_changed, &_mtx_changed);
}

void TableState::lockTable() {
  pthread_mutex_lock(&_mtx_changed);
}

void TableState::unlockTable() {
  pthread_mutex_unlock(&_mtx_changed);
}

void TableState::sendChange() {
  pthread_cond_broadcast(&_cond_changed);
}

void TableState::updateTally(ItemState state, long interval) {
  pthread_mutex_lock(&_mtx_tally);

  tally[state] += interval;

  pthread_mutex_unlock(&_mtx_tally);
}
