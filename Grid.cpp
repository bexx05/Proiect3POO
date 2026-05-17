#include "Grid.h"
#include "ConwayCell.h"
#include "HighLifeCell.h"
#include "DayNightCell.h"
#include "CellFactory.h"
#include "ISimulationObserver.h"
#include <random>
#include <iostream>

// constructor cu lista de initializare
Grid::Grid(int rows, int cols, int cellSize)
    : rows_(rows)
    , cols_(cols)
    , cellSize_(cellSize)
    , cells_(rows, std::vector<std::shared_ptr<Cell>>(cols))
    , window_(sf::VideoMode({ static_cast<unsigned>(cols * cellSize),
                               static_cast<unsigned>(rows * cellSize) }),
              "Conway's Game of Life")
{
}

//pot folosi default pentru ca am shared_ptr
Grid::~Grid() = default;

// starea initiala e bazata pe probabilitati random
void Grid::populate(const ICellFactory& factory, float aliveProbability)
{
    std::mt19937 rng{ std::random_device{}() };
    std::bernoulli_distribution dist(aliveProbability);

    for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c)
            cells_[r][c] = factory.create(dist(rng));
}

//aici are loc efectiv simularea, de aici apelez tranzitiile intre stari
void Grid::run()
{
    int generation =0;
    while (window_.isOpen() && generation< 5000)
    {
        while (const std::optional event = window_.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window_.close();

            // escape ca sa ies
            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                if (key->code == sf::Keyboard::Key::Escape)
                    window_.close();
        }

        update();

        generation++;

        window_.clear(sf::Color::Black);
        draw();
        window_.display();
    }
}

//aici se face tranzitia intre stari
void Grid::update()
{
    std::vector<std::vector<bool>> next(rows_, std::vector<bool>(cols_));

    for (int r = 0; r < rows_; ++r)
    {
        for (int c = 0; c < cols_; ++c)
        {
            const int n = countNeighbors(r, c);
            const Cell& cell = *cells_[r][c];

            next[r][c] = cell.isAlive() ? cell.survives(n)
                                        : cell.born(n);
        }
    }

    for (int r = 0; r < rows_; ++r)
        for (int c = 0; c < cols_; ++c)
            cells_[r][c]->setAlive(next[r][c]);

    generationLog_.record(Cell::getLivingCellCount()); // ← o linie
    ++generation_;
    for (auto* obs : observers_)
        obs->onGenerationUpdate(generation_, Cell::getLivingCellCount());
}

///aici desenez
void Grid::draw()
{
    sf::RectangleShape rect({ static_cast<float>(cellSize_ - 1),
                               static_cast<float>(cellSize_ - 1) });
    rect.setFillColor(sf::Color::White);

    for (int r = 0; r < rows_; ++r)
    {
        for (int c = 0; c < cols_; ++c)
        {
            if (cells_[r][c]->isAlive())
            {
                rect.setPosition({ static_cast<float>(c * cellSize_),
                                   static_cast<float>(r * cellSize_) });
                window_.draw(rect);
            }
        }
    }
}

//maxim 8 vecini
int Grid::countNeighbors(int row, int col) const
{
    int count = 0;
    for (int dr = -1; dr <= 1; ++dr)
    {
        for (int dc = -1; dc <= 1; ++dc)
        {
            if (dr == 0 && dc == 0) continue;

            const int nr = row + dr;
            const int nc = col + dc;

            if (nr >= 0 && nr < rows_ && nc >= 0 && nc < cols_)
                if (cells_[nr][nc]->isAlive())
                    ++count;
        }
    }

    return count;
}

//pentru cerinta cu downcast
void Grid::printCellTypeStats() const
{
    int conway = 0, highLife = 0, dayNight = 0;

    for (const auto& row : cells_)
        for (const auto& cell : row)
        {
            if      (std::dynamic_pointer_cast<ConwayCell>(cell))   ++conway;
            else if (std::dynamic_pointer_cast<HighLifeCell>(cell)) ++highLife;
            else if (std::dynamic_pointer_cast<DayNightCell>(cell)) ++dayNight;
        }

    std::cout << "ConwayCells: "    << conway
              << " HighLifeCells: " << highLife
              << " DayNightCells: " << dayNight << "\n";
}