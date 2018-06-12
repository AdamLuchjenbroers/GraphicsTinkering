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

    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is hungry\n", _seat); 
    setState(ItemState::PHILOSOPHER_WAITING);

    pthread_cleanup_push( releaseAllChopsticks , this);

    has_left  = false;
    has_right = false;

    // Lock the Table and setup cleanup. Use setcancelstate() to ensure both must complete to avoid
    // possible wierdness and locking issues if somehow interrupted between these two calls.
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    _controller->lockTable();  
    pthread_cleanup_push( unlockTable , this);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

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

    //Unlock table and switch off the cleanup handler, again as an atomic op.
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    _controller->unlockTable();
    pthread_cleanup_pop(false);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    setState(ItemState::PHILOSOPHER_EATING);
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is eating\n", _seat); 
 
     wait();
    Logger::logprintf(Logger::LOG_VERBOSEINFO, Logger::LOG_APPLICATION, "TryWaitPhilosopher %i is sated\n", _seat); 
    _left->release();
    _right->release();
    _controller->sendChange();
    pthread_cleanup_pop(false);

    setState(ItemState::PHILOSOPHER_THINKING);
  }
}

void TryWaitPhilosopher::stop() {
  pthread_cancel(_thread);
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Cancel Queued for philosopher %i\n", _seat); 

  // Broadcast the table changed condition variable to force threads to resume.
  // This is needed to shake free any threads currently waiting on this variable.
  _controller->sendChange();

  pthread_join(_thread, NULL);
  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Ended for philosopher %i\n", _seat); 
}

void unlockTable(void *arg) {
  TryWaitPhilosopher *p = (TryWaitPhilosopher *)arg;

  p->_controller->unlockTable();
}
