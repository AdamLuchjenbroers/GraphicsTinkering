
#include "TableState.h"

TableState::TableState(int diners) {
  _diners = diners;

  philosophers = new PhilosopherState[diners];
  chopsticks = new ChopstickState[diners];
}

TableState::~TableState() {
  delete philosophers;
  delete chopsticks;
}
