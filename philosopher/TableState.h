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

  int num_diners() { return _diners; };

  virtual void seatDiners();

  void write_state(GLvoid *target);

  bool is_running();
  bool stop_running();

  void start_dinner();
protected:

  int _diners;
  bool _running;

  std::vector<PhilosopherRef> _philosophers; 
  std::vector<Chopstick>   _chopsticks;
};
