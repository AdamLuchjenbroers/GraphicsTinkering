#include "PhilosopherCore.h"

#include <stdlib.h>
#include <unistd.h>

Philosopher::Philosopher(TableState *controller, int seat, float min_wait, float max_wait) {
  _seat = seat;
  _controller = controller;

  _state = ItemState::PHILOSOPHER_THINKING;
  pthread_mutex_init(&_mtx_access, NULL);

  _left  = _controller->leftOf(_seat);
  _right = _controller->rightOf(_seat);

  // Convert these values into micro-seconds for use with usleep
  _wait_base = (int) (min_wait * 1000000);
  _wait_range = (int) ((max_wait - min_wait) * 1000000);

  _ready = true; 

  _last_change = clock();
}

Philosopher::~Philosopher() {
  pthread_mutex_destroy(&_mtx_access);
}

void Philosopher::wait() {
  useconds_t delay;

  delay = _wait_base + (rand() % _wait_range);
  usleep(delay);
}

ItemState Philosopher::getState() {
  ItemState val;

  pthread_mutex_lock(&_mtx_access);
  val = _state;
  pthread_mutex_unlock(&_mtx_access);

  return val;
}

void Philosopher::setState(ItemState val) {
  clock_t now;
  ItemState last = _state;

  pthread_mutex_lock(&_mtx_access);
  _state = val;
  now = clock();
  pthread_mutex_unlock(&_mtx_access);

  _controller->updateTally(last, now - _last_change);
  _last_change = now;
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
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 

  wait();
  setState( ItemState::PHILOSOPHER_EATING );
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Philosopher %i is eating\n", _seat); 
}

void releaseAllChopsticks(void *arg) {
  Philosopher *p = (Philosopher *)arg; 

  if (p->_left->iHold()) {
    p->_left->release(); 
  }

  if (p->_right->iHold()) {
    p->_right->release(); 
  }
}
