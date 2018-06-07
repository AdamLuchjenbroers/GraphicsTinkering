#pragma once
#include "PhilosopherCore.h"
#include "NaiveCore.h"
#include "NaiveTable.h"
#include "NaivePhilosopher.h"

class NaiveCore : public PhilosopherCore {
public:
    NaiveCore();

    virtual void setupTable(int diners);
};
