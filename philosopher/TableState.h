#pragma once

#include "../fw1/fw1.h"

class TableState {
public: 
  TableState(int diners);
  ~TableState();

  // Use explicit assignment here and in GLSL
  // so we can easily ensure / verify alignment.
  enum ItemState {
      PHILOSOPHER_THINKING = 0
  ,   PHILOSOPHER_WAITING  = 1
  ,   PHILOSOPHER_EATING   = 2
  ,   CHOPSTICK_FREE       = 4
  ,   CHOPSTICK_LEFT       = 5
  ,   CHOPSTICK_RIGHT      = 6
  };

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
};
