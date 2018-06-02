#include "Chopstick.h"

Chopstick::Chopstick() {
  pthread_mutex_init( &_mtx_held, NULL );

  _state = ItemState::CHOPSTICK_LEFT;
}

Chopstick::~Chopstick() {
  pthread_mutex_destroy( &_mtx_held );
}

ItemState Chopstick::get_state() {
  return _state;
}
