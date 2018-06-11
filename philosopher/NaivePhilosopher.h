#pragma once

#include "Philosopher.h"

class NaivePhilosopher : public Philosopher {
public:
  NaivePhilosopher(TableState *controller, int seat, float min_wait, float max_wait) : Philosopher(controller, seat, min_wait, max_wait) {};

  virtual void start();
  void *run();
};
