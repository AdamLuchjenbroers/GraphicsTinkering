#pragma once

#include <pthread.h>
#include "constants.h"

class Chopstick {
public:
  Chopstick();
  ~Chopstick();

  ItemState get_state();

protected:
  pthread_mutex_t _mtx_held;
  ItemState _state;
};
