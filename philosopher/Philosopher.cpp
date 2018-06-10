#include "PhilosopherCore.h"

#include <stdlib.h>
#include <unistd.h>

Philosopher::Philosopher(TableState *controller, int seat) {
  _seat = seat;
  _controller = controller;

  _state = ItemState::PHILOSOPHER_THINKING;
  pthread_mutex_init(&_mtx_access, NULL);

  _ready = true;
}

Philosopher::~Philosopher() {
  pthread_mutex_destroy(&_mtx_access);
}

ItemState Philosopher::get_state() {
  ItemState val;

  pthread_mutex_lock(&_mtx_access);
  val = _state;
  pthread_mutex_unlock(&_mtx_access);

  return val;
}

void Philosopher::set_state(ItemState val) {
  pthread_mutex_lock(&_mtx_access);
  _state = val;
  pthread_mutex_unlock(&_mtx_access);
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
  useconds_t delay;

  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 
  delay = 3000000 + (rand() % 4000000);
  usleep(delay);

  set_state( ItemState::PHILOSOPHER_EATING );
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Philosopher %i is eating\n", _seat); 
}


