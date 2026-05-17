#ifndef UNTITLED_HIGHLIFECELL_H
#define UNTITLED_HIGHLIFECELL_H
#pragma once
#include "Cell.h"

class HighLifeCell : public Cell
{
public:
    explicit HighLifeCell(bool isAlive = false);
    HighLifeCell(const HighLifeCell& other);
    ~HighLifeCell() override;

    bool survives(int neighbors) const override;
    bool born(int neighbors)     const override;
    //B36/S23
};
#endif //UNTITLED_HIGHLIFECELL_H