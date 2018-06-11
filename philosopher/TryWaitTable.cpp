
#include "TryWaitCore.h"

TryWaitTable::TryWaitTable(int diners)
: TableState(diners) {

}

void TryWaitTable::seatDiners() {
  for(int i=0;i<_diners;i++) {
     Philosopher *p = new TryWaitPhilosopher(this, i, 1.0, 2.5);
     _philosophers[i].setReference(p);
  }
}
