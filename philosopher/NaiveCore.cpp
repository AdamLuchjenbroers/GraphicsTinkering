
#include "NaiveCore.h"

NaiveCore::NaiveCore()
{
    display = SDLDisplay::resizableDisplay("Dining Philosophers - Naive Locking", 800, 800);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void NaiveCore::setupTable(int diners) {
    if (_table) {
        delete _table;
    }

    _table = new NaiveTable(diners);
    _table->seatDiners();
}



