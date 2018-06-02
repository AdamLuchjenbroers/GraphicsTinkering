#pragma once

#include "../fw1/fw1.h"
#include "constants.h"
#include "Philosopher.h"
#include "Chopstick.h"

class Philosopher;

class TableState {
public: 
  TableState(int diners);
  ~TableState();

  enum ItemType {
      PHILOSOPHER = 1
  ,   CHOPSTICK   = 2
  };

  int num_diners() { return _diners; };

  void write_state(GLvoid *target);

  bool is_running();
  bool stop_running();

private:
  int _diners;
  bool _running;

  Philosopher *_philosophers; 
  Chopstick *_chopsticks;
};
