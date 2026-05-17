#include "exceptions.h"

InvalidCellTypeException::InvalidCellTypeException(int choice)
    : std::invalid_argument("Tipul celulei nu exista: " + std::to_string(choice) +
                            ". Valorile valide sunt 1 (Conway), 2 (HighLife), sau 3 (DayNight).")
{
}

std::ostream& operator<<(std::ostream& os, const InvalidCellTypeException& e)
{
    os << "[InvalidCellTypeException] " << e.what();
    return os;
}

GridInitializationException::GridInitializationException(int rows, int cols, int cellSize)
    : std::invalid_argument("Parametri invalizi: linii=" + std::to_string(rows) +
                            ", coloane="     + std::to_string(cols) +
                            ". Toate valorile trebuie sa fie intre 1 si 100.")
{
}

std::ostream& operator<<(std::ostream& os, const GridInitializationException& e)
{
    os << "[GridInitializationException] " << e.what();
    return os;
}

InvalidProbabilityException::InvalidProbabilityException(float probability)
    : std::out_of_range("Probabilitate invalida: " + std::to_string(probability) +
                        " trebuie sa fie in intervalul [0.0, 1.0].")
{
}

std::ostream& operator<<(std::ostream& os, const InvalidProbabilityException& e)
{
    os << "[InvalidProbabilityException] " << e.what();
    return os;
}