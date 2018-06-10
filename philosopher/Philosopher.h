#pragma once

#include <pthread.h>
#include "constants.h"

class TableState;

class Philosopher {
public:
  Philosopher(TableState *controller, int seat);
  ~Philosopher();

  ItemState get_state();

  void start();
  void stop();
  void *run();

protected:
  void set_state(ItemState val);

  int _seat;
  ItemState _state;

  bool _ready;

  TableState *_controller;
  pthread_t _thread;

  pthread_mutex_t _mtx_access;
};

	
typedef void * (*THREADFUNCPTR)(void *);
