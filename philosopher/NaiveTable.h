#pragma once

#include "TableState.h"


class NaiveTable : public TableState {
public:
  NaiveTable(int diners);

  virtual void seatDiners();
};
