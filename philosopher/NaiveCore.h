#pragma once
#include "NaivePhilosophers.h"


class NaiveCore : public PhilosopherCore {
public:
    NaiveCore();

    virtual void setupTable(int diners);
};
