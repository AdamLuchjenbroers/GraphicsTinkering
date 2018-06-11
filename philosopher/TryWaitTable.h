#pragma once

#include "TableState.h"


class TryWaitTable : public TableState {
public:
  TryWaitTable(int diners);

  virtual void seatDiners();
};
