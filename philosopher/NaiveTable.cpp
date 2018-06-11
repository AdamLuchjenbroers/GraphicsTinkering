
#include "NaiveCore.h"

NaiveTable::NaiveTable(int diners)
: TableState(diners) {

}

void NaiveTable::seatDiners() {
  for(int i=0;i<_diners;i++) {
     Philosopher *p = new NaivePhilosopher(this, i, 1.0, 2.5);
     _philosophers[i].set_reference(p);
  }
}
