#include "ConwayCell.h"

ConwayCell::ConwayCell(bool isAlive)
    : Cell(isAlive)
{
}

ConwayCell::ConwayCell(const ConwayCell& other)
    : Cell(other)
{
}

ConwayCell::~ConwayCell() = default;

// A live cell survives with 2 or 3 neighbours
bool ConwayCell::survives(int neighbors) const
{
    return neighbors == 2 || neighbors == 3;
}

// A dead cell is born with exactly 3 neighbours
bool ConwayCell::born(int neighbors) const
{
    return neighbors == 3;
}