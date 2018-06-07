#include "PhilosopherCore.h"

#include <stdlib.h>
#include <unistd.h>

Philosopher::Philosopher(TableState *controller, int seat) {
  _seat = seat;
  _controller = controller;

  _state = ItemState::PHILOSOPHER_WAITING;
  _ready = true;
}

ItemState Philosopher::get_state() {
  return _state;
}

void Philosopher::start() {
  if (_ready) {
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Creating thread for philosopher %i\n", _seat); 
    pthread_create(&_thread, NULL, (THREADFUNCPTR) &Philosopher::run, this);
  } else {
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to start thread for philosopher %i - not initialized\n", _seat); 
  }
}

void Philosopher::stop() {
  pthread_cancel(_thread);

  pthread_join(_thread, NULL);
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Ended for philosopher %i\n", _seat); 
}

void *Philosopher::run() {
  int delay;

  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 
  delay = rand() % 7;
  sleep(delay);

  _state = ItemState::PHILOSOPHER_EATING;
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Philosopher %i is eating\n", _seat); 
}


