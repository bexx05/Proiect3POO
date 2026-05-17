//
// Created by Rebeca on 29/04/2026.
//

#ifndef UNTITLED_NORMALCELL_H
#define UNTITLED_NORMALCELL_H

#pragma once
#include "Cell.h"

class ConwayCell : public Cell
{
public:
    explicit ConwayCell(bool isAlive = false);
    ConwayCell(const ConwayCell& other);
    ~ConwayCell() override;

    bool survives(int neighbors) const override;
    bool born(int neighbors)     const override;
};
#endif //UNTITLED_NORMALCELL_H