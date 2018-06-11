#pragma once

#include "PhilosopherCore.h"

class PhilosopherRef {
public:
  PhilosopherRef() : _ref(NULL) {};
  PhilosopherRef(Philosopher *ref) : _ref(ref) {};

  ~PhilosopherRef();

  void setReference(Philosopher *ref);

  void start() { _ref->start(); }
  void stop() { _ref->stop(); }
  ItemState getState() { return _ref->getState(); }

protected:
  Philosopher *_ref;
};
