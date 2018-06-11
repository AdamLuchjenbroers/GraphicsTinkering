#pragma once

#include <pthread.h>
#include "constants.h"

class TableState;

class Philosopher {
public:
  Philosopher(TableState *controller, int seat, float min_wait, float max_wait);
  ~Philosopher();

  ItemState getState();

  virtual void start();
  void stop();
  void *run();

  friend void releaseAllChopsticks(void *arg);

protected:
  void setState(ItemState val);

  void wait();

  int _seat;
  ItemState _state;

  bool _ready;

  TableState *_controller;
  Chopstick *_left, *_right;

  int _wait_base;
  int _wait_range;

  pthread_t _thread;
  pthread_mutex_t _mtx_access;
};

	
typedef void * (*THREADFUNCPTR)(void *);
