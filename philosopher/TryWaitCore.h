#pragma once
#include "PhilosopherCore.h"
#include "TryWaitCore.h"
#include "TryWaitTable.h"
#include "TryWaitPhilosopher.h"

class TryWaitCore : public PhilosopherCore {
public:
    TryWaitCore();

    virtual void setupTable(int diners);
};
