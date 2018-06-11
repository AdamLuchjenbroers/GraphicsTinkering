#include "PhilosopherCore.h"

PhilosopherRef::~PhilosopherRef() {
  if (_ref) {
    delete _ref;
  }
}

void PhilosopherRef::setReference(Philosopher *ref) {
  if (_ref) {
    delete _ref;
  }
  
 _ref = ref;
}
