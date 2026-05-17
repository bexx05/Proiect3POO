//
// Created by Rebeca on 29/04/2026.
//
#include "Cell.h"

// variabila statica
int Cell::livingCellCount = 0;

// constructor
Cell::Cell(bool isAlive)
    : isAlive_(isAlive)
{
    if (isAlive_)
        ++livingCellCount;
}

//constructor de copiere
Cell::Cell(const Cell& other)
    : isAlive_(other.isAlive_)
{
    if (isAlive_)
        ++livingCellCount;
}

// destructor
Cell::~Cell()
{
    if (isAlive_)
        --livingCellCount;
}

bool Cell::isAlive() const
{
    return isAlive_;
}

//doar aici schimb variabila statica
void Cell::setAlive(bool alive)
{
    if (alive && !isAlive_)
        ++livingCellCount;
    else if (!alive && isAlive_)
        --livingCellCount;

    isAlive_ = alive;
}

int Cell::getLivingCellCount()
{
    return livingCellCount;
}

//interfata non virtuala pentru o functie virtuala
bool Cell::nextState(int neighbors) const
{
    return isAlive_ ? survives(neighbors) : born(neighbors);
}