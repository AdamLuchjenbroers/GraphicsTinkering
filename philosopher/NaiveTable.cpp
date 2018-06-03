
#include "PhilosopherCore.h"

NaiveTable::NaiveTable(int diners)
: TableState(diners) {

  for(int i=0;i<_diners;i++) {
     _philosophers[i].setup(this, i);
  }
}
