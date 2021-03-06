#include "PhilosopherCore.h"

Chopstick::Chopstick() {
  pthread_mutex_init( &_mtx_held, NULL );
  pthread_mutex_init( &_mtx_access, NULL );

  _state = ItemState::CHOPSTICK_FREE;
  _held = false;
}

Chopstick::~Chopstick() {
  pthread_mutex_destroy( &_mtx_held );
  pthread_mutex_destroy( &_mtx_access );
}

ItemState Chopstick::getState() {
  ItemState state;

  pthread_mutex_lock(&_mtx_access);
  state = _state;
  pthread_mutex_unlock(&_mtx_access);

  return state;
}

void Chopstick::grab(bool left) {
  pthread_mutex_lock(&_mtx_held);

  grabbed(left);  
}

bool Chopstick::tryGrab(bool left) {
  int result;

  result = pthread_mutex_trylock(&_mtx_held);

  if ( result == 0 ) {
    grabbed(left);  
    return true;
  } else {
    // Lock failed
    return false;
  }
}

void Chopstick::grabbed(bool left) {
  pthread_mutex_lock(&_mtx_access);
  if (left) {
    _state = ItemState::CHOPSTICK_LEFT;
  } else {
    _state = ItemState::CHOPSTICK_RIGHT;
  }

  _held = true;
  _held_by = pthread_self();

  pthread_mutex_unlock(&_mtx_access);
}

void Chopstick::release() {
  pthread_mutex_unlock(&_mtx_held);

  pthread_mutex_lock(&_mtx_access);
  _state = ItemState::CHOPSTICK_FREE;
  _held = false;
  pthread_mutex_unlock(&_mtx_access);
}

bool Chopstick::iHold() {
  if (_held) {
    return (bool) pthread_equal( _held_by, pthread_self());
  } else {
    // Not held by anyone.
    return false;
  }
} 
