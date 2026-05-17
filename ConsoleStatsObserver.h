
#ifndef UNTITLED_CONSOLESTATSOBSERVER_H
#define UNTITLED_CONSOLESTATSOBSERVER_H
#include "ISimulationObserver.h"
#include <iostream>

class ConsoleStatsObserver : public ISimulationObserver {
    int printEvery_;
public:
    explicit ConsoleStatsObserver(int every = 10) : printEvery_(every) {}

    void onGenerationUpdate(int generation, int livingCells) override {
        if (generation % printEvery_ == 0)
            std::cout << "Gen " << generation
                      << " | Alive: " << livingCells << "\n";
    }
};
#endif //UNTITLED_CONSOLESTATSOBSERVER_H