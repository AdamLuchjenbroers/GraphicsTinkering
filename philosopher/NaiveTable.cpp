
#include "NaiveCore.h"

NaiveTable::NaiveTable(int diners)
: TableState(diners) {

}

void NaiveTable::seatDiners() {
  for(int i=0;i<_diners;i++) {
     Philosopher *p = new Philosopher(this, i);
     _philosophers[i].set_reference(p);
  }
}

