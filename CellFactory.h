//
// Created by Rebeca on 16/05/2026.
//

#ifndef UNTITLED_CELLFACTORY_H
#define UNTITLED_CELLFACTORY_H
// CellFactory.h
#pragma once
#include "Cell.h"
#include "ConwayCell.h"
#include "HighLifeCell.h"
#include "DayNightCell.h"
#include <memory>

class ICellFactory {
public:
    virtual std::shared_ptr<Cell> create(bool alive) const = 0;
    virtual ~ICellFactory() = default;
};

class ConwayCellFactory : public ICellFactory {
public:
    std::shared_ptr<Cell> create(bool alive) const override {
        return std::make_shared<ConwayCell>(alive);
    }
};

class HighLifeCellFactory : public ICellFactory {
public:
    std::shared_ptr<Cell> create(bool alive) const override {
        return std::make_shared<HighLifeCell>(alive);
    }
};

class DayNightCellFactory : public ICellFactory {
public:
    std::shared_ptr<Cell> create(bool alive) const override {
        return std::make_shared<DayNightCell>(alive);
    }
};
#endif