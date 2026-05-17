//
// Created by Rebeca on 29/04/2026.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H

#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "CellFactory.h"
#include "GenerationLog.h"
#include "ISimulationObserver.h"

class Grid
{
    GenerationLog<int> generationLog_;   // ← un singur câmp nou
    int generation_ = 0;
    std::vector<ISimulationObserver*> observers_;
public:
    Grid(int rows, int cols, int cellSize);
    ~Grid();

    // e.g.  grid.populate([](bool a){ return std::make_shared<ConwayCell>(a); }, 0.3f);
    using CellFactory = std::function<std::shared_ptr<Cell>(bool alive)>;

    void populate(const ICellFactory& factory, float aliveProbability);
    void run();   // SFML event + render loop
    void printCellTypeStats() const;
    const GenerationLog<int>& getLog() const { return generationLog_; }
    void addObserver(ISimulationObserver* obs) { observers_.push_back(obs); }

private:
    void update();
    void draw();
    int  countNeighbors(int row, int col) const;

    int rows_;
    int cols_;
    int cellSize_;

    std::vector<std::vector<std::shared_ptr<Cell>>> cells_;
    sf::RenderWindow window_;
};

#endif //UNTITLED_GRID_H