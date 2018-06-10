#pragma once

#include "Philosopher.h"

class NaivePhilosopher : public Philosopher {
public:
  NaivePhilosopher(TableState *controller, int seat) : Philosopher(controller, seat) {};

  virtual void start();
  void *run();
};
