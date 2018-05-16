#pragma once

class TableState {
public: 
  TableState(int diners);
  ~TableState();

  enum PhilosopherState {
      PHILOSOPHER_THINKING
  ,   PHILOSOPHER_WAITING
  ,   PHILOSOPHER_EATING
  };

  enum ChopstickState {
      CHOPSTICK_FREE
  ,   CHOPSTICK_LEFT
  ,   CHOPSTICK_RIGHT
  };

  int num_diners() { return _diners; };

private:
  int _diners;

  PhilosopherState *philosophers;
  ChopstickState *chopsticks;
};
