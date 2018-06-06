#include "PhilosopherCore.h"

PhilosopherRef::~PhilosopherRef() {
  if (_ref) {
    delete _ref;
  }
}

void PhilosopherRef::set_reference(Philosopher *ref) {
  if (_ref) {
    delete _ref;
  }
  
 _ref = ref;
}
