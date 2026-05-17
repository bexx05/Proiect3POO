#include "HighLifeCell.h"

HighLifeCell::HighLifeCell(bool isAlive)
    : Cell(isAlive)
{
}

HighLifeCell::HighLifeCell(const HighLifeCell& other)
    : Cell(other)
{
}

HighLifeCell::~HighLifeCell() = default;

// supravietuire: 2 sau 3 vecini
bool HighLifeCell::survives(int neighbors) const
{
    return neighbors == 2 || neighbors == 3;
}

// se naste cu 3 sau 6 vecini ( 6 vecini sunt extra fata de varianta clasica conway)
bool HighLifeCell::born(int neighbors) const
{
    return neighbors == 3 || neighbors == 6;
}