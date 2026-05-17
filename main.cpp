#include "ConwayCell.h"
#include "HighLifeCell.h"
#include "DayNightCell.h"
#include "Grid.h"
#include "exceptions.h"
#include <iostream>
#include "SimulationConfig.h"
#include "ConsoleStatsObserver.h"

int main()
{
    try
    {
        int rows, cols, choice;

        std::cout << "Enter number of rows (1-100): ";
        std::cin >> rows;

        std::cout << "Enter number of cols (1-100): ";
        std::cin >> cols;

        if (rows < 1 || rows > 100 || cols < 1 || cols > 100)
            throw GridInitializationException(rows, cols, 10);

        std::cout << "Select cell type:\n"
                  << "  1 - Conway\n"
                  << "  2 - HighLife\n"
                  << "  3 - DayNight\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3)
            throw InvalidCellTypeException(choice);

        SimulationConfig::instance().set(rows, cols, choice, 0.3f);
        Grid grid(SimulationConfig::instance().rows(),
          SimulationConfig::instance().cols(), 10);

        std::unique_ptr<ICellFactory> factory;
        if      (choice == 1) factory = std::make_unique<ConwayCellFactory>();
        else if (choice == 2) factory = std::make_unique<HighLifeCellFactory>();
        else                  factory = std::make_unique<DayNightCellFactory>();

        grid.populate(*factory, 0.3f);

        ConsoleStatsObserver statsObserver(50); // afișează la fiecare 50 gen
        grid.addObserver(&statsObserver);

        GenerationLog<std::string> eventLog;
        eventLog.record("Simulation starting");
        //std::cout << eventLog << "\n";

        grid.run();

        eventLog.record("Simulation ended");
        std::cout << eventLog << "\n";

        std::cout << grid.getLog() << "\n";
        std::cout << "Average living cells: " << average(grid.getLog()) << "\n";
    }
    catch (const GridInitializationException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const InvalidCellTypeException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const InvalidProbabilityException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Unexpected Error] " << e.what() << "\n";
    }

    return 0;
}