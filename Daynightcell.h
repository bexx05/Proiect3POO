#ifndef UNTITLED_DAYNIGHTCELL_H
#define UNTITLED_DAYNIGHTCELL_H
#pragma once
#include "Cell.h"

class DayNightCell : public Cell
{
public:
    explicit DayNightCell(bool isAlive = false);
    DayNightCell(const DayNightCell& other);
    ~DayNightCell() override;

    bool survives(int neighbors) const override;
    bool born(int neighbors)     const override;

    //B3678/S34678
};
#endif //UNTITLED_DAYNIGHTCELL_H