#pragma once

#include <pthread.h>
#include "constants.h"
#include "TableState.h"

class TableState;

class Philosopher {
public:
  Philosopher(TableState* controller, int seat);
  Philosopher();
  
  void setup(TableState* controller, int seat);

  ItemState get_state();

  void start();
  void *run();

protected:
  int _seat;
  ItemState _state;

  bool _ready;

  TableState *_controller;
  pthread_t _thread;
};

	
typedef void * (*THREADFUNCPTR)(void *);
