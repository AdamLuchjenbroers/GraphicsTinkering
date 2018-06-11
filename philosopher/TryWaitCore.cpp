
#include "TryWaitCore.h"

TryWaitCore::TryWaitCore()
{
    display = SDLDisplay::resizableDisplay("Dining Philosophers - TryWait Locking", 800, 800);

    _projection = Matrix4::fovHorizontal( 1.0f, 6.0f, 90.0f, display->aspectRatio());
}

void TryWaitCore::setupTable(int diners) {
    if (_table) {
        delete _table;
    }

    _table = new TryWaitTable(diners);
    _table->seatDiners();
}



