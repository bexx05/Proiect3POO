#include "DayNightCell.h"

DayNightCell::DayNightCell(bool isAlive)
    : Cell(isAlive)
{
}

DayNightCell::DayNightCell(const DayNightCell& other)
    : Cell(other)
{
}

DayNightCell::~DayNightCell() = default;

// Supravietuieste cu 3, 4, 6, 7, sau 8 vecini
bool DayNightCell::survives(int neighbors) const
{
    return neighbors == 3 || neighbors == 4 ||
           neighbors == 6 || neighbors == 7 || neighbors == 8;
}

// Se naste cu 3, 6, 7, sau 8 vecini
bool DayNightCell::born(int neighbors) const
{
    return neighbors == 3 || neighbors == 6 ||
           neighbors == 7 || neighbors == 8;
}