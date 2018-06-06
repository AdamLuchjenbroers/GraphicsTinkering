#pragma once

#include "PhilosopherCore.h"

class PhilosopherRef {
public:
  PhilosopherRef() : _ref(NULL) {};
  PhilosopherRef(Philosopher *ref) : _ref(ref) {};

  ~PhilosopherRef();

  void set_reference(Philosopher *ref);

  void start() { _ref->start(); }
  ItemState get_state() { return _ref->get_state(); }

protected:
  Philosopher *_ref;
};
