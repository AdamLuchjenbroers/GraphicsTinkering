#include "Philosopher.h"

#include <stdlib.h>
#include <unistd.h>

Philosopher::Philosopher() {
  _ready = false;
  _controller = NULL;
}

Philosopher::Philosopher(TableState *controller, int seat) {
  this->setup(controller, seat);
}

void Philosopher::setup(TableState* controller, int seat) {
  _seat = seat;
  _controller = controller;

  _state = ItemState::PHILOSOPHER_WAITING;
  _ready = true;
}

ItemState Philosopher::get_state() {
  return _state;
}

void Philosopher::start() {
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Creating thread for philosopher %i\n", _seat); 
  pthread_create(&_thread, NULL, (THREADFUNCPTR) &Philosopher::run, this);
}

void *Philosopher::run() {
  int delay;

  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 
  delay = rand() % 7;
  sleep(delay);

  _state = ItemState::PHILOSOPHER_EATING;
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Philosopher %i is eating\n", _seat); 
}


