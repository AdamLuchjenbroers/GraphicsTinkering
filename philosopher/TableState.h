#pragma once

#include "../fw1/fw1.h"
#include <vector>

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

  bool isRunning();
  bool stopRunning();

  void startDinner();
protected:

  int _diners;
  bool _running;

  std::vector<PhilosopherRef> _philosophers; 
  std::vector<Chopstick>   _chopsticks;
};
