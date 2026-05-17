//
// Created by Rebeca on 29/04/2026.
//

#ifndef UNTITLED_CELL_H
#define UNTITLED_CELL_H

#pragma once

class Cell
{
public:
    explicit Cell(bool isAlive = false);
    Cell(const Cell& other);
    virtual ~Cell();

    Cell& operator=(const Cell&) = delete;

    bool isAlive() const;
    bool nextState(int neighbors) const;
    void setAlive(bool alive);   //pentru livingcellcount

    virtual bool survives(int neighbors) const = 0;
    virtual bool born(int neighbors) const    = 0;

    static int getLivingCellCount();
    static int livingCellCount;  // counts only living cells

protected:
    bool isAlive_;
};

#endif //UNTITLED_CELL_H