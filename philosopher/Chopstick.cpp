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

void Chopstick::grab(bool left) {
  pthread_mutex_lock(&_mtx_access);
  
  pthread_mutex_lock(&_mtx_held);

  if (left) {
    _state = ItemState::CHOPSTICK_LEFT;
  } else {
    _state = ItemState::CHOPSTICK_RIGHT;
  }
  pthread_mutex_unlock(&_mtx_access);
}

void Chopstick::release() {
  pthread_mutex_lock(&_mtx_access);
  
  _state = ItemState::CHOPSTICK_FREE;

  pthread_mutex_unlock(&_mtx_held);
  pthread_mutex_unlock(&_mtx_access);
} 
