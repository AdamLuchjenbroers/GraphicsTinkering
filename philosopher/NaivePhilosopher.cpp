#include "NaiveCore.h"

#include <stdlib.h>
#include <unistd.h>

void NaivePhilosopher::start() {
  if (_ready) {
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Creating thread for philosopher %i\n", _seat); 
    pthread_create(&_thread, NULL, (THREADFUNCPTR) &NaivePhilosopher::run, this);
  } else {
    Logger::logprintf(Logger::LOG_ERROR, Logger::LOG_APPLICATION, "Unable to start thread for philosopher %i - not initialized\n", _seat); 
  }
}

void *NaivePhilosopher::run() {
  useconds_t delay;


  Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "Thread Started for philosopher %i\n", _seat); 
  while (1) {
    delay = 3000000 + (rand() % 4000000);
    usleep(delay);
  
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "NaivePhilosopher %i is hungry\n", _seat); 
    set_state(ItemState::PHILOSOPHER_WAITING);

    pthread_cleanup_push( releaseAllChopsticks , this);
    _left->grab(true);
    _right->grab(false);
    set_state(ItemState::PHILOSOPHER_EATING);
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "NaivePhilosopher %i is eating\n", _seat); 

    delay = 3000000 + (rand() % 4000000);
    usleep(delay);
  
    Logger::logprintf(Logger::LOG_INFO, Logger::LOG_APPLICATION, "NaivePhilosopher %i is sated\n", _seat); 
    _left->release();
    _right->release();
    pthread_cleanup_pop(false);

    set_state(ItemState::PHILOSOPHER_THINKING);
  }
}