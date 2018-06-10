#pragma once

#include <pthread.h>

class Chopstick {
public:
  Chopstick();
  ~Chopstick();

  ItemState get_state();

  void grab(bool left);
  void release();

protected:
  /* Two Mutexes are used to control access to Chopstick:

     _mtx_access is used when reading or writing state. It should be held only 
        while performing and read/write operations on current state.

     _mtx_held is held by the philosopher currently holding the chopstick. and
        is held for the duration of the chopstick being held.

     Locks should always be acquired in the order: access, held.
  */

  pthread_mutex_t _mtx_held;
  pthread_mutex_t _mtx_access;

  ItemState _state;
};
