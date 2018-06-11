#include "TryWaitCore.h"

#include <stdlib.h>
#include <unistd.h>

void TryWaitPhilosopher::start() {
  if (_ready) {
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Creating thread for philosopher %i\n", _seat); 
    pthread_create(&_thread, NULL, (THREADFUNCPTR) &TryWaitPhilosopher::run, this);
  } else {
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to start thread for philosopher %i - not initialized\n", _seat); 
  }
}

void *TryWaitPhilosopher::run() {
  bool has_left, has_right;

  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 
  while (1) {
    wait();

    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is hungry\n", _seat); 
    setState(ItemState::PHILOSOPHER_WAITING);

    pthread_cleanup_push( releaseAllChopsticks , this);

    has_left  = false;
    has_right = false;

    _controller->lockTable();  
    while (! (has_left && has_right)) {

      has_left  =  _left->tryGrab(true);
      has_right = _right->tryGrab(false);


      if ( (!has_left) && has_right ) {
        _right->release();
        has_right = false;
      } else if ( (!has_right) && has_left) {
        _left->release();
        has_left = false;
      } 

      if (! (has_left && has_right) ) { 
        _controller->awaitChange();
      }
    }
    _controller->unlockTable();

    setState(ItemState::PHILOSOPHER_EATING);
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is eating\n", _seat); 
 
     wait();
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is sated\n", _seat); 
    _left->release();
    _right->release();
    _controller->sendChange();
    pthread_cleanup_pop(false);

    setState(ItemState::PHILOSOPHER_THINKING);
  }
}
