#pragma once

#include "../fw1/fw1.h"
#include <vector>
#include <map>

class TableState {
public: 
  TableState(int diners);
  ~TableState();

  enum ItemType {
      PHILOSOPHER = 1
  ,   CHOPSTICK   = 2
  };

  int numDiners() { return _diners; };

  virtual void seatDiners();

  void writeState(GLvoid *target);

  Chopstick *leftOf(int seat);
  Chopstick *rightOf(int seat);

  void startDinner();

  void lockTable();
  void unlockTable();

  void awaitChange();
  void sendChange();

  void updateTally(ItemState state, long interval);
protected:
  int _diners;
  bool _running;

  pthread_cond_t _cond_changed;
  pthread_mutex_t _mtx_changed;
  pthread_t _changed_by;

  std::vector<PhilosopherRef> _philosophers; 
  std::vector<Chopstick>   _chopsticks;

  pthread_mutex_t _mtx_tally;
  std::map<ItemState, long> tally;
};
