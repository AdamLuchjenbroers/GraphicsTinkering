#pragma once

#include "Philosopher.h"

class TryWaitPhilosopher : public Philosopher {
public:
  TryWaitPhilosopher(TableState *controller, int seat, float min_wait, float max_wait) : Philosopher(controller, seat, min_wait, max_wait) {};

  friend void unlockTable(void *arg);

  virtual void start();
  virtual void stop();
  void *run();
};

void unlockTable(void *arg);
