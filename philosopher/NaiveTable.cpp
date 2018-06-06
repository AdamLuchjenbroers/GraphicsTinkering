
#include "PhilosopherCore.h"

NaiveTable::NaiveTable(int diners)
: TableState(diners) {

  for(int i=0;i<_diners;i++) {
     Philosopher *p = new Philosopher(this, i);
     _philosophers[i].set_reference(p);
  }
}
