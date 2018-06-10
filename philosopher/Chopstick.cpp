#include "PhilosopherCore.h"

Chopstick::Chopstick() {
  pthread_mutex_init( &_mtx_held, NULL );
  pthread_mutex_init( &_mtx_access, NULL );

  _state = ItemState::CHOPSTICK_FREE;
}

Chopstick::~Chopstick() {
  pthread_mutex_destroy( &_mtx_held );
  pthread_mutex_destroy( &_mtx_access );
}

ItemState Chopstick::get_state() {
  ItemState state;

  pthread_mutex_lock(&_mtx_access);
  state = _state;
  pthread_mutex_unlock(&_mtx_access);

  return state;
}

void Chopstick::set_state(ItemState val) {
  pthread_mutex_lock(&_mtx_access);
  _state = val;
  pthread_mutex_unlock(&_mtx_access);
}

void Chopstick::grab(bool left) {
  pthread_mutex_lock(&_mtx_held);
  
  if (left) {
    set_state(ItemState::CHOPSTICK_LEFT);
  } else {
    set_state(ItemState::CHOPSTICK_RIGHT);
  }
}

void Chopstick::release() {
  pthread_mutex_unlock(&_mtx_held);

  pthread_mutex_lock(&_mtx_access);
  _state = ItemState::CHOPSTICK_FREE;
  pthread_mutex_unlock(&_mtx_access);
} 
