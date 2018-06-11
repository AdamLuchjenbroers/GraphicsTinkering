#pragma once

#include <pthread.h>
#include "constants.h"

class TableState;

class Philosopher {
public:
  Philosopher(TableState *controller, int seat);
  ~Philosopher();

  ItemState get_state();

  virtual void start();
  void stop();
  void *run();

  friend void releaseAllChopsticks(void *arg);

protected:
  void set_state(ItemState val);

  int _seat;
  ItemState _state;

  bool _ready;

  TableState *_controller;
  Chopstick *_left, *_right;

  pthread_t _thread;
  pthread_mutex_t _mtx_access;
};

	
typedef void * (*THREADFUNCPTR)(void *);
