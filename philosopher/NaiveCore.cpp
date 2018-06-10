
#include "NaiveCore.h"

NaiveCore::NaiveCore()
 : PhilosopherCore() {
}

void NaiveCore::setupTable(int diners) {
    if (_table) {
        delete _table;
    }

    _table = new NaiveTable(diners);
    _table->seatDiners();
}



