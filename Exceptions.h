#ifndef UNTITLED_EXCEPTIONS_H
#define UNTITLED_EXCEPTIONS_H
#pragma once
#include <stdexcept>
#include <string>
#include <ostream>

class InvalidCellTypeException : public std::invalid_argument
{
public:
    explicit InvalidCellTypeException(int choice);
    friend std::ostream& operator<<(std::ostream& os, const InvalidCellTypeException& e);
};

class GridInitializationException : public std::invalid_argument
{
public:
    GridInitializationException(int rows, int cols, int cellSize);
    friend std::ostream& operator<<(std::ostream& os, const GridInitializationException& e);
};

class InvalidProbabilityException : public std::out_of_range
{
public:
    explicit InvalidProbabilityException(float probability);
    friend std::ostream& operator<<(std::ostream& os, const InvalidProbabilityException& e);
};
#endif //UNTITLED_EXCEPTIONS_H